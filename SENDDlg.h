
// SENDDlg.h : 头文件
//

#pragma once


// CSENDDlg 对话框
class CSENDDlg : public CDialogEx
{
// 构造
public:
	CSENDDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_sendData;



	/******************************************/
	//功能;模拟键盘输入
	//参数
	//		window：窗口标题,如："MTC条形码输入（工位一）2016.12.15v2.7MES正式版"
	//		cID:控件ID ，使用spy获取
	//		data:写入EDIT的值
	/*******************************************/
	int Input(LPCTSTR window,int cID, CString data);
	/******************************************/
	//功能;模拟鼠标点击进控件
	//参数
	//		window：窗口标题
	//		cID:控件ID ，使用spy获取
	//		Button :
	/*
	`	WM_LBUTTONDOWN	左键按下
		WM_LBUTTONUP	左键抬起
		WM_LBUTTONDBLCLK	左键双击
		WM_RBUTTONDOWN	右键按下
		WM_RBUTTONUP	右键抬起
		WM_RBUTTONDBLCLK	右键双击
		WM_LBUTTON	点击
		*/
		
	//
	/*******************************************/
	int Click(LPCTSTR window,int cID, int Button);
	/******************************************/
	//功能;取得指定EDIT控件的值
	//返回值
	//		CString ,取得的字符串
	//参数
	//		window：窗口标题
	//		cID:控件ID ，使用spy获取

	/*******************************************/
	CString GetEdit(LPCTSTR window, int cID);

	/******************************************/
	//功能;虚拟键盘输入
	//返回值
	//		int ,成功1，失败0
	//参数
	//		window：窗口标题
	//		keyValue：键值，参考WinUser.h
	/*******************************************/
	int VK_Input(LPCTSTR window,char keyValue);
	int VK_Input(LPCTSTR window, CString keyValue);
};
