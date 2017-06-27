// File: BlPerson.h v0.0.7

#include "BlFunction.h"


#if !defined(BLF_H_BLPERSON_INCLUDED_)
#define BLF_H_BLPERSON_INCLUDED_

class CBlPerson: public CBl
{
public:
	CBlPerson::CBlPerson(): m_blFun(NULL),m_blFatory(NULL) 
	{

		strcpy(name,"unkown");
	}
	CBlPerson::CBlPerson(char *name): m_blFun(NULL) 
	{

		strcpy(this->name,name);
	}
	void CBlPerson::plSetName(char *name)
	{
		strcpy(this->name,name);
	
	}
	void CBlPerson::plSetFactory( CBlFactory *f)
	{
		m_blFatory = f;
	}
	void CBlPerson::plSetFun(CBlFunction *f,int x,int y,int r,int d)
	{
		if(f) 
		{
			m_blFun = f;
			f->plSetInfo(x,y,r,d);
		}
	}
	char * CBlPerson::plGetName()
	{
		return name;
	}
	void CBlPerson::plMoveR(int nM,int w)
	{
		m_nX += nM;
		if (m_nX > w) m_nX = 0;
	}
	void CBlPerson::plMoveD(int nM,int h)
	{
		m_nY += nM;
		if (m_nY > h) m_nY = 0;
	}

    virtual	void CBlPerson::pl2WM(HWND h,UINT m,WPARAM w,LPARAM l)
	{   
		pvWM(h,m,w,l);

		if(m_blFun)
		{
			m_blFun->pl2WM(h,m,w,l);
		}
	}

	void CBlPerson::pl2Show(CDC *pDC,int x,int y,int w,int h,bool bShowMe)
	{ 
		if(bShowMe)
		{
			pvShowMe(pDC,x,y,w,h);
		}
		if(m_blFun)
		{
			m_blFun->pl2Do(pDC,m_nX,m_nY,x,y,w,h);
		} 
	} 
protected:
	char		name[16];
	char		birthday[16];
	int			age;
//	int			x,y;
#include "BlFunction.h"
	CBlFunction		*m_blFun;
	CBlFactory		*m_blFatory;
private:
	void CBlPerson::pvWM(HWND h,UINT m,WPARAM w,LPARAM l)
	{   
		switch(m)
		{
		case WM_LBUTTONDOWN:
			ptLBtnDown(h,m,w,l);
			break;
		case WM_LBUTTONUP:
			ptLBtnUp(h,m,w,l);
			break;
		case WM_MOUSEMOVE:
			ptMouseMove(h,m,w,l);
			break;
		} 
	}
	void CBlPerson::pvShowText(CDC *pDC,char *s,int x,int y)
	{
		pDC->TextOut(x,y,s);
	}
	void pvShowMe(CDC *pDC,int x,int y,int w,int h)
	{
		ptShowOutBorder(pDC);
		int r	= 20;
		int x1	= m_nX - r;
		int y1	= m_nY - r;
		int x2	= m_nX + r;
		int y2	= m_nY + r;
		pDC->Ellipse(x1,y1,x2,y2);
		pvShowText(pDC,name,m_nX,m_nY);
	}
};

#endif // !defined(BLF_H_BLPERSON_INCLUDED_)
