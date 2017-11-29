// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__1DA05FE9_DC2C_4DEC_8A7E_CC7FAC74885A__INCLUDED_)
#define AFX_STDAFX_H__1DA05FE9_DC2C_4DEC_8A7E_CC7FAC74885A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxhtml.h>			// MFC HTML view support

class CBlBase
{
public:
	CBlBase():m_pContext(NULL),m_strV("v0.0.4"),m_strName("BlBase"){}
	~CBlBase(){}
	bool pl2ParseString(CString s){ 
		if(-1 != s.Find("xd=Cancel")) {  	
			AfxMessageBox("vc6: CBlBase: xd=Cancel");
			return true;
		} 	
		if(-1 != s.Find("xd=xd3")) {  	
			AfxMessageBox("vc6: CBlBase: xd=xd3");
			return true;
		} 	
		if(-1 != s.Find("xd=get_win_app_v")) {  	
			AfxMessageBox(m_strName + " : " + m_strV);
			return true;
		} 	
		return false;
	}
	void plSetContext(void* p){m_pContext = p;}
	void plSetWindowText(char *sz){
		CWnd *pw = (CWnd*) m_pContext;
		pw->SetWindowText(sz);
	}
	void	*	m_pContext;
private:
	CString		m_strV;
	CString		m_strName;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1DA05FE9_DC2C_4DEC_8A7E_CC7FAC74885A__INCLUDED_)
