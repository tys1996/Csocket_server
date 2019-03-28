#pragma once

class CIM_CsocketDlg;//编程者添加的类声明
class CMsg;

//用于与客户端建立连接并交换数据
// CCSocket 命令目标

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);//动态类声明
public:
	CCSocket(CIM_CsocketDlg* pDlg);//构造函数内，添加了入口参数
	virtual ~CCSocket();

	CIM_CsocketDlg* m_pDlg;//主对话框类指针变量
	CSocketFile* m_pFile;//CSocketFile对象的指针变量
	CArchive* m_pArchiveIn;//用于输入的CArchive对象的指针变量
	CArchive* m_pArchiveOut;//用于输入的CArchive对象的指针变量

	void Initialize();//初始化
	void ReceiveMessage(CMsg* pMsg);//发送消息
	void SendMessege(CMsg* pMsg);//接受消息
	
	//可重载的回调函数，当套接字接收到数据时，自动调用此函数
protected:
	virtual void OnReceive(int nErrorCode);
};


