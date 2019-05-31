//Download by http://www.NewXing.com
#if !defined(AFX_GDIPLUSDEMODLG_H__315E0925_1877_423F_92ED_F7CA6B814544__INCLUDED_)
#define AFX_GDIPLUSDEMODLG_H__315E0925_1877_423F_92ED_F7CA6B814544__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GdiplusDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGdiplusDemoDlg dialog

class CGdiplusDemoDlg : public CDialog
{
// Construction
public:
	CGdiplusDemoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGdiplusDemoDlg)
	enum { IDD = IDD_DIALOG1 };
	CTreeCtrl	m_ctrlTree;
	//}}AFX_DATA

	int m_index1, m_index2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGdiplusDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGdiplusDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIPLUSDEMODLG_H__315E0925_1877_423F_92ED_F7CA6B814544__INCLUDED_)
