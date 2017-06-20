~~~c++
// BlFunction.h


#if !defined(BLF_H_BLFUNCTION_INCLUDED_)
#define BLF_H_BLFUNCTION_INCLUDED_

class CBlFunction
{
public:
	CBlFunction::CBlFunction()
	{
		strcpy(name,"unkown");
	}
    virtual	void CBlFunction::plShowInf(CDC *pDC,int x,int y)
	{
		pDC->TextOut(x,y,name);
	}
protected:
	char		name[16];

};

class CBlFViewMng: public CBlFunction
{
public:	
	CBlFViewMng::CBlFViewMng()
	{
		strcpy(name,"nameCBlFViewMng");
	}
	void CBlFViewMng::plShowInf(CDC *pDC,int x,int y)
	{
		pDC->TextOut(x,y,"nameCBlFViewMng inf");
		CBlFunction::plShowInf(pDC,x,y+20);
	}
};

#endif // !defined(BLF_H_BLFUNCTION_INCLUDED_)
~~~
