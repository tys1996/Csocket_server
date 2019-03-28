
// IM_CsocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "IM_CsocketDlg.h"
#include "afxdialogex.h"
#include "Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIM_CsocketDlg 对话框



CIM_CsocketDlg::CIM_CsocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IM_CSOCKET_DIALOG, pParent)
	//初始化
	, m_nPort(0)
	, m_pLSocket(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pLSocket = NULL;
}

void CIM_CsocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_NUM, m_staNum);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnListen);
	DDX_Control(pDX, IDOK, m_btnClose);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
}

BEGIN_MESSAGE_MAP(CIM_CsocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_STN_CLICKED(IDC_STATIC_NUM, &CIM_CsocketDlg::OnStnClickedStaticNum)
//ON_BN_CLICKED(IDOK, &CIM_CsocketDlg::OnButtonListen)
ON_BN_CLICKED(IDOK, &CIM_CsocketDlg::OnClose)
ON_BN_CLICKED(IDC_BUTTON_LISTEN, &CIM_CsocketDlg::OnButtonListen)
END_MESSAGE_MAP()


// CIM_CsocketDlg 消息处理程序

BOOL CIM_CsocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_nPort = 8000;
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIM_CsocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIM_CsocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIM_CsocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CIM_CsocketDlg::OnButtonListen()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
//}

//当单击停止服务按钮时，执行此函数
void CIM_CsocketDlg::OnClose()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CMsg msg;
	msg.m_strText = "服务器终止服务";
	delete m_pLSocket;//删除监听套接字
	m_pLSocket = NULL;
	while (!m_connList.IsEmpty())//对连接列表进行处理
	{
		//向每一个连接和客户机发送“服务器终止服务”的消息
		//并逐个删除已建立的连接
		CCSocket* pSocket = (CCSocket*)m_connList.RemoveHead();
		pSocket->SendMessege(&msg);
		delete pSocket;
	}
	//清除列表框
	while (m_listMsg.GetCount() != 0)
	{
		m_listMsg.DeleteString(0);
	}
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

//单击监听时，执行，启动服务端套接字的监听
void CIM_CsocketDlg::OnButtonListen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//获得用户输入
	//创建侦听套接字对象
	m_pLSocket = new CLSocket(this);
	//穿件监听套接字的底层套接字，在用户指定的端口上侦听
	if (!m_pLSocket->Create(m_nPort))
	{
		delete m_pLSocket;//错误处理
		m_pLSocket = NULL;
		AfxMessageBox(L"创建监听套接字错误");
		return;
	}
	//启动监听套接字，时刻准备接收客户端的连接请求
	if (!m_pLSocket->Listen())
	{
		delete m_pLSocket;//错误处理
		m_pLSocket = NULL;
		AfxMessageBox(L"启动监听错误");
		return;
	}
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

//接收连接请求
void CIM_CsocketDlg::OnAccept()
{
	//创建用于与客户端连接并交换数据的套接字对象
	CCSocket* pSocket = new CCSocket(this);
	if (m_pLSocket->Accept(*pSocket))//接收客户机的连接请求
	{
		//对连接套接字初始化
		pSocket->Initialize();
		m_connList.AddTail(pSocket);
		//更新在线人数
		CString strTemp;
		strTemp.Format(L"在线人数：%d", m_connList.GetCount());
		m_staNum.SetWindowTextW(strTemp);
	}
	else
	{
		delete pSocket;
	}
}

//获取客户机的发送消息
void CIM_CsocketDlg::OnReceive(CCSocket* pSocket)
{
	static CMsg msg;
	do {
		//接收客户机的信息显示在服务器的对话框中
		pSocket->ReceiveMessage(&msg);
		//将客户机的信息显示在服务器对话框中
		m_listMsg.AddString(msg.m_strText);
		//向所有客户机返回该客户机发来的消息
		backClients(&msg);

		//如果客户机关闭，将与该客户机的连接从连接列表中删除
		if (msg.m_bClose)
		{
			pSocket->Close();
			POSITION pos, temp;
			for (pos = m_connList.GetHeadPosition(); pos != NULL;)
			{
				//对于已近关闭的客户机
				//在消息列表中将已经建立的连接删除
				temp = pos;
				CCSocket* pSock = (CCSocket*)m_connList.GetNext(pos);
				//匹配成功
				if (pSock == pSocket)
				{
					m_connList.RemoveAt(temp);
					CString strTemp;
					//更新在线人数
					strTemp.Format(L"在线人数：%d", m_connList.GetCount());
					m_staNum.SetWindowTextW(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}

	} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}

//当服务器收到某个客户机发来的信息后，将他转发给聊天室的所有客户机
void CIM_CsocketDlg::backClients(CMsg* pMsg)
{
	for (POSITION pos = m_connList.GetHeadPosition(); pos != NULL;)
	{
		//获得连接列表的成员
		CCSocket* pSocket = (CCSocket*)m_connList.GetNext(pos);
		pSocket->SendMessege(pMsg);
	}
}
