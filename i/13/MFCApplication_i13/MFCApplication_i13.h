
// MFCApplication_i13.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplicationi13App:
// See MFCApplication_i13.cpp for the implementation of this class
//

class CMFCApplicationi13App : public CWinApp
{
public:
	CMFCApplicationi13App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplicationi13App theApp;
