
// SENDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SEND.h"
#include "SENDDlg.h"
#include "afxdialogex.h"
#include"winUser.h"
#include"string.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString window;
CString SendData;//全局变量，输入值
int  ControlID;//全局变量，控件ID
int Button;
char* GetBuffer;

#define WM_LBUTTON 0

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CSENDDlg 对话框



CSENDDlg::CSENDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEND_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSENDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CSENDDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSENDDlg::OnBnClickedOk)
	
END_MESSAGE_MAP()


// CSENDDlg 消息处理程序

BOOL CSENDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSENDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSENDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSENDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CALLBACK EnumProc_Input(HWND hwnd, LPARAM lParam)
{
	int id = -1;
	char lpclassName[255];
   //获得当前这个子窗口的ID 
    id = ::GetDlgCtrlID(hwnd);
	::GetClassName(hwnd,(LPSTR)lpclassName,255);

	if (id == ControlID)
	{	
		
		
		if (_stricmp(lpclassName, "COMBOBOX") == 0)//0:相等
		{	
			::SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)(LPCTSTR)(SendData));
			//::SendMessage(hwnd, CBN_SELCHANGE, NULL, (LPARAM)(LPCTSTR)(SendData));
		}
		else
		{
			::SendMessage(hwnd, WM_SETTEXT, NULL, (LPARAM)(LPCTSTR)(SendData));
		}
		
	}

	  return TRUE;
}


BOOL CALLBACK EnumProc_GetEdit(HWND hwnd, LPARAM lParam)
{
	char* buffer;
	int id = -1;
	char lpclassName[255];
	//获得当前这个子窗口的ID 
	id = ::GetDlgCtrlID(hwnd);
	::GetClassName(hwnd, (LPSTR)lpclassName, 255);

	if (id == ControlID)
	{


		if (_stricmp(lpclassName, "EDIT") == 0)//0:相等
		{
			
			int len = ::SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
			buffer = new char[len + 1];
			int n = ::SendMessage(hwnd, WM_GETTEXT, len + 1, (LPARAM)buffer);
			//MessageBox(buffer);
			GetBuffer = buffer;
		}
		else
		{
			AfxMessageBox(_T("无法获取此控件的值"));
		}

	}
	return TRUE;
}

BOOL CALLBACK EnumProc_Click(HWND hwnd, LPARAM lParam)
{
	int id = -1;
	//获得当前这个子窗口的ID 
	id = ::GetDlgCtrlID(hwnd);

	if (id == ControlID)
	{
/*
 WM_LBUTTONDOWN                  
 WM_LBUTTONUP                    
 WM_LBUTTONDBLCLK                
 WM_RBUTTONDOWN                  
 WM_RBUTTONUP                    
 WM_RBUTTONDBLCLK                
*/
		switch (Button)
		{
		case  WM_LBUTTONDOWN:
			::SendMessage(hwnd, WM_LBUTTONDOWN, NULL, 0);  //发送鼠标按下消息 
			break;
		case  WM_LBUTTONUP:
			::SendMessage(hwnd, WM_LBUTTONUP, NULL, 0);  //发送鼠标按下消息 
			break;
		case  WM_LBUTTONDBLCLK:
			::SendMessage(hwnd, WM_LBUTTONDBLCLK, NULL, 0);  //发送鼠标按下消息 
			break;
		case  WM_RBUTTONDOWN:
			::SendMessage(hwnd, WM_RBUTTONDOWN, NULL, 0);  //发送鼠标按下消息 
			break;
		case  WM_RBUTTONUP:
			::SendMessage(hwnd, WM_RBUTTONUP, NULL, 0);  //发送鼠标按下消息 
			break;
		case  WM_RBUTTONDBLCLK:
			::SendMessage(hwnd, WM_RBUTTONDBLCLK, NULL, 0);  //发送鼠标按下消息 
			break;
		case WM_LBUTTON:
			::SendMessage(hwnd, WM_LBUTTONDOWN, NULL, 0);
			::SendMessage(hwnd, WM_LBUTTONUP, NULL, 0);
			break;
		default:
			break;
		}
	
	}
	return TRUE;
}
/******************************************/
//功能;模拟键盘输入
//参数
//		window：窗口标题
//		cID:控件ID ，使用spy获取
//		data:写入EDIT的值
/*******************************************/
int CSENDDlg::Input(LPCTSTR window,int cID,CString data)
{
	CWnd *w = FindWindow(NULL, window);
	if (w == NULL)
	{
		AfxMessageBox(_T("找不到窗口"));
		return 0;
	}		
	else
	{
		//parent就是该主窗口的句柄，
		HWND parent = w->m_hWnd;

		ControlID = cID;
		SendData = data;

		//列举主窗口下的所有子窗口，包括子窗口的子窗口  
		EnumChildWindows(parent, EnumProc_Input, (LPARAM)this);
		return 1;
	}
	
}


/******************************************/
//功能;模拟鼠标点击进控件
//参数
//		window：窗口标题
//		cID:控件ID ，使用spy获取
/*******************************************/
int CSENDDlg::Click(LPCTSTR window,int cID,int button)
{
	CWnd *w = FindWindow(NULL,window);
	::SetForegroundWindow(w->m_hWnd);
	CString str;
	str.Format("找不到窗口:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}	
	else
	{
		//parent就是该主窗口的句柄，
		HWND parent = w->m_hWnd;
		ControlID = cID;
		Button = button;
		//列举主窗口下的所有子窗口，包括子窗口的子窗口  
		EnumChildWindows(parent, EnumProc_Click, (LPARAM)this);
		return 1;
	}
	
}

/******************************************/
//功能;取得指定EDIT控件的值
//返回值
//		CString ,取得的字符串
//参数
//		window：窗口标题
//		cID:控件ID ，使用spy获取
/*******************************************/
CString  CSENDDlg::GetEdit(LPCTSTR window, int cID)
{
	CWnd *w = FindWindow(NULL, window);
	::SetForegroundWindow(w->m_hWnd);
	CString str;
	str.Format("找不到窗口:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return NULL;
	}
	else
	{
		//parent就是该主窗口的句柄，
		HWND parent = w->m_hWnd;
		ControlID = cID;
		//列举主窗口下的所有子窗口，包括子窗口的子窗口  
		EnumChildWindows(parent, EnumProc_GetEdit, (LPARAM)this);
		return GetBuffer;
	}
}
/******************************************/
//功能;模拟键盘按键输入
//返回值：成功1，失败0
//参数
//		window：窗口标题
//		keyValue:按键值
/*******************************************/
int CSENDDlg::VK_Input(LPCTSTR window,char keyValue)
{

	CWnd *w = FindWindow(NULL, window);
	CString str;
	str.Format("找不到窗口:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}
	else
	{
		::SetForegroundWindow(w->m_hWnd);

		keybd_event(keyValue, 0, 0, 0);//按下
		keybd_event(keyValue, 0, KEYEVENTF_KEYUP, 0);//弹起
		return 1;
	}
	return 0;
}


/*
int CSENDDlg::VK_Input(LPCTSTR window,CString keyValue)
{	
	char *key = (LPSTR)(LPCTSTR)keyValue;
	CWnd *w = FindWindow(NULL, window);
	CString str;
	str.Format("找不到窗口:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}
	else
	{
		::SetForegroundWindow(w->m_hWnd);
		keybd_event(keyValue, 0, 0, 0);//按下
		keybd_event(keyValue, 0, KEYEVENTF_KEYUP, 0);//弹起
		return 1;
	}
	return 0;
}


*/
void CSENDDlg::OnBnClickedOk()
{
	// 寻找标题为“”的窗口指针
	
	//window= _T("MTC条形码输入（工位一）2016.12.15v2.7MES正式版（适用于IP2072测试+写号+校号）");
	window = _T("serial-com4 - SecureCRT");
	/*
	Input(window, 0x400, _T("201002377001"));//订单号
	Sleep(500);
	Input(window, 0x400, _T("201002377001"));//订单号
	Input(window, 0x417, _T("5A"));

	Input(window, 0x419, _T("写号"));

	Input(window, 0x420, _T("1001251"));
	Click(window, 0x401,WM_LBUTTON);
	*/
	//MessageBox(GetEdit(window, 0x400));
	/*
	window = _T("飞越数字机顶盒量产工具");
	Input(window, 0x3EB, _T("com5"));
	Input(window, 0x3EC, _T("奇校验"));
	Input(window, 0x3F0, _T("yangsen"));
	*/
	
	VK_Input(window, 13);
	//VK_Input(window, VK_LWIN);

}