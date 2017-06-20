~~~c++
// BlFunction.h v0.0.2


#if !defined(BLF_H_BLFUNCTION_INCLUDED_)
#define BLF_H_BLFUNCTION_INCLUDED_

class CBlFunction
{
public:
	CBlFunction::CBlFunction()
	{
		strcpy(name,"unkown");
	}
	void CBlFunction::setFactory( CBlFactory *f)
	{
		m_blFactory = f;
	}
    virtual	void CBlFunction::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                             int x,int y,int w,int h)
	{
		pDC->TextOut(x,y,name);
	}
protected:
	char		name[16];
	CBlFactory	*m_blFactory;

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
	}
	void CBlFunWork::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                     int x,int y,int w,int h)
	{ 
		pDC->TextOut(nPersonX,nPersonY,"CBlFunWork::pl2Do test");
	}
private:
	 
};

class CBlFunStudent: public CBlFunction
{
public:	
	CBlFunStudent::CBlFunStudent(CBlFactory *f)
	{
		strcpy(name,"CBlFunWork");
		m_blFactory = f;
	}
	void CBlFunStudent::pl2Do(CDC *pDC,int nPersonX,int nPersonY,
		                     int x,int y,int w,int h)
	{ 
		pDC->TextOut(nPersonX,nPersonY,"CBlFunStudent::pl2Do test");
	}
private:
	 
};
#endif // !defined(BLF_H_BLFUNCTION_INCLUDED_)
~~~
