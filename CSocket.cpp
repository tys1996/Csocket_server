// CSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "CSocket.h"
#include "IM_CsocketDlg.h"
#include "Msg.h"


// CCSocket

CCSocket::CCSocket(CIM_CsocketDlg* pDlg)
{
	//初始化代码
	m_pDlg = pDlg;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

CCSocket::~CCSocket()
{
	//初始化
	m_pDlg = NULL;
	if (m_pArchiveOut != NULL) delete m_pArchiveOut;
	if (m_pArchiveIn != NULL) delete m_pArchiveIn;
	if (m_pFile != NULL) delete m_pFile;
}


// CCSocket 成员函数

//OnReceive事件处理函数，当套接字收到数据时，激发此事件
void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnReceive(nErrorCode);

	//调用主对话框类中的相应函数来处理
	m_pDlg->OnReceive(this);
}

//初始化
void CCSocket::Initialize()
{
	//构造与此套接字相应的CSocketFile对象
	m_pFile = new CSocketFile(this, TRUE);
	//构造与此套接字相应的CArchive对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

//接受消息
void CCSocket::ReceiveMessage(CMsg* pMsg)
{
	//调用消息类的序列化函数，接收消息
	pMsg->Serialize(*m_pArchiveIn);
}

//发送消息
void CCSocket::SendMessege(CMsg* pMsg)
{
	if (m_pArchiveOut != NULL)
	{
		//调用消息类的序列化函数，发消息
		pMsg->Serialize(*m_pArchiveOut);
		//将CArchive对象中的数据强制写入CSocketFile文件中
		m_pArchiveOut->Flush();
	}
}
IMPLEMENT_DYNAMIC(CCSocket,CSocket)