// BlFactory.h v0.0.4


#if !defined(BLF_H_BLFACTORY_INCLUDED_)
#define BLF_H_BLFACTORY_INCLUDED_
 
class CBlFactory
{
#include "BlPerson.h"
public:
	CBlFactory::CBlFactory(): m_nAll(0)
	{
		strcpy(name,"unkown");
		pvRegistor("vm");
		pvRegistor("zh3");
		pvRegistor("li4");

		CBlPerson *pVM = pvGetPerson("vm");

		f1.plSetFactory (this);
		if(pVM) pVM->setFun (&f1,100,200,50,10);
	
		pVM = pvGetPerson("zh3");
		w1.plSetFactory (this);
		if(pVM)
		{
			pVM->plMoveR(300,800);
			pVM->plMoveD(100,500);
			pVM->setFun (&w1,450,80,60,12);
		}
		
		pVM = pvGetPerson("li4");
		s1.plSetFactory(this);
		if(pVM)
		{
			pVM->plMoveR(350,500);
			pVM->plMoveD(180,500);
			pVM->setFun (&s1,55,60,70,13);
		}
	}
 
	void CBlFactory::plCmd(CDC *pDC,int x,int y,int w,int h)
	{
		CBlPerson *pVM = pvGetPerson("zh3");	
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h,true);

		pVM = pvGetPerson("li4");	
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h,true);
	}

    virtual	void CBlFactory::pl_WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{ 
		
		switch(m)
		{
		case WM_LBUTTONDOWN: 
		//	AfxMessageBox("xd");
			break;
		}

		CBlPerson *pVM = pvGetPerson("li4");	
		if(pVM)	pVM->pl2WM(h,m,w,l);

		pVM = pvGetPerson("zh3");	
		if(pVM)	pVM->pl2WM(h,m,w,l);
	}

    virtual	void CBlFactory::pl_Work(CDC *pDC,int x,int y,int w,int h)
	{ 
		CBlPerson *pVM = pvGetPerson("vm");
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h,false);
	}
protected:
	char			name[16];
	CBlPerson		m_All[250]; 
	int				m_nAll;
private:
	void CBlFactory::pvRegistor(char *name)
	{
		m_All[m_nAll].setName(name);
		m_nAll++;
		m_All[m_nAll].setFactory(this);
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