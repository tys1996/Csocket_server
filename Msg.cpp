// Msg.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "Msg.h"


// CMsg

CMsg::CMsg()
{
	m_strText = _T("");//初始化成员变量
	m_bClose = FALSE;
}

CMsg::~CMsg()
{
}

// CMsg 成员函数

void CMsg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())//如果是输出就发送数据
	{
		ar << (WORD)m_bClose;
		ar << m_strText;
	}
	else//如果是输入就接收数据
	{
		WORD wd;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)//动态类的声明