// BlFunction.h v0.0.4


#if !defined(BLF_H_BLFUNCTION_INCLUDED_)
#define BLF_H_BLFUNCTION_INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif


#define	MAXSIZE		1000
class CBlFunStack 
{
public:
	CBlFunStack ::CBlFunStack (){}
	CBlFunStack ::~CBlFunStack (){}
	void CBlFunStack::_plParse(CString &s)
	{
		int n = s.GetLength();
		char *sz = s.GetBuffer(n);
		char cWBegin = '"';
		char cWEnd = '"';
		bool b1 = false;
		char w[100] = {0};
		int nW = 0;
		int nIdx = 0;
		printf("n = %d\n",n);
		

		for(int i=0; i<n;i++)
		{
			if(false==b1)
			{
				if(sz[i]==cWBegin)
				{
					b1 = true;
				//	printf("[ \n");
				}
				else
				{
				//	printf("pass \n");
				}
			}
			else
			{
				if(sz[i]==cWEnd)
				{
					nIdx++;
					if(1==nIdx%2)
					{
						cWBegin = ':';
						cWEnd	= ',';
					}
					else
					{
						cWBegin = '"';
						cWEnd	= '"';
					}
					
				//	printf("] \n");
					float f = -1.0;
					sscanf(w,"%f",&f);
					if(-1.0==f)
					{
						printf("nIdx = %d %s  \n",nIdx,w);
					}
					else
					{
						printf("nIdx = %d %s    f = %.2f \n",nIdx,w,f);
					}
					memset(w,0,100);
					nW = 0;
					b1 = false;

				}
				else
				{
					w[nW++] = sz[i];
			//		printf("push %c \n",sz[i]);
				}
			}
		}
		
		printf("parse: s= %s\n",sz);
	}
private:
	int isempty() {
		
		if(top == -1)
			return 1;
		else
			return 0;
	}
	
	int isfull() {
		
		if(top == MAXSIZE)
			return 1;
		else
			return 0;
	}
	
	int peek() {
		return stack[top];
	}
	
	int pop() {
		int data;
		
		if(!isempty()) {
			data = stack[top];
			top = top - 1;   
			return data;
		} else {
			printf("Could not retrieve data, Stack is empty.\n");
			return -1;
		}
	}
	
	void push(int data) {
		
		if(!isfull()) {
			top = top + 1;   
			stack[top] = data;
		} else {
			printf("Could not insert data, Stack is full.\n");
		}
	}
protected:
private:
	char v[16]; 
	int stack[MAXSIZE];     
	int top;  
	
};


class CBlFunction
{
public:
	CBlFunction::CBlFunction():x(0),y(0),r(50),d(10),rB(5)
	{
		strcpy(name,"unkown");
	}
	void CBlFunction::plSetInfo(int x,int y,int r,int d)
	{
		this->x = x;
		this->y = y;
		this->r = r;
		this->d = d;
	}
	void CBlFunction::plSetFactory( CBlFactory *f)
	{
		m_blFactory = f;
	}
    virtual	void CBlFunction::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                             int x,int y,int w,int h)
	{
		pDC->TextOut(x,y,name);
	}
    virtual	void CBlFunction::pl2WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{   
		switch(m)
		{
		case WM_LBUTTONDOWN:			
			this->x += 100;
			AfxMessageBox("xd");
			break;
		}

	}

protected:
	char		name[16];
	CBlFactory	*m_blFactory;
	int			x,y,r,d;
	int			xB,yB,rB;
	
	 void ptDrawBlock(CDC *pDC,float x1,float y1,float x2,float y2)
	 {
		 rB++;
		 float r0 = pvR0(x1,y1,x2,y2);
		 if(rB>r0) rB = 0;
		 xB = pvF(r0,rB,x1,x2);
		 yB = pvF(r0,rB,y1,y2);
		 int d = this->d/2;
		 pDC->MoveTo(x1,y1);
		 pDC->LineTo(x2,y2);
		 pDC->Rectangle(xB-d,yB-d,xB+d,yB+d);
	 }

	int CBlFunction::ptPointInMe(int i,int j)
	{
		int nRet = 0;
		
		if( i>x-r	&& // 1 Left
			i<x-r+d &&
			j>y-r+d	&&
			j<y+r-d)
		{
			x -= d;

			nRet = 1;
		}
        else if( i>x-r+d	&& // 2 Up
			i<x+r-d &&
			j>y-r	&&
			j<y-r+d)
		{
			y -= d;

			nRet = 2;
		}
		else if( i>x+r-d && // 3 Right
			i<x+r	&&
			j>y-r+d &&
			j<y+r-d)
		{
			x += d;

			nRet = 3;
		}
		else if( i>x-r+d && // 4 Down
			i<x+r-d	&&
			j>y+r-d &&
			j<y+r)
		{
			y += d;

			nRet = 4;
		}
		else if( i>x-r	&& // 5 Left Down
			i<x-r+d	&&
			j>y+r-d &&
			j<y+r)
		{
			y += d;
			x -= d;

			nRet = 4;
		}
		else if( i>x-r	&& // 6 Left Up
			i<x-r+d	&&
			j>y-r   &&
			j<y-r+d)
		{
			y -= d;
			x -= d;

			nRet = 4;
		}
		else if( i>x+r-d && // 7 Right Up 
			i<x+r	&&
			j>y-r	&&
			j<y-r+d)
		{
			y -= d;
			x += d;

			nRet = 4;
		}
		else if( i>x+r-d && // 8 Right Down
			i<x+r	&&
			j>y+r-d &&
			j<y+r)
		{
			y += d;
			x += d;

			nRet = 4;
		}
		else if( i>x-r+d && // 9 Center
			i<x+r-d	&&
			j>y-r+d &&
			j<y+r-d)
		{ 
			nRet = 9;
		}

		return nRet;
	}
	void CBlFunction::ptShowMe(CDC *pDC)
	{ 
		int x1	= this->x - r;
		int y1	= this->y - r;
		int x2	= this->x + r;
		int y2	= this->y + r;

		pDC->Rectangle(x1,y1,x2,y2);
		pDC->Rectangle(x1+d,y1+d,x2-d,y2-d);
		pDC->Rectangle(x1,y2,x1+d,y2-d);	//Left Down
		pDC->Rectangle(x1,y1,x1+d,y1+d);	//Left Up
		pDC->Rectangle(x2-d,y1,x2,y1+d);	//Right Up
		pDC->Rectangle(x2-d,y2-d,x2,y2);	//Right Down
		pDC->TextOut(x-r/2,y,name);
	}
private:
	float pvF(float r0,float r,float x1,float x2)
	 {
		 float f = r*(x2-x1)/r0 + x1;
		 return f;
	 }
	 float pvR0(float x1,float y1,float x2,float y2)
	 {
		 float f = (float)sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
		 return f;
	 }
};

class CBlFViewMng: public CBlFunction
{
public:	
	CBlFViewMng::CBlFViewMng()
	{
		strcpy(name,"nameCBlFViewMng");
	}
	void CBlFViewMng::pl2Do(CDC *pDC,int nPersonX, int nPersonY,
		                     int x,int y,int w,int h)
	{
		pvDrawFromMem(pDC,x,y,w,h); 
	}
private:
	void pvDrawFromMem(CDC *pDC,int x1,int y1,int x2,int y2)
	{
		static int n = 0;
		n++;

		CRect rect(x1,y1,x2,y2); 
		int w = rect.Width();
		int h = rect.Height();
		CDC dcMem;
	    if(!dcMem.CreateCompatibleDC (pDC))
		    return;
	    CBitmap cBmp;
		if(!cBmp.CreateCompatibleBitmap(pDC,w,h)) return; 
	    dcMem.SelectObject (&cBmp); 

		CBrush b(RGB(80,80,220));
		CRect r(x1,y1,x2,y2);
		dcMem.FillRect(&r,&b);

		
		dcMem.Rectangle(110,110,500,500);

		CString str;
		str.Format("draw times = %d",n);
		dcMem.TextOut(111,100,str);  
		
		m_blFactory->plCmd(&dcMem,x1,y1,w,h);

	    pDC->BitBlt (0,0,w,h,&dcMem,0,0,SRCCOPY);

	}
};

class CBlFunWork: public CBlFunction
{
public:	
	CBlFunWork::CBlFunWork()
	{
		strcpy(name,"CBlFunWork");
		m_strHTML	= "";
	}
    void CBlFunWork::pl2WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{   
		switch(m)
		{
		case WM_LBUTTONDOWN:			
			int i = (int)(short)LOWORD(l);
			int j = (int)(short)HIWORD(l);
			int r = ptPointInMe(i,j);
			if(9==r)
			{
				CBlFunUrlData	d;
				CString str  = "http://api.baidao.com/api/hq/npdata.do?ids=201";
				BOOL b = d.plGetDataFromUrl(str); 
				if(b) 
				{
					m_strHTML = d.plGetStrHtml();
					s._plParse(m_strHTML);
				} 
			} 
			break;
		}
	}
	void CBlFunWork::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                     int x,int y,int w,int h)
	{ 
		ptShowMe(pDC);


		pDC->TextOut(nPersonX,nPersonY,m_strHTML.GetBuffer(m_strHTML.GetLength()));
		
		ptDrawBlock(pDC,nPersonX,nPersonY,this->x,this->y);
 
	}
private:
	 char		v[16];
	 CString	m_strHTML;
	 
	 CBlFunStack	s;
};

class CBlFunStudent: public CBlFunction
{
	
public:	
	CBlFunStudent::CBlFunStudent()
	{
		strcpy(name,"CBlFunStudent"); 
	}
	
    void CBlFunStudent::pl2WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{   
		switch(m)
		{
		case WM_LBUTTONDOWN:			
			{
				int i = (int)(short)LOWORD(l);
				int j = (int)(short)HIWORD(l);
				if(ptPointInMe(i,j))
				{ 
				}
			}
			break;
		case WM_TIMER:
			if(2==w)
			{
				CBlFunUrlData	d;
				CString str  = "http://api.baidao.com/api/hq/npdata.do?ids=201";
				BOOL b = d.plGetDataFromUrl(str); 
				if(b) 
				{
					m_strHTML = d.plGetStrHtml();					
				}
			}
			break;
		} 
	}
	void CBlFunStudent::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                     int x,int y,int w,int h)
	{  

		ptShowMe(pDC);

		pDC->TextOut(this->x,this->y,m_strHTML.GetBuffer(m_strHTML.GetLength()));
		
		ptDrawBlock(pDC,nPersonX,nPersonY,this->x,this->y);
	
	}
private:
	 CString		m_strHTML;
};

//*

class CBlFunUrlData  
{
public:  
	CBlFunUrlData()
	{ 
		m_lpszBufRawHtml = NULL;
	}
	
	virtual		~CBlFunUrlData()
	{ 
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
	}

	CString CBlFunUrlData::plGetStrHtml()
	{
		CString strRet;
		strRet.Format("%s",m_lpszBufRawHtml);
		return strRet;	
	}
	
	
	
	bool plGetDataFromUrl(CString str)
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
		pvParseURL(strUrl);
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
			pvMyNewBuf(dwFileSize);
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
	char		*m_lpszBufRawHtml;
	
	CString		m_strServer;
	CString		m_strPath;
	int			nLine;
	int			(*p_Ball)[9];
private: 
	
	void pvMyNewBuf(DWORD dwSize)
	{
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
		m_lpszBufRawHtml=new char[dwSize+1];
		memset(m_lpszBufRawHtml,0,dwSize+1);
	}
	
	void pvParseURL(CString &strUrl)
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
	
};

//*/

#endif // !defined(BLF_H_BLFUNCTION_INCLUDED_)