// BlFactory.h v0.0.7


#if !defined(BLF_H_BLFACTORY_INCLUDED_)
#define BLF_H_BLFACTORY_INCLUDED_
 
class CBlFactory
{
#include "BlFunction.h"

	class CBlList: public CBl
	{
	public:	
		CBlList::CBlList()
		{ 
		}
		CBlList::~CBlList()
		{ 

		}
		void CBlList::pl2WM(HWND h,UINT m,WPARAM w,LPARAM l)
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
		void CBlList::pl2Show(CDC *pDC,int x,int y,int w,int h)
		{
			pvDraw(pDC,x,y,w,h); 
		}
	private:
		typedef struct _node{
		}NODE,*PNODE;
		PNODE	h;
		void pvDraw(CDC *pDC,int x,int y,int w,int h)
		{ 
			ptShowInBorder(pDC);
		} 
		
		

	};

#include "BlPerson.h"
public:
	CBlFactory::CBlFactory(): m_nAll(0),
		m_hPWnd(NULL),m_hInst(NULL)
	{
		strcpy(name,"unkown"); 
		m_mp3Player.plSetFactory(this);
		 
	}
	CBlFactory::~CBlFactory()
	{
	} 
 
	void CBlFactory::plAddPerson(char *name)
	{
		m_All[m_nAll].plSetName(name);
		m_All[m_nAll].plSetFactory(this);
		m_All[m_nAll].plMoveD(130+50*m_nAll,500);
		if(0==m_nAll){
			m_All[m_nAll].plSetFun(&m_mp3Player,100,100,100,10);
			
		}
		else if (1==m_nAll){
			m_All[m_nAll].plSetFun (&w1,30*m_nAll,80,60,12);
		}
		m_nAll++;

	}
	void CBlFactory::plCmd(int idCmd,char *sz)
	{
		pvMp3Play(m_hPWnd,m_hInst,sz);

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
		m_ToolList.pl2WM(h,m,w,l);
	}

    virtual	void CBlFactory::pl_Draw(CDC *pDC,int x,int y,int w,int h)
	{ 
		/*
		CBlPerson *pVM = pvGetPerson("vm");
		if(pVM)	pVM->pl2Show(pDC,x,y,w,h,false);
		//*/ 
		pvDraw(pDC,x,y,w,h);
	} 
	void CBlFactory::pl_Init(HWND hWnd,HINSTANCE hInst)
	{ 
		m_hPWnd = hWnd;
		m_hInst = hInst;
		
	}
protected:
	char			name[16];
	CBlPerson		m_All[250]; 
	int				m_nAll; 
	CBlList			m_ToolList;
private:
	//
	void pvDrawFactory(CDC *pDC,int x1,int y1,int x2,int y2)
	{
		pDC->TextOut(x1,y1,name);
	}
	void pvDrawTools(CDC *pDC,int x,int y,int w,int h)
	{
		m_ToolList.pl2Show(pDC,x,y,w,h);
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
		pvDrawTools(&dcMem,x1,y1,w,h);
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
	
	void pvMp3Play(HWND hPWnd,HINSTANCE hInst,char *szFilePath)
	{
		HWND hAudio = NULL;
		try{ 
			hAudio=MCIWndCreate(hPWnd,hInst,
				WS_CHILD|MCIWNDF_NOMENU,szFilePath);
		}
		catch(...)
		{
			AfxMessageBox("...");
			return;
			
		}
		
		if(hAudio!=NULL){
			MCIWndPlay(hAudio);	
			
			int nSetVol=63*9;
			if(nSetVol>1000)
				nSetVol=1000;
			MCIWndSetVolume(hAudio,nSetVol);
		}
	}
	
//	CBlFViewMng		f1;
	CBlFunWork			w1;
	CBlFunMp3Player		m_mp3Player;
	HWND				m_hPWnd;
	HINSTANCE			m_hInst;
};
 
#endif // !defined(BLF_H_BLFACTORY_INCLUDED_)