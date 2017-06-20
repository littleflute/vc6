~~~
// File: BlPerson.h v0.0.2

#include "BlFunction.h"


#if !defined(BLF_H_BLPERSON_INCLUDED_)
#define BLF_H_BLPERSON_INCLUDED_

class CBlPerson
{
public:
	CBlPerson::CBlPerson(): m_blFun(NULL),m_blFatory(NULL),x(0),y(0)
	{

		strcpy(name,"unkown");
	}
	CBlPerson::CBlPerson(char *name): m_blFun(NULL),x(0),y(0)
	{

		strcpy(this->name,name);
	}
	void CBlPerson::setName(char *name)
	{
		strcpy(this->name,name);
	
	}
	void CBlPerson::setFactory( CBlFactory *f)
	{
		m_blFatory = f;
	}
	void CBlPerson::setFun(CBlFunction *f)
	{
		if(f) 
		{
			m_blFun = f;
		}
	}
	char * CBlPerson::plGetName()
	{
		return name;
	}
	void CBlPerson::plMoveR(int nM,int w)
	{
		x += nM;
		if (x > w) x = 0;
	}
	void CBlPerson::plMoveD(int nM,int h)
	{
		y += nM;
		if (y > h) y = 0;
	}
	void CBlPerson::plCmd(CDC *pDC,int x,int y,int w,int h)
	{
		int &nX = this->x;
		int &nY = this->y;
		nX += 1;
		if(nX>x+w) nX = 0;
		pDC->TextOut(nX,nY,name);
	}
	void CBlPerson::pl2ShowFun(CDC *pDC,int x,int y,int w,int h)
	{ 
		if(m_blFun)
		{
			m_blFun->pl2Do(pDC,this->x,this->y,x,y,w,h);
		} 
	} 
protected:
	char		name[16];
	char		birthday[16];
	int			age;
	int			x,y;
#include "BlFunction.h"
	CBlFunction		*m_blFun;
	CBlFactory		*m_blFatory;
private:
	void CBlPerson::pvShowText(CDC *pDC,char *s,int x,int y)
	{
		pDC->TextOut(x,y,s);
	}
};

#endif // !defined(BLF_H_BLPERSON_INCLUDED_)

~~~
