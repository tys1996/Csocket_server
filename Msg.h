#pragma once
//Ϊ������CSocket�༰�����������
//�Ͷ���CSocketFile��CArchive�������������ݷ��ͺͽ��յ�����
//����һ��ר������Ϣ�������

// CMsg ����Ŀ��

class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);//��̬������
public:
	CMsg();
	virtual ~CMsg();
	CString m_strText;//�ַ�����Ա
	BOOL m_bClose;//�Ƿ�ر�״̬
	virtual void Serialize(CArchive& ar);//���л�����
};


