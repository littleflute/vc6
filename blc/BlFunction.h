// BlFunction.h v0.0.5


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

class CBl 
{
public:
	CBl ::CBl():d(20170622){
		strcpy(v,"0.0.1");
	}
	CBl::~CBl(){}
protected:
	int		d;

private:
	char v[16];
};

class CBlKlines : public CBl 
{
	typedef  struct _ohlc
	{
		float	o,h,l,c;
		int		ymd,hh,mm,ss;
	} OHLC,*POHLC;

public:
	CBlKlines ::CBlKlines():nA(0),x(10),y(10),w(300),h(300)
	{
		strcpy(v,"0.0.1");
		memset(&k,0,sizeof(OHLC));
		k.c = 1250.00;
		k.o = 1245.00;
	}

	CBlKlines::~CBlKlines(){}
	void CBlKlines::plSetNewSellData(float f,int ymd,int hh,int mm,int ss)
	{
		if(k.mm != mm)
		{
			if(0!=k.ymd)
			{	
				memcpy(&kA[nA],&k,sizeof(OHLC));
				nA++;
			}
			k.o = k.h = k.l = k.c = f;
		}
		else
		{
			k.c		= f;
			if(f>k.h) k.h = f;
			if(f<k.l) k.l = f;
		}
		k.ymd	= ymd;
		k.hh	= hh;
		k.mm	= mm;
		k.ss	= ss;
		
	}
	void CBlKlines::plSetXY(int x,int y)
	{
		this->x = x;
		this->y = y;
	}
	void CBlKlines::plShow(CDC *pDC)
	{
		pvDrawBkgnd(pDC);
		OHLC k1;
		k1.o = 1251.0;
		k1.c = 1258.0;
		k1.h = 1259.0;
		k1.l = 1245.0;
		pvDraw_1_K(pDC,x+350,y+10,k1);

		pvDraw_1_K(pDC,x+10,y+10,k);
		int x0 = 100;
		for(int i = 0; i < nA; i++){
			pvDraw_1_K(pDC,x0+x+i*15,y+i*50,kA[i]);
		}
	}
protected:
	OHLC	kA[1000],k;
	int		nA;


private:
	char	v[16];
	int		x,y,w,h;
	void pvDrawBkgnd(CDC *pDC)
	{
		CRect r(x,y,x+w,y+h);

		CBrush b(RGB(0,0,0));
		pDC->FillRect(&r,&b);
	}
	void pvDraw_1_K(CDC *pDC,int x,int y,OHLC &k)
	{
		int oY = pvF2Y(k.o);
		int cY = pvF2Y(k.c);
		int hY = pvF2Y(k.h);
		int lY = pvF2Y(k.l); 
		CBrush rB(RGB(255,0,0));
		CBrush gB(RGB(0,255,0));
		CBrush *pB = &gB;
		if(k.c>k.o)
		{
			pB = &rB;
		}
 
		{
			if(oY==cY) cY++;
			CRect rOC(x-5,oY,x+5,cY);
			pDC->FillRect(&rOC,pB);
		}
		{
			CRect rHL(x-1,hY,x+1,lY); 
			pDC->FillRect(&rHL,pB);
		}
	}	
	
	int pvF2Y(float f)
	{
		int y1		= this->y;
		int y2		= this->y + this->h;
		float fMax	= 1260.0;
		float fMin	= 1248.0;
		
		int i = y1 + (f-fMax)*(y2-y1)/(fMin-fMax);
		return i;
	}
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
	#include "BlThread.h"
	class CMyThread: public CThread
	{
		#define NEARLYINFINITE       6000
	public:
		CMyThread():m_bRunning(true){
			m_hDisplayOver = CreateEvent(NULL, FALSE , FALSE, NULL);
		}
		~CMyThread(){
			CloseHandle(m_hDisplayOver);
		}
		void plRun(void *p)
		{
			m_bRunning = true;
			pvCreate(pvMyFun,p);
		}
		void pl2Stop()
		{
			m_bRunning = false;
			WaitForSingleObject(m_hDisplayOver, NEARLYINFINITE);
		}

		bool plIsRunning()
		{
			return m_bRunning;
		}
	private:
		static DWORD WINAPI		CMyThread::pvMyFun(void *p1)
		{
			DWORD dwR = 0; 
			CBlFunWork*  pTest = (CBlFunWork*) p1;
		
			static n=300;
			static BYTE bt[300*300*3];
			int i=0;
			while(pTest->GetMyThread()->plIsRunning())
			{ 
				Sleep(1000);
				static int n = 0;
				n++;
				pTest->SetStr(n);
			} 
			SetEvent(pTest->GetMyThread()->m_hDisplayOver); 
			return dwR;
		}
	private:
		bool			m_bRunning;
		HANDLE			m_hDisplayOver; 
		
	};



public:	
	CBlFunWork::CBlFunWork():b(false) 
	{
		strcpy(name,"CBlFunWork");
		m_strHTML	= "";
		m_myThread.plRun(this);
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
				

				
			} 
			break;
		}
	}
	
	CMyThread* CBlFunWork::GetMyThread()
	{
			return &m_myThread;
	}
	void CBlFunWork::SetStr(int i)
	{
		CBlFunUrlData	d;
		CString str  = "http://api.baidao.com/api/hq/npdata.do?ids=201";
		BOOL b = d.plGetDataFromUrl(str); 
		if(b) 
		{
			CString &s = m_strHTML;
			float f = d.plGetSell();
			m_strHTML.Format("i=%d : sell: %.2f",i,f);

			s += "    ";
			CString strT = d.plGetTime();
			s += strT;
			s += "    ";
			s += d.plGetValue(13);
			
			int ymd,hh,mm,ss;
			sscanf(strT.GetBuffer(strT.GetLength()),"%d %d:%d:%d",&ymd,&hh,&mm,&ss);
		
			ks.plSetNewSellData(f,ymd,hh,mm,ss);
			this->b = !this->b;
		} 
		else
		{
			AfxMessageBox("fail to open website.");
		} 
		
	}
	void CBlFunWork::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                     int x,int y,int w,int h)
	{ 
		ptShowMe(pDC);


		pDC->TextOut(nPersonX,nPersonY,m_strHTML.GetBuffer(m_strHTML.GetLength()));
		
		ptDrawBlock(pDC,nPersonX,nPersonY,this->x,this->y);

		CRect r(this->x-10,this->y-10,this->x+10,this->y+10);
		if(b)
		{
			CBrush br(RGB(255,0,233));
			pDC->FillRect(&r,&br);
		}
		else
		{
			CBrush br(RGB(255,0,0));
			pDC->FillRect(&r,&br);
		}
		ks.plSetXY(this->x-this->r,this->y + this->r);
		ks.plShow(pDC);
 
	}
private:
	char		v[16];
	CString		m_strHTML;
	bool		b;  
	CMyThread	m_myThread;
	
	CBlKlines	ks;
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
	float CBlFunUrlData::plGetSell()
	{ 
		float f = 0.0;
		CString s = pvValue(11);
		sscanf(s.GetBuffer(s.GetLength()),"%f",&f);
		return f;
	}

	CString CBlFunUrlData::plGetTime()
	{ 
		CString s = pvValue(3);
		s = s.Right(s.GetLength()-1);
		s = s.Left(s.GetLength()-1);
		return s;
	}

	CString CBlFunUrlData::plGetValue(int n)
	{ 
		CString s = "";
		s = pvValue(n);
		return s;
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
	CString pvValue(int nNo)
	{
		CString strRet = "";
		CString s = this->plGetStrHtml();
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
					if(nIdx/2== nNo) 
					{
						strRet = w;
						return strRet;
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
		return strRet;
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