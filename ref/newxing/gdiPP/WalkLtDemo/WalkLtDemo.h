//Download by http://www.NewXing.com
// WalkLtDemo.h : main header file for the WALKLTDEMO application
//

#if !defined(AFX_WALKLTDEMO_H__826A807C_C01D_4FF0_9248_A6BD0369F3A8__INCLUDED_)
#define AFX_WALKLTDEMO_H__826A807C_C01D_4FF0_9248_A6BD0369F3A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

//加入gdi+支持
#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#endif

#include  "gdiplus.h"
using namespace Gdiplus;

#pragma comment(lib, "gdiplus.lib")


/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoApp:
// See WalkLtDemo.cpp for the implementation of this class
//

class CWalkLtDemoApp : public CWinApp
{
public:
	CWalkLtDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalkLtDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWalkLtDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALKLTDEMO_H__826A807C_C01D_4FF0_9248_A6BD0369F3A8__INCLUDED_)
