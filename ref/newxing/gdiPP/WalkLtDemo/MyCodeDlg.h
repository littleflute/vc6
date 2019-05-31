//Download by http://www.NewXing.com
#if !defined(AFX_MYCODEDLG_H__CB796A39_5595_4CA7_B115_39C51FE11946__INCLUDED_)
#define AFX_MYCODEDLG_H__CB796A39_5595_4CA7_B115_39C51FE11946__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyCodeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyCodeDlg dialog

class CMyCodeDlg : public CDialog
{
// Construction
public:
	CMyCodeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyCodeDlg)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_ctrl;
	CString	m_str;
	//}}AFX_DATA

	CString m_title;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyCodeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCODEDLG_H__CB796A39_5595_4CA7_B115_39C51FE11946__INCLUDED_)
