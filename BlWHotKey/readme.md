~~~c++
//BlWHotKey.h
/*
*/



class CBlWHotKey
{
public:
	CBlWHotKey::CBlWHotKey(){
		strcpy(m_szV,"V0.0.1");
	}
	CBlWHotKey::~CBlWHotKey(){}
	void onUnRegKey(HWND h,int code)
	{
		::UnregisterHotKey(h,code);
	}
	void onRegKey(HWND h,int code,WORD sysKey,WORD virKey)
	{ 
		UINT ui = 0; 
		if (sysKey & HOTKEYF_ALT)	    ui|= MOD_ALT;
		if (sysKey & HOTKEYF_CONTROL)   ui|= MOD_CONTROL;
		if (sysKey & HOTKEYF_SHIFT) 	ui|= MOD_SHIFT; 	
		
		if(!::RegisterHotKey(h, code, ui, virKey))
		{ 
		}
	}
	void onKey(HWND h,int code)
	{
		switch(code)
		{
		case 1:
			pvFun1(h);
			break;
		case 2:
			pvFun2(h);
			break;
		case 3:
			pvFun3(h);
			break;
		case 4:
			pvFun4(h);
			break;
		}
	}

private:
	char	m_szV[16];
	void pvFun2(HWND h)
	{
		//::MessageBox(h,"pvFun2","xd",IDOK);
#include "XdBmp.h"
		CXdBmp xb;

		POINT pt;
		::GetCursorPos(&pt);
		HWND hwnd = WindowFromPoint(pt);
		RECT rc;
		GetWindowRect(hwnd,&rc);

		xb.getScreenToBmp(&rc,true);
	}
	void pvFun3(HWND h)
	{
		::MessageBox(h,"pvFun3","xd",IDOK);
	}
	void pvFun4(HWND h)
	{
		::MessageBox(h,"pvFun4","xd",IDOK);
	}
	void pvFun1(HWND h)
	{
		static int b = 0; 
		b = !b;
		if(b)
		{
			::ShowWindow(h,SW_HIDE); 
			onRegKey(h,2,MOD_CONTROL,VK_SPACE); 
		}
		else
		{
			::ShowWindow(h,SW_SHOW); 
			::SetFocus(h);
			onUnRegKey(h,2); 
			onUnRegKey(h,3); 
			onUnRegKey(h,4);
		} 
	}
};

~~~
