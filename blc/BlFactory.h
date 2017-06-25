// BlFactory.h v0.0.5


#if !defined(BLF_H_BLFACTORY_INCLUDED_)
#define BLF_H_BLFACTORY_INCLUDED_
 
class CBlFactory
{
#include "BlFunction.h"

	class CBlFViewMng: public CBlFunction
	{
	public:	
		CBlFViewMng::CBlFViewMng()
		{
			strcpy(name,"nameCBlFViewMng");
		}
		CBlFViewMng::~CBlFViewMng()
		{ 

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
			
			CBrush b(RGB(80,180,220));
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

#include "BlPerson.h"
public:
	CBlFactory::CBlFactory(): m_nAll(0)
	{
		strcpy(name,"unkown"); 

		CBlPerson *pVM = pvGetPerson("vm");

		f1.plSetFactory (this);
		if(pVM) pVM->plSetFun (&f1,100,200,50,10);
	 
		pVM = pvGetPerson("li4");
		s1.plSetFactory(this);
		if(pVM)
		{
			pVM->plMoveR(350,500);
			pVM->plMoveD(180,500);
			pVM->plSetFun (&s1,55,60,70,13);
		}
		 
	}
	CBlFactory::~CBlFactory()
	{
	}
 
	void CBlFactory::plAddPerson(char *name)
	{
		m_All[m_nAll].plSetName(name);
		m_All[m_nAll].plSetFactory(this);
		m_All[m_nAll].plMoveD(50*m_nAll,500);
		m_nAll++;
		m_All[m_nAll].plSetFun (&w1,30*m_nAll,80,60,12);

	}
	void CBlFactory::plCmd(CDC *pDC,int x,int y,int w,int h)
	{
		CBlPerson *pVM = pvGetPerson("zh3");	
		if(pVM)	pVM->pl2Show(pDC,x,y,w,h,true);

		pVM = pvGetPerson("li4");	
		if(pVM)	pVM->pl2Show(pDC,x,y,w,h,true);

	}

    virtual	void CBlFactory::pl_WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{ 	
		switch(m)
		{
		case WM_LBUTTONDOWN:  
			break; 
		} 
		for(int i=0;i<m_nAll;i++)
		{
			m_All[i].pl2WM(h,m,w,l);
		}
	}

    virtual	void CBlFactory::pl_Draw(CDC *pDC,int x,int y,int w,int h)
	{ 
		/*
		CBlPerson *pVM = pvGetPerson("vm");
		if(pVM)	pVM->pl2Show(pDC,x,y,w,h,false);
		//*/ 
		pvDraw(pDC,x,y,w,h);
	} 
protected:
	char			name[16];
	CBlPerson		m_All[250]; 
	int				m_nAll; 
private:
	//
	void pvDrawFactory(CDC *pDC,int x1,int y1,int x2,int y2)
	{
		pDC->TextOut(x1,y1,name);
	}
	void pvDrawAllPerson(CDC *pDC,int x1,int y1,int x2,int y2)
	{
		for(int i=0;i<m_nAll;i++)
		{
			m_All[i].pl2Show(pDC,x1,y1,x2-x1,y2-y1,true);
		}
	}
	void pvDraw(CDC *pDC,int x1,int y1,int x2,int y2)
	{
		CRect rect(x1,y1,x2,y2); 
		int w = rect.Width();
		int h = rect.Height();
		CDC dcMem;
		if(!dcMem.CreateCompatibleDC (pDC))
			return;
		CBitmap cBmp;
		if(!cBmp.CreateCompatibleBitmap(pDC,w,h)) return; 
		dcMem.SelectObject (&cBmp); 
		
		pvDrawFactory(&dcMem,x1,y1,x2,y2);
		pvDrawAllPerson(&dcMem,x1,y1,x2,y2); 
		
		pDC->BitBlt (0,0,w,h,&dcMem,0,0,SRCCOPY);
	} 
		
	CBlPerson * CBlFactory::pvGetPerson(char *name)
	{
		CBlPerson *pRet = NULL;
		for (int i = 0; i < m_nAll; i++)
		{
			if(0==strcmp(name,m_All[i].plGetName()))
			{
				pRet = &m_All[i];
			}
		}
		return pRet;
	}
	
	CBlFViewMng		f1;
	CBlFunWork		w1;
	CBlFunStudent	s1;
};
 
#endif // !defined(BLF_H_BLFACTORY_INCLUDED_)