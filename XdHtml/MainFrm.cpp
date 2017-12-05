// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "XdHtml.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_nTimerNum = 0;
	m_blSon.plSetContext(this);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);
	
	pvSetHotKey();

//	this->SetTimer(1,100,NULL);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.hMenu = NULL;
	

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	pvHotKey(message,wParam,lParam);
	switch(message)
	{
	case WM_LBUTTONDOWN:
		break;
	}
	return CFrameWnd::DefWindowProc(message, wParam, lParam);
}
#include "XdHtmlView.h"
void CMainFrame::pvHotKey(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(WM_HOTKEY!=message) return;
	CString s;
	s.Format(" %d w = %d",LOWORD(lParam),wParam);
	switch(wParam)
	{
	case 1:	
		{ 
			CString s;
			GetWindowText(s);
			AfxMessageBox("a:" + s);
		}
		break;
	case 2:		
		AfxMessageBox("b");
		break; 
	case 48:		 
		CXdHtmlView *pv = (CXdHtmlView *) this->GetActiveView();
		pv->BlHome();
		break;
	}


}

void CMainFrame::pvSetHotKey()
{
//	if (RegisterHotKey(        m_hWnd,        1,        MOD_CONTROL,  0x41))  //0x41 is 'a'
    { 
    } 

	if (RegisterHotKey( m_hWnd,        2,        MOD_CONTROL,       0x42))  //0x42 is 'b'
    { 
    } 
	if (RegisterHotKey(        m_hWnd,        48,        MOD_CONTROL,        0x48))  //0x48 is 'h'
    { 
    } 


}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CFrameWnd::ActivateFrame(nCmdShow);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
	SetWindowText("xd title 1");
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
	SetWindowText("xd title: OnActivate");
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
	SetWindowText("xd title: OnShowWindow");
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_nTimerNum++;
	char sz[256];
	sprintf(sz,"blson test: %d",m_nTimerNum);
	m_blSon.plSetWindowText(sz); 

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	this->KillTimer(1);
}
