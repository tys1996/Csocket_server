// LSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "LSocket.h"
#include "IM_CsocketDlg.h"


// CLSocket

CLSocket::CLSocket(CIM_CsocketDlg* pDlg)
{
	m_pDlg = pDlg;//�Գ�Ա������ֵ
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;//��ָ���Ա������Ϊ��
}


// CLSocket ��Ա����

//OnAccept�¼������������׽����յ�FD_Accept��Ϣʱ���Զ����ô˺���
void CLSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnAccept(nErrorCode);//����ִ�л����ͬ������
	m_pDlg->OnAccept();//�������Ի������е���Ӧ����
}
IMPLEMENT_DYNAMIC(CLSocket,CSocket)//�������ӵĶ�̬�����
