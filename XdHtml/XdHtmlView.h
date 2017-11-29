// XdHtmlView.h : interface of the CXdHtmlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDHTMLVIEW_H__54D4F885_A085_4A7A_B92A_F1C31162080A__INCLUDED_)
#define AFX_XDHTMLVIEW_H__54D4F885_A085_4A7A_B92A_F1C31162080A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "XdHtmlDoc.h"
#include "wininet.h"
#include "WebPage.h"

class CBlHTML
{
public: 
	CString CBlHTML::plGetStrHtml()
	{
		CString strRet;
		strRet.Format("%s",m_lpszBufRawHtml);
		return strRet;	
	}
	
	void CBlHTML::fn_MyNewBuf(DWORD dwSize)
	{
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
		m_lpszBufRawHtml=new char[dwSize+1];
		memset(m_lpszBufRawHtml,0,dwSize+1);
	}
	
	void CBlHTML::fn_ParseURL(CString &strUrl)
	{
		if(strUrl.IsEmpty())
		{
			return;
		}
		//去掉"http://"
		CString strTemp=strUrl.Mid(7);
		
		//检查主机的路径
		int nSlash=strTemp.Find("/");
		if (nSlash!=-1)  //如等于-1，就是没找到
		{
			m_strServer=strTemp.Left(nSlash);//取‘/’左边的服务器地址
			m_strPath=strTemp.Mid(nSlash);
		}
		else
			m_strServer=strTemp;
		
		
	}

	bool fn_From_URL(CString str)
	{
		m_lpszBufRawHtml=NULL;
		bool bRet = TRUE;
		CString strUrl = str;
		//判断地址是否有效,如为空或开头7个字符不是“http://"
		if(strUrl.IsEmpty()||strUrl.Left(7)!="http://")
		{
			AfxMessageBox("Sorry,It is a invalid address!");
			bRet = FALSE;
			goto EXIT;
		}
		//解析地址，得到server名字和文件路径
		fn_ParseURL(strUrl);
		//第一步:初始化internet DLL,这是第一个被调用的函数
		HINTERNET hSession;
		hSession = ::InternetOpen("Raw HTML Reader",PRE_CONFIG_INTERNET_ACCESS,
			"",INTERNET_INVALID_PORT_NUMBER,0);
		
		//判断会话句柄是否有效
		if(hSession==NULL)
		{
			AfxMessageBox("Internet session initalization failed!");
			bRet = FALSE;
			goto EXIT;
		}
		//第二步：初始化HTTP session
		HINTERNET	hConnect;
		hConnect = ::InternetConnect(hSession,//当前internet会话句柄
			m_strServer,//server name
			INTERNET_INVALID_PORT_NUMBER,
			NULL,//"",//user name
			"",//password
			INTERNET_SERVICE_HTTP,//Type of service to access
			0,
			0);
		//判断连接句柄是否有效
		if(hConnect==NULL)
		{
			AfxMessageBox("Internet connect initalization failed!");
			//关闭会话句柄
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		//第三步：打开一个HTTP请求句柄
		HINTERNET hHttpFile;
		hHttpFile = ::HttpOpenRequest(hConnect,
										  "GET",
										  m_strPath,
										  HTTP_VERSION,
										  NULL,
										  0,
										  INTERNET_FLAG_DONT_CACHE,
										  0);
		//判断连接句柄是否有效
		//判断会话句柄是否有效
		if(hHttpFile==NULL)
		{
			AfxMessageBox("Http request failed!");
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		
		
		//第四步：发出请求
		BOOL bSendRequest;
		bSendRequest = ::HttpSendRequest(hHttpFile,
									   NULL,
									   0,
									   0,
									   0);
		if(bSendRequest)
		{
			//得到文件的大小
			char achQueryBuf[16];
			DWORD dwFileSize;
			DWORD dwQueryBufLen=sizeof(achQueryBuf);
			BOOL bQuery=::HttpQueryInfo(hHttpFile,
				HTTP_QUERY_CONTENT_LENGTH,
				achQueryBuf,
				&dwQueryBufLen,
				NULL);
			if(bQuery)
			{
				//查找成功，指出需要存放文件的内存大小???????
				dwFileSize=(DWORD)atol(achQueryBuf);
			}
			else
			{
				//失败，猜出一个最大文件数
				return false;
				dwFileSize=10*1024;
			}
			
			//分配一个缓冲区给文件数据
			//	 m_lpszBufRawHtml=new char[dwFileSize+1];
			fn_MyNewBuf(dwFileSize);
			//读文件
			DWORD dwBytesRead;
			BOOL bRead = ::InternetReadFile(hHttpFile,
				m_lpszBufRawHtml,
				dwFileSize+1,
				&dwBytesRead);
			
			// 关闭INTERNET句柄
			VERIFY(::InternetCloseHandle(hHttpFile));
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
		}
		else{
			bRet = FALSE; //网络不通
		}
		
EXIT:
		return bRet;
}
	CBlHTML()
	{ 
		m_lpszBufRawHtml = NULL;
	}

	virtual		~CBlHTML()
	{ 
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
	}
private:
	char		*m_lpszBufRawHtml;
	
	CString		m_strServer;
	CString		m_strPath;
	int			nLine;
	void vv_Fun_Fine_All(){};
	static UINT  v_Thread_Fun_FineAll(LPVOID pParam){};
};
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
	void BlHome();
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
	void xd_plvCallJSFun();
	void xd_plv_create_xd2_html();
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
