
// SENDDlg.h : ͷ�ļ�
//

#pragma once


// CSENDDlg �Ի���
class CSENDDlg : public CDialogEx
{
// ����
public:
	CSENDDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_sendData;



	/******************************************/
	//����;ģ���������
	//����
	//		window�����ڱ���,�磺"MTC���������루��λһ��2016.12.15v2.7MES��ʽ��"
	//		cID:�ؼ�ID ��ʹ��spy��ȡ
	//		data:д��EDIT��ֵ
	/*******************************************/
	int Input(LPCTSTR window,int cID, CString data);
	/******************************************/
	//����;ģ����������ؼ�
	//����
	//		window�����ڱ���
	//		cID:�ؼ�ID ��ʹ��spy��ȡ
	//		Button :
	/*
	`	WM_LBUTTONDOWN	�������
		WM_LBUTTONUP	���̧��
		WM_LBUTTONDBLCLK	���˫��
		WM_RBUTTONDOWN	�Ҽ�����
		WM_RBUTTONUP	�Ҽ�̧��
		WM_RBUTTONDBLCLK	�Ҽ�˫��
		WM_LBUTTON	���
		*/
		
	//
	/*******************************************/
	int Click(LPCTSTR window,int cID, int Button);
	/******************************************/
	//����;ȡ��ָ��EDIT�ؼ���ֵ
	//����ֵ
	//		CString ,ȡ�õ��ַ���
	//����
	//		window�����ڱ���
	//		cID:�ؼ�ID ��ʹ��spy��ȡ

	/*******************************************/
	CString GetEdit(LPCTSTR window, int cID);

	/******************************************/
	//����;�����������
	//����ֵ
	//		int ,�ɹ�1��ʧ��0
	//����
	//		window�����ڱ���
	//		keyValue����ֵ���ο�WinUser.h
	/*******************************************/
	int VK_Input(LPCTSTR window,char keyValue);
	int VK_Input(LPCTSTR window, CString keyValue);
};
