// LSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "IM_Csocket.h"
#include "LSocket.h"
#include "IM_CsocketDlg.h"


// CLSocket

CLSocket::CLSocket(CIM_CsocketDlg* pDlg)
{
	m_pDlg = pDlg;//对成员变量赋值
}

CLSocket::~CLSocket()
{
	m_pDlg = NULL;//将指针成员变量置为空
}


// CLSocket 成员函数

//OnAccept事件处理函数，当套接字收到FD_Accept消息时，自动调用此函数
void CLSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSocket::OnAccept(nErrorCode);//首先执行基类的同名函数
	m_pDlg->OnAccept();//调用主对话框类中的相应函数
}
IMPLEMENT_DYNAMIC(CLSocket,CSocket)//编程者添加的动态类语句
