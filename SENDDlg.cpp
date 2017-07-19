
// SENDDlg.cpp : ʵ���ļ�
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
CString SendData;//ȫ�ֱ���������ֵ
int  ControlID;//ȫ�ֱ������ؼ�ID
int Button;
char* GetBuffer;

#define WM_LBUTTON 0

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSENDDlg �Ի���



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


// CSENDDlg ��Ϣ�������

BOOL CSENDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSENDDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSENDDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CALLBACK EnumProc_Input(HWND hwnd, LPARAM lParam)
{
	int id = -1;
	char lpclassName[255];
   //��õ�ǰ����Ӵ��ڵ�ID 
    id = ::GetDlgCtrlID(hwnd);
	::GetClassName(hwnd,(LPSTR)lpclassName,255);

	if (id == ControlID)
	{	
		
		
		if (_stricmp(lpclassName, "COMBOBOX") == 0)//0:���
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
	//��õ�ǰ����Ӵ��ڵ�ID 
	id = ::GetDlgCtrlID(hwnd);
	::GetClassName(hwnd, (LPSTR)lpclassName, 255);

	if (id == ControlID)
	{


		if (_stricmp(lpclassName, "EDIT") == 0)//0:���
		{
			
			int len = ::SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
			buffer = new char[len + 1];
			int n = ::SendMessage(hwnd, WM_GETTEXT, len + 1, (LPARAM)buffer);
			//MessageBox(buffer);
			GetBuffer = buffer;
		}
		else
		{
			AfxMessageBox(_T("�޷���ȡ�˿ؼ���ֵ"));
		}

	}
	return TRUE;
}

BOOL CALLBACK EnumProc_Click(HWND hwnd, LPARAM lParam)
{
	int id = -1;
	//��õ�ǰ����Ӵ��ڵ�ID 
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
			::SendMessage(hwnd, WM_LBUTTONDOWN, NULL, 0);  //������갴����Ϣ 
			break;
		case  WM_LBUTTONUP:
			::SendMessage(hwnd, WM_LBUTTONUP, NULL, 0);  //������갴����Ϣ 
			break;
		case  WM_LBUTTONDBLCLK:
			::SendMessage(hwnd, WM_LBUTTONDBLCLK, NULL, 0);  //������갴����Ϣ 
			break;
		case  WM_RBUTTONDOWN:
			::SendMessage(hwnd, WM_RBUTTONDOWN, NULL, 0);  //������갴����Ϣ 
			break;
		case  WM_RBUTTONUP:
			::SendMessage(hwnd, WM_RBUTTONUP, NULL, 0);  //������갴����Ϣ 
			break;
		case  WM_RBUTTONDBLCLK:
			::SendMessage(hwnd, WM_RBUTTONDBLCLK, NULL, 0);  //������갴����Ϣ 
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
//����;ģ���������
//����
//		window�����ڱ���
//		cID:�ؼ�ID ��ʹ��spy��ȡ
//		data:д��EDIT��ֵ
/*******************************************/
int CSENDDlg::Input(LPCTSTR window,int cID,CString data)
{
	CWnd *w = FindWindow(NULL, window);
	if (w == NULL)
	{
		AfxMessageBox(_T("�Ҳ�������"));
		return 0;
	}		
	else
	{
		//parent���Ǹ������ڵľ����
		HWND parent = w->m_hWnd;

		ControlID = cID;
		SendData = data;

		//�о��������µ������Ӵ��ڣ������Ӵ��ڵ��Ӵ���  
		EnumChildWindows(parent, EnumProc_Input, (LPARAM)this);
		return 1;
	}
	
}


/******************************************/
//����;ģ����������ؼ�
//����
//		window�����ڱ���
//		cID:�ؼ�ID ��ʹ��spy��ȡ
/*******************************************/
int CSENDDlg::Click(LPCTSTR window,int cID,int button)
{
	CWnd *w = FindWindow(NULL,window);
	::SetForegroundWindow(w->m_hWnd);
	CString str;
	str.Format("�Ҳ�������:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}	
	else
	{
		//parent���Ǹ������ڵľ����
		HWND parent = w->m_hWnd;
		ControlID = cID;
		Button = button;
		//�о��������µ������Ӵ��ڣ������Ӵ��ڵ��Ӵ���  
		EnumChildWindows(parent, EnumProc_Click, (LPARAM)this);
		return 1;
	}
	
}

/******************************************/
//����;ȡ��ָ��EDIT�ؼ���ֵ
//����ֵ
//		CString ,ȡ�õ��ַ���
//����
//		window�����ڱ���
//		cID:�ؼ�ID ��ʹ��spy��ȡ
/*******************************************/
CString  CSENDDlg::GetEdit(LPCTSTR window, int cID)
{
	CWnd *w = FindWindow(NULL, window);
	::SetForegroundWindow(w->m_hWnd);
	CString str;
	str.Format("�Ҳ�������:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return NULL;
	}
	else
	{
		//parent���Ǹ������ڵľ����
		HWND parent = w->m_hWnd;
		ControlID = cID;
		//�о��������µ������Ӵ��ڣ������Ӵ��ڵ��Ӵ���  
		EnumChildWindows(parent, EnumProc_GetEdit, (LPARAM)this);
		return GetBuffer;
	}
}
/******************************************/
//����;ģ����̰�������
//����ֵ���ɹ�1��ʧ��0
//����
//		window�����ڱ���
//		keyValue:����ֵ
/*******************************************/
int CSENDDlg::VK_Input(LPCTSTR window,char keyValue)
{

	CWnd *w = FindWindow(NULL, window);
	CString str;
	str.Format("�Ҳ�������:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}
	else
	{
		::SetForegroundWindow(w->m_hWnd);

		keybd_event(keyValue, 0, 0, 0);//����
		keybd_event(keyValue, 0, KEYEVENTF_KEYUP, 0);//����
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
	str.Format("�Ҳ�������:%s", window);
	if (w == NULL)
	{
		AfxMessageBox(str);
		return 0;
	}
	else
	{
		::SetForegroundWindow(w->m_hWnd);
		keybd_event(keyValue, 0, 0, 0);//����
		keybd_event(keyValue, 0, KEYEVENTF_KEYUP, 0);//����
		return 1;
	}
	return 0;
}


*/
void CSENDDlg::OnBnClickedOk()
{
	// Ѱ�ұ���Ϊ�����Ĵ���ָ��
	
	//window= _T("MTC���������루��λһ��2016.12.15v2.7MES��ʽ�棨������IP2072����+д��+У�ţ�");
	window = _T("serial-com4 - SecureCRT");
	/*
	Input(window, 0x400, _T("201002377001"));//������
	Sleep(500);
	Input(window, 0x400, _T("201002377001"));//������
	Input(window, 0x417, _T("5A"));

	Input(window, 0x419, _T("д��"));

	Input(window, 0x420, _T("1001251"));
	Click(window, 0x401,WM_LBUTTON);
	*/
	//MessageBox(GetEdit(window, 0x400));
	/*
	window = _T("��Խ���ֻ�������������");
	Input(window, 0x3EB, _T("com5"));
	Input(window, 0x3EC, _T("��У��"));
	Input(window, 0x3F0, _T("yangsen"));
	*/
	
	VK_Input(window, 13);
	//VK_Input(window, VK_LWIN);

}