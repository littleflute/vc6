// XdHtmlView.cpp : implementation of the CXdHtmlView class
//

#include "stdafx.h"
#include "XdHtml.h"

#include "XdHtmlDoc.h"
#include "XdHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView

IMPLEMENT_DYNCREATE(CXdHtmlView, CHtmlView)

BEGIN_MESSAGE_MAP(CXdHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CXdHtmlView)
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTON_XD1, OnButtonXd1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView construction/destruction

CXdHtmlView::CXdHtmlView()
{
	// TODO: add construction code here
	m_nTimer = 0;
}

CXdHtmlView::~CXdHtmlView()
{
}

BOOL CXdHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}
 
/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView drawing

void CXdHtmlView::OnDraw(CDC* pDC)
{
	CXdHtmlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->Ellipse(100,100,500,500);
}

void CXdHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate(); 
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
//	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
//	Navigate2(_T("file:///C:/Users/13699/xd/index.html"),NULL,NULL);
	Navigate2(_T("file:///C:/Users/13699/xd1/baidu/VC6_EN/VC6_EN/VC6EN/MyProjects/XdHtml/index.html?l=xd1"),NULL,NULL);


	this->SetTimer(1,1000,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView printing


/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView diagnostics

#ifdef _DEBUG
void CXdHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CXdHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CXdHtmlDoc* CXdHtmlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXdHtmlDoc)));
	return (CXdHtmlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlView message handlers

void CXdHtmlView::OnBeforeNavigate2(LPCTSTR lpszURL, 
									DWORD nFlags, 
									LPCTSTR lpszTargetFrameName,
									CByteArray& baPostedData, 
									LPCTSTR lpszHeaders, 
									BOOL* pbCancel) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString s = lpszURL; 
	CBlBase blb;
	* pbCancel = blb.pl2ParseString(s);
 
	if(-1 != s.Find("xd=xd2")) {  	 
		xd_plv_create_xd2_html();
		* pbCancel = true;
	} 		 
		 
	if(-1 != s.Find("xd=save")) {  	 
		xd_plv_save();
		* pbCancel = true;
	} 
	if(-1 != s.Find("a=0")) {  			
		CString sURL = "file:///C:/Users/13699/xd/baidu/VC6_EN/VC6_EN/VC6EN/MyProjects/XdHtml/index.html?";
		CString s;
		s.Format("l=xd%d",m_nTimer);
		sURL += s;
		Navigate2(_T(sURL),NULL,NULL);
		* pbCancel = true;
	} 
	if(-1 != s.Find("a=2")) { 
		int a,x,y;
		int i = s.Find("a=2");
		CString sXY = s.Right(s.GetLength()-i);
		sscanf(sXY.GetBuffer(s.GetLength()),"a=%d&x=%d&y=%d",&a,&x,&y);
		CString sr;
		sr.Format("a = %d, [%d,%d]",a,x,y);  

		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		* pbCancel = true;
	} 
	if(-1 != s.Find("a=3")) { 
		int a,x,y;
		int i = s.Find("a=3");
		CString sXY = s.Right(s.GetLength()-i);
		sscanf(sXY.GetBuffer(s.GetLength()),"a=%d&x=%d&y=%d",&a,&x,&y);
		CString sr;
		sr.Format("a = %d, [%d,%d]",a,x,y); 
	//	AfxMessageBox(sr);
//		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, 0, 0, 0, 0);
//		GetCursorPos(&pt);
		SetCursorPos(x,y);

		* pbCancel = true;
	} 
	if(-1 != s.Find("a=4")) { 
		int x = 0;
		int y = 0;
		SetCursorPos(200,170);
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0); 
		SetCursorPos(350,170);
		mouse_event(MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE, x, y, 0, 0);

		* pbCancel = true;
	} 
	CHtmlView::OnBeforeNavigate2(lpszURL, nFlags,	lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

void CXdHtmlView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_nTimer++;
	POINT pt;
	GetCursorPos(&pt);

	CString sURL = "file:///C:/Users/13699/xd/baidu/VC6_EN/VC6_EN/VC6EN/MyProjects/XdHtml/index.html?";
		CString s;
		s.Format("l=xd%d_[%d_%d]",m_nTimer,pt.x,pt.y);
		sURL += s;
//		Navigate2(_T(sURL),NULL,NULL);
	
	CHtmlView::OnTimer(nIDEvent);
}

void CXdHtmlView::OnButtonXd1() 
{
	// TODO: Add your command handler code here
//	m_webPage.CallJScript("Welcome");
	
	CWebPage		m_webPage;
	CComPtr<IDispatch> spDisp = CHtmlView::GetHtmlDocument();
	m_webPage.SetDocument(spDisp);
	m_webPage.CallJScript("add","1","2");


	IDispatch *pHtml = GetHtmlDocument();
	IHTMLDocument2 *pHtmlDoc = NULL;
	IHTMLElement *pDiv = NULL;
 
}

void CXdHtmlView::xd_plv_save()
{ 
	CString strFileName = "";
	CString strFileTxt	= "";
	CComVariant	r;
	CWebPage		m_webPage;
	CComPtr<IDispatch> spDisp = CHtmlView::GetHtmlDocument();
	m_webPage.SetDocument(spDisp);

	//1. 
	if(!m_webPage.CallJScript("get_file_name","1","2",&r)) {
		AfxMessageBox("XXXX: [get_file_name] something is wrong!!!! ");
		return;
	}

	CString s; 
	WCHAR a[5555*2];
	::memset(a,0,sizeof(a));
	::memcpy(a,r.bstrVal,::SysStringByteLen(r.bstrVal)); 
	s = a; 
	strFileName = s; 

	//1a. 
	if(!m_webPage.CallJScript("get_file_length","1","2",&r)) {
		AfxMessageBox("XXXX: [get_file_length] something is wrong!!!! ");
		return;
	}
	CString sLength; 
	WCHAR rLength[1111*2];
	::memset(rLength,0,sizeof(rLength));
	::memcpy(rLength,r.bstrVal,::SysStringByteLen(r.bstrVal)); 
	sLength = rLength; 
	int nLength = 0;
	sscanf(sLength.GetBuffer(sLength.GetLength()),"%d",&nLength);


	
	
	//2. 

	if(!m_webPage.CallJScript("create_page","titleByVC6","BodyByVC6",&r)) {
		AfxMessageBox("XXXX: [create_page] something is wrong!!!! ");
		return;
	}
	
	WCHAR *pWC = new WCHAR [nLength];
	s = ""; 
	::memset(pWC,0,sizeof(pWC));
	::memcpy(pWC,r.bstrVal,::SysStringByteLen(r.bstrVal)); 
	s = pWC; 
	strFileTxt	= s; 

	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeWrite|CFile::modeCreate))
	{
		CString strError = strFileName + _T(" 文件打开失败。");
			::AfxMessageBox(strError);
			return;
	}	
	file.WriteString(strFileTxt);

	//3.
	CString strOK = strFileName + _T(" 文件 save ok。");
	m_webPage.CallJScript("show_msg",strOK.GetBuffer(strOK.GetLength()),"BodyByVC6",&r); 
	  
	delete []pWC;
				
}
void CXdHtmlView::xd_plv_create_xd2_html()
{
	CComVariant	r;
	CWebPage		m_webPage;
	CComPtr<IDispatch> spDisp = CHtmlView::GetHtmlDocument();
	m_webPage.SetDocument(spDisp);
	m_webPage.CallJScript("create_xd2_html","11","22",&r);
	CString s; 
	WCHAR a[2512*2];
	::memset(a,0,sizeof(a));
	::memcpy(a,r.bstrVal,::SysStringByteLen(r.bstrVal)); 
	s = a; 
	 
	CStdioFile file;
	if (!file.Open("xd2.html", CFile::modeWrite|CFile::modeCreate))
	{
			::AfxMessageBox(_T("文件打开失败。"));
			return;
	}	
	file.WriteString(s);
	::AfxMessageBox(_T("xd_plv_create_xd2_html ok!!!"));
				
}

void CXdHtmlView::BlHome()
{
	OnInitialUpdate();
}
