
// IM_CsocketDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcoll.h"
#include "CSocket.h"
#include "LSocket.h"

class CMsg;

// CIM_CsocketDlg 对话框
class CIM_CsocketDlg : public CDialogEx
{
// 构造
public:
	CIM_CsocketDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IM_CSOCKET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnButtonListen();
	DECLARE_MESSAGE_MAP()

public:
	//类导向添加的
	CStatic m_staNum;
	UINT m_nPort;
	CButton m_btnListen;
	CButton m_btnClose;
	CListBox m_listMsg;

	CLSocket* m_pLSocket;//侦听套接字指针变量
	CPtrList m_connList;//连接列表

	void OnAccept();//接收连接请求
	void OnReceive(CCSocket* pSocket);//获取客户机发送消息
	void backClients(CMsg* pMsg);//向聊天室的所有客户机转发消息
};
