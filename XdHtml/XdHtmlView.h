// XdHtmlView.h : interface of the CXdHtmlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDHTMLVIEW_H__54D4F885_A085_4A7A_B92A_F1C31162080A__INCLUDED_)
#define AFX_XDHTMLVIEW_H__54D4F885_A085_4A7A_B92A_F1C31162080A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WebPage.h"

class CXdHtmlView : public CHtmlView
{
protected: // create from serialization only
	CXdHtmlView();
	DECLARE_DYNCREATE(CXdHtmlView)

// Attributes
public:
	CXdHtmlDoc*		GetDocument();
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXdHtmlView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXdHtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXdHtmlView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonXd1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nTimer;
};

#ifndef _DEBUG  // debug version in XdHtmlView.cpp
inline CXdHtmlDoc* CXdHtmlView::GetDocument()
   { return (CXdHtmlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDHTMLVIEW_H__54D4F885_A085_4A7A_B92A_F1C31162080A__INCLUDED_)
