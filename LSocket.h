#pragma once

class CIM_CsocketDlg;//�������ӵĶԻ�����

//���ڼ����ͻ��˵���������
// CLSocket ����Ŀ��
class CLSocket : public CSocket
{
	DECLARE_DYNAMIC(CLSocket);//��̬�������

public:
	CLSocket(CIM_CsocketDlg* pDlg);//Ϊ���캯���������ڲ���
	virtual ~CLSocket();
	CIM_CsocketDlg* m_pDlg;//��Ա��������ָ��Ի������ָ��

	//�����صĻص����������׽����յ����������ǣ��Զ����ú���
protected:
	virtual void OnAccept(int nErrorCode);

};


