
// IM_Csocket.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIM_CsocketApp: 
// �йش����ʵ�֣������ IM_Csocket.cpp
//

class CIM_CsocketApp : public CWinApp
{
public:
	CIM_CsocketApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIM_CsocketApp theApp;