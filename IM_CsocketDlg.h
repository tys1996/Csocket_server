
// IM_CsocketDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcoll.h"
#include "CSocket.h"
#include "LSocket.h"

class CMsg;

// CIM_CsocketDlg �Ի���
class CIM_CsocketDlg : public CDialogEx
{
// ����
public:
	CIM_CsocketDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IM_CSOCKET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnButtonListen();
	DECLARE_MESSAGE_MAP()

public:
	//�ർ����ӵ�
	CStatic m_staNum;
	UINT m_nPort;
	CButton m_btnListen;
	CButton m_btnClose;
	CListBox m_listMsg;

	CLSocket* m_pLSocket;//�����׽���ָ�����
	CPtrList m_connList;//�����б�

	void OnAccept();//������������
	void OnReceive(CCSocket* pSocket);//��ȡ�ͻ���������Ϣ
	void backClients(CMsg* pMsg);//�������ҵ����пͻ���ת����Ϣ
};
