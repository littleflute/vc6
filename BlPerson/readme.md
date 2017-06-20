~~~c++
// File: BlPerson.h
#include "BlFunction.h"


#if !defined(BLF_H_BLPERSON_INCLUDED_)
#define BLF_H_BLPERSON_INCLUDED_

class CBlPerson
{
public:
	CBlPerson::CBlPerson(): m_blF(NULL)
	{

		strcpy(name,"unkown");
	}
	CBlPerson::CBlPerson(char *name): m_blF(NULL)
	{

		strcpy(this->name,name);
	}
	void CBlPerson::setFun(CBlFunction *f)
	{
		if(f) m_blF = f;
	}
	void CBlPerson::plShowInf(CDC *pDC,int x,int y)
	{
		int d = 20;
		pvShowText(pDC,"test:",x,y);
		pvShowText(pDC,name,x,y+d);
		if(m_blF)
		{
			m_blF->plShowInf(pDC,x,y+2*d);
		}
	} 
protected:
	char		name[16];
	char		birthday[16];
	int			age;
#include "BlFunction.h"
	CBlFunction		*m_blF;
private:
	void CBlPerson::pvShowText(CDC *pDC,char *s,int x,int y)
	{
		pDC->TextOut(x,y,s);
	}
};

#endif // !defined(BLF_H_BLPERSON_INCLUDED_)
~~~
