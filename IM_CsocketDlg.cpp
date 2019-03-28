
// IM_CsocketDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "IM_CsocketDlg.h"
#include "afxdialogex.h"
#include "Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CIM_CsocketDlg �Ի���



CIM_CsocketDlg::CIM_CsocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IM_CSOCKET_DIALOG, pParent)
	//��ʼ��
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


// CIM_CsocketDlg ��Ϣ�������

BOOL CIM_CsocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nPort = 8000;
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIM_CsocketDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIM_CsocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//void CIM_CsocketDlg::OnButtonListen()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnOK();
//}

//������ֹͣ����ťʱ��ִ�д˺���
void CIM_CsocketDlg::OnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	CMsg msg;
	msg.m_strText = "��������ֹ����";
	delete m_pLSocket;//ɾ�������׽���
	m_pLSocket = NULL;
	while (!m_connList.IsEmpty())//�������б���д���
	{
		//��ÿһ�����ӺͿͻ������͡���������ֹ���񡱵���Ϣ
		//�����ɾ���ѽ���������
		CCSocket* pSocket = (CCSocket*)m_connList.RemoveHead();
		pSocket->SendMessege(&msg);
		delete pSocket;
	}
	//����б��
	while (m_listMsg.GetCount() != 0)
	{
		m_listMsg.DeleteString(0);
	}
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}

//��������ʱ��ִ�У�����������׽��ֵļ���
void CIM_CsocketDlg::OnButtonListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//����û�����
	//���������׽��ֶ���
	m_pLSocket = new CLSocket(this);
	//���������׽��ֵĵײ��׽��֣����û�ָ���Ķ˿�������
	if (!m_pLSocket->Create(m_nPort))
	{
		delete m_pLSocket;//������
		m_pLSocket = NULL;
		AfxMessageBox(L"���������׽��ִ���");
		return;
	}
	//���������׽��֣�ʱ��׼�����տͻ��˵���������
	if (!m_pLSocket->Listen())
	{
		delete m_pLSocket;//������
		m_pLSocket = NULL;
		AfxMessageBox(L"������������");
		return;
	}
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

//������������
void CIM_CsocketDlg::OnAccept()
{
	//����������ͻ������Ӳ��������ݵ��׽��ֶ���
	CCSocket* pSocket = new CCSocket(this);
	if (m_pLSocket->Accept(*pSocket))//���տͻ�������������
	{
		//�������׽��ֳ�ʼ��
		pSocket->Initialize();
		m_connList.AddTail(pSocket);
		//������������
		CString strTemp;
		strTemp.Format(L"����������%d", m_connList.GetCount());
		m_staNum.SetWindowTextW(strTemp);
	}
	else
	{
		delete pSocket;
	}
}

//��ȡ�ͻ����ķ�����Ϣ
void CIM_CsocketDlg::OnReceive(CCSocket* pSocket)
{
	static CMsg msg;
	do {
		//���տͻ�������Ϣ��ʾ�ڷ������ĶԻ�����
		pSocket->ReceiveMessage(&msg);
		//���ͻ�������Ϣ��ʾ�ڷ������Ի�����
		m_listMsg.AddString(msg.m_strText);
		//�����пͻ������ظÿͻ�����������Ϣ
		backClients(&msg);

		//����ͻ����رգ�����ÿͻ��������Ӵ������б���ɾ��
		if (msg.m_bClose)
		{
			pSocket->Close();
			POSITION pos, temp;
			for (pos = m_connList.GetHeadPosition(); pos != NULL;)
			{
				//�����ѽ��رյĿͻ���
				//����Ϣ�б��н��Ѿ�����������ɾ��
				temp = pos;
				CCSocket* pSock = (CCSocket*)m_connList.GetNext(pos);
				//ƥ��ɹ�
				if (pSock == pSocket)
				{
					m_connList.RemoveAt(temp);
					CString strTemp;
					//������������
					strTemp.Format(L"����������%d", m_connList.GetCount());
					m_staNum.SetWindowTextW(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}

	} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}

//���������յ�ĳ���ͻ�����������Ϣ�󣬽���ת���������ҵ����пͻ���
void CIM_CsocketDlg::backClients(CMsg* pMsg)
{
	for (POSITION pos = m_connList.GetHeadPosition(); pos != NULL;)
	{
		//��������б�ĳ�Ա
		CCSocket* pSocket = (CCSocket*)m_connList.GetNext(pos);
		pSocket->SendMessege(pMsg);
	}
}
