#pragma once
//为了利用CSocket类及其派生类可以
//和对象CSocketFile、CArchive合作来进行数据发送和接收的特性
//构造一个专用于消息传输的类

// CMsg 命令目标

class CMsg : public CObject
{
	DECLARE_DYNCREATE(CMsg);//动态类声明
public:
	CMsg();
	virtual ~CMsg();
	CString m_strText;//字符串成员
	BOOL m_bClose;//是否关闭状态
	virtual void Serialize(CArchive& ar);//序列化函数
};


