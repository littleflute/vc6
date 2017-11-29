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
		//ȥ��"http://"
		CString strTemp=strUrl.Mid(7);
		
		//���������·��
		int nSlash=strTemp.Find("/");
		if (nSlash!=-1)  //�����-1������û�ҵ�
		{
			m_strServer=strTemp.Left(nSlash);//ȡ��/����ߵķ�������ַ
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
		//�жϵ�ַ�Ƿ���Ч,��Ϊ�ջ�ͷ7���ַ����ǡ�http://"
		if(strUrl.IsEmpty()||strUrl.Left(7)!="http://")
		{
			AfxMessageBox("Sorry,It is a invalid address!");
			bRet = FALSE;
			goto EXIT;
		}
		//������ַ���õ�server���ֺ��ļ�·��
		fn_ParseURL(strUrl);
		//��һ��:��ʼ��internet DLL,���ǵ�һ�������õĺ���
		HINTERNET hSession;
		hSession = ::InternetOpen("Raw HTML Reader",PRE_CONFIG_INTERNET_ACCESS,
			"",INTERNET_INVALID_PORT_NUMBER,0);
		
		//�жϻỰ����Ƿ���Ч
		if(hSession==NULL)
		{
			AfxMessageBox("Internet session initalization failed!");
			bRet = FALSE;
			goto EXIT;
		}
		//�ڶ�������ʼ��HTTP session
		HINTERNET	hConnect;
		hConnect = ::InternetConnect(hSession,//��ǰinternet�Ự���
			m_strServer,//server name
			INTERNET_INVALID_PORT_NUMBER,
			NULL,//"",//user name
			"",//password
			INTERNET_SERVICE_HTTP,//Type of service to access
			0,
			0);
		//�ж����Ӿ���Ƿ���Ч
		if(hConnect==NULL)
		{
			AfxMessageBox("Internet connect initalization failed!");
			//�رջỰ���
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		//����������һ��HTTP������
		HINTERNET hHttpFile;
		hHttpFile = ::HttpOpenRequest(hConnect,
										  "GET",
										  m_strPath,
										  HTTP_VERSION,
										  NULL,
										  0,
										  INTERNET_FLAG_DONT_CACHE,
										  0);
		//�ж����Ӿ���Ƿ���Ч
		//�жϻỰ����Ƿ���Ч
		if(hHttpFile==NULL)
		{
			AfxMessageBox("Http request failed!");
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		
		
		//���Ĳ�����������
		BOOL bSendRequest;
		bSendRequest = ::HttpSendRequest(hHttpFile,
									   NULL,
									   0,
									   0,
									   0);
		if(bSendRequest)
		{
			//�õ��ļ��Ĵ�С
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
				//���ҳɹ���ָ����Ҫ����ļ����ڴ��С???????
				dwFileSize=(DWORD)atol(achQueryBuf);
			}
			else
			{
				//ʧ�ܣ��³�һ������ļ���
				return false;
				dwFileSize=10*1024;
			}
			
			//����һ�����������ļ�����
			//	 m_lpszBufRawHtml=new char[dwFileSize+1];
			fn_MyNewBuf(dwFileSize);
			//���ļ�
			DWORD dwBytesRead;
			BOOL bRead = ::InternetReadFile(hHttpFile,
				m_lpszBufRawHtml,
				dwFileSize+1,
				&dwBytesRead);
			
			// �ر�INTERNET���
			VERIFY(::InternetCloseHandle(hHttpFile));
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
		}
		else{
			bRet = FALSE; //���粻ͨ
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
