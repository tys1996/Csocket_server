#pragma once

class CIM_CsocketDlg;//�������ӵ�������
class CMsg;

//������ͻ��˽������Ӳ���������
// CCSocket ����Ŀ��

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);//��̬������
public:
	CCSocket(CIM_CsocketDlg* pDlg);//���캯���ڣ��������ڲ���
	virtual ~CCSocket();

	CIM_CsocketDlg* m_pDlg;//���Ի�����ָ�����
	CSocketFile* m_pFile;//CSocketFile�����ָ�����
	CArchive* m_pArchiveIn;//���������CArchive�����ָ�����
	CArchive* m_pArchiveOut;//���������CArchive�����ָ�����

	void Initialize();//��ʼ��
	void ReceiveMessage(CMsg* pMsg);//������Ϣ
	void SendMessege(CMsg* pMsg);//������Ϣ
	
	//�����صĻص����������׽��ֽ��յ�����ʱ���Զ����ô˺���
protected:
	virtual void OnReceive(int nErrorCode);
};


