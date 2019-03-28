// CSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "CSocket.h"
#include "IM_CsocketDlg.h"
#include "Msg.h"


// CCSocket

CCSocket::CCSocket(CIM_CsocketDlg* pDlg)
{
	//��ʼ������
	m_pDlg = pDlg;
	m_pFile = NULL;
	m_pArchiveIn = NULL;
	m_pArchiveOut = NULL;
}

CCSocket::~CCSocket()
{
	//��ʼ��
	m_pDlg = NULL;
	if (m_pArchiveOut != NULL) delete m_pArchiveOut;
	if (m_pArchiveIn != NULL) delete m_pArchiveIn;
	if (m_pFile != NULL) delete m_pFile;
}


// CCSocket ��Ա����

//OnReceive�¼������������׽����յ�����ʱ���������¼�
void CCSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);

	//�������Ի������е���Ӧ����������
	m_pDlg->OnReceive(this);
}

//��ʼ��
void CCSocket::Initialize()
{
	//��������׽�����Ӧ��CSocketFile����
	m_pFile = new CSocketFile(this, TRUE);
	//��������׽�����Ӧ��CArchive����
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);
}

//������Ϣ
void CCSocket::ReceiveMessage(CMsg* pMsg)
{
	//������Ϣ������л�������������Ϣ
	pMsg->Serialize(*m_pArchiveIn);
}

//������Ϣ
void CCSocket::SendMessege(CMsg* pMsg)
{
	if (m_pArchiveOut != NULL)
	{
		//������Ϣ������л�����������Ϣ
		pMsg->Serialize(*m_pArchiveOut);
		//��CArchive�����е�����ǿ��д��CSocketFile�ļ���
		m_pArchiveOut->Flush();
	}
}
IMPLEMENT_DYNAMIC(CCSocket,CSocket)