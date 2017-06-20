~~~c++
// BlFactory.h v0.0.2


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

		static CBlFViewMng		f1;
		f1.setFactory (this);
		if(pVM) pVM->setFun (&f1);
	
		pVM = pvGetPerson("zh3");
		static CBlFunWork		w1;
		w1.setFactory (this);
		if(pVM) pVM->setFun (&w1);
		
		pVM = pvGetPerson("li4");
		static CBlFunStudent s1(this);
		if(pVM)
		{
			pVM->setFun (&s1);
		}
	}
	void CBlFactory::plCmd(CDC *pDC,int x,int y,int w,int h)
	{
		CBlPerson *pVM = pvGetPerson("zh3");
		pVM->plMoveR(2,w);
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h);

		pVM = pvGetPerson("li4");
		pVM->plMoveD(2,h);
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h);
	}
    virtual	void CBlFactory::pl2Work(CDC *pDC,int x,int y,int w,int h)
	{ 
		CBlPerson *pVM = pvGetPerson("vm");
		if(pVM)	pVM->pl2ShowFun(pDC,x,y,w,h);
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
};
 
#endif // !defined(BLF_H_BLFACTORY_INCLUDED_)
~~~
