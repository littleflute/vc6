// XdHtml.h : main header file for the XDHTML application
//

#if !defined(AFX_XDHTML_H__DDFA8819_98FD_4E91_9AE6_F3F007DB3F11__INCLUDED_)
#define AFX_XDHTML_H__DDFA8819_98FD_4E91_9AE6_F3F007DB3F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlApp:
// See XdHtml.cpp for the implementation of this class
//

class CXdHtmlApp : public CWinApp
{
public:
	CXdHtmlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXdHtmlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXdHtmlApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDHTML_H__DDFA8819_98FD_4E91_9AE6_F3F007DB3F11__INCLUDED_)
