#pragma once

class CIM_CsocketDlg;//编程者添加的对话框定义

//用于监听客户端的连接请求
// CLSocket 命令目标
class CLSocket : public CSocket
{
	DECLARE_DYNAMIC(CLSocket);//动态类的声明

public:
	CLSocket(CIM_CsocketDlg* pDlg);//为构造函数添加了入口参数
	virtual ~CLSocket();
	CIM_CsocketDlg* m_pDlg;//成员变量，是指向对话框类的指针

	//可重载的回调函数，当套接字收到连接请求是，自动调用函数
protected:
	virtual void OnAccept(int nErrorCode);

};


