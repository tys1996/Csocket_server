// Msg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{
	m_strText = _T("");//��ʼ����Ա����
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}

// CMsg ��Ա����

void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//���������ͷ�������
	{
		ar << (WORD)m_bClose;
		ar << m_strText;
	}
	else//���������ͽ�������
	{
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)//��̬�������