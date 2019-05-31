//Download by http://www.NewXing.com
//	WalkLtDemoHelp.cpp
//
#include "stdafx.h"
#include "WalkLtDemo.h"

#include "WalkLtDemoHelp.h"
#include "GdiplusDemoFuns.h"

#include <math.h>
#include <io.h>

//���� 4244 ���뾯��
#pragma warning( disable : 4244 )

CWideCharString::CWideCharString()
{
	m_nBufferLen=0;
	m_pBuffer=new WCHAR [m_nBufferLen+1];
	m_pBuffer[0]=0;
}

CWideCharString::CWideCharString(LPCWSTR widestring, int len)
{
	if(widestring)
		m_nBufferLen=wcslen(widestring);
	else
		m_nBufferLen=0;
	if(len<m_nBufferLen && len>=0){
		m_nBufferLen=len;
	}

	m_pBuffer=new WCHAR [m_nBufferLen+1];
	if(widestring)
		wcsncpy(m_pBuffer, widestring,m_nBufferLen);
	m_pBuffer[m_nBufferLen]=0;
}

CWideCharString::CWideCharString(const CWideCharString& wcString)
{
	m_nBufferLen=wcString.m_nBufferLen;
	m_pBuffer=new WCHAR [m_nBufferLen+1];
	wcscpy(m_pBuffer,wcString.m_pBuffer);
}

CWideCharString::CWideCharString(const char* lpszString, int len)
{
	if(!lpszString){
		m_nBufferLen=0;
		m_pBuffer=new WCHAR [1];
		m_pBuffer[0]=0;
		return;
	}
	int srclen=strlen(lpszString);

	if(len < srclen && len >=0){
		srclen=len;
	}

	m_nBufferLen=srclen;
	m_pBuffer=new WCHAR[m_nBufferLen+1];
	m_nBufferLen=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszString,srclen,m_pBuffer,m_nBufferLen+1);
	m_pBuffer[m_nBufferLen]=0;
}

CWideCharString::~CWideCharString()
{
	if(m_pBuffer)
		delete[] m_pBuffer;
}

CWideCharString& CWideCharString::operator=(const CWideCharString& wcString)
{
	if(this == &wcString)
		return *this;

	if(m_pBuffer)
		delete[] m_pBuffer;
	m_nBufferLen=wcString.m_nBufferLen;
	m_pBuffer=new WCHAR [m_nBufferLen+1];
	wcscpy(m_pBuffer,wcString.m_pBuffer);
	return *this;
}

CWideCharString& CWideCharString::operator =(const char* lpszString)
{
	if(lpszString==NULL){
		m_nBufferLen=0;
		if(!m_pBuffer){
			m_pBuffer=new WCHAR [m_nBufferLen+1];
		}
		m_pBuffer[0]=0;
		return *this;
	}
	
	int srclen=strlen(lpszString);
	m_nBufferLen=srclen;
	if(m_pBuffer)
		delete[] m_pBuffer;
	m_pBuffer=new WCHAR[m_nBufferLen+1];
	m_nBufferLen=MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,lpszString,srclen,m_pBuffer,m_nBufferLen+1);
	m_pBuffer[m_nBufferLen]=0;
	return *this;	

}

CWideCharString CWideCharString::Mid(int begin,int len)
{
	if (len<0) len=GetLength();
	if(begin+len>m_nBufferLen)
		len=m_nBufferLen-begin;

	return CWideCharString(m_pBuffer+begin,len);
}
BOOL CWideCharString::operator == (const CWideCharString& wcString)
{
	return (wcscmp(m_pBuffer,wcString.m_pBuffer)==0);
}
BOOL CWideCharString::operator != (const CWideCharString& wcString)
{
	return (wcscmp(m_pBuffer,wcString.m_pBuffer)!=0);
}
WCHAR CWideCharString::operator[] (int index) const
{
	if(index<0 || index>=m_nBufferLen)
		return 0;
	return m_pBuffer[index];
}

WCHAR& CWideCharString::operator[] (int index)
{
	if(index<0 || index>=m_nBufferLen){
		static WCHAR w=0;
		return w;
	}
	return m_pBuffer[index];
}

CWideCharString CWideCharString::operator + (const CWideCharString& wcString)
{
	int totalLen=m_nBufferLen+wcString.m_nBufferLen;
	WCHAR* pBuf=new WCHAR[totalLen+1];

	wcscpy(pBuf,m_pBuffer);
	wcscat(pBuf+m_nBufferLen,wcString.m_pBuffer);

	CWideCharString ret(pBuf);
	delete[] pBuf;

	return ret;
}

CWideCharString& CWideCharString::operator += (const CWideCharString& wcString)
{
	int totalLen=m_nBufferLen+wcString.m_nBufferLen;
	WCHAR* pTempBuf=new WCHAR[totalLen+1];

	wcscpy(pTempBuf,m_pBuffer);
	wcscat(pTempBuf+m_nBufferLen,wcString.m_pBuffer);

	delete[] m_pBuffer;
	m_pBuffer=pTempBuf;
	m_nBufferLen=totalLen;

	return *this;
}



Status MyDrawString(Graphics &graphics, const TCHAR *str, const Font &font, const Brush &brush, const PointF &origin)
{
	CWideCharString string(str, strlen(str));
	return graphics.DrawString(string, wcslen(string), &font, origin, &brush);
}
Status MyDrawString(Graphics &graphics, const TCHAR *str, const Font &font, const Brush &brush, const PointF &origin, StringFormat &fmt)
{
	CWideCharString string(str, strlen(str));
	return graphics.DrawString(string, wcslen(string), &font, origin, &fmt, &brush);
}
Status MyDrawString(Graphics &graphics, const TCHAR *str, const Font &font, const Brush &brush, const Point &origin)
{
	CWideCharString string(str, strlen(str));
	return graphics.DrawString(string, wcslen(string), &font, PointF(origin.X,origin.Y), &brush);
}
Status MyDrawString(Graphics &graphics, const TCHAR *str, const Font &font, const Brush &brush, const RectF &rect, StringFormat &fmt)
{
	CWideCharString string(str, strlen(str));
	return graphics.DrawString(string, wcslen(string), &font, rect, &fmt, &brush);
}
Status MyDrawString(Graphics &graphics, const TCHAR *str, const Font &font, const Brush &brush, const Rect &rect, StringFormat &fmt)
{
	CWideCharString string(str, strlen(str));
	RectF r(rect.X, rect.Y, rect.Width, rect.Height);
	return graphics.DrawString(string, wcslen(string), &font, r, &fmt, &brush);
}

void MyImageSave(Bitmap &im, const WCHAR* filename, const GUID* clsid, const EncoderParameters *en)
{
	CString file= filename;
	if (0==::_access(file, 0))
		::DeleteFile(file);
	im.Save(filename, clsid, en);
}

Color _MakeA_RGB(int a, Color cl)
{
	return Color(a, cl.GetR(), cl.GetG(), cl.GetB());
}

Color _MakeA_RGB(int r, int g, int b)
{
	return Color(255, r, g, b);
}


int rand_Next(int bound)
{
	::srand( (unsigned)time( NULL ) );
	return ::rand()/bound;
}




void FillGdiplusFuns(CTreeCtrl &tree)
{
	HTREEITEM ch1, ch2, ch, ch0=TVI_ROOT;

	CString txt0, txt1, txt2;

	int index1=0, index2=0;


	tree.SetItemText(ch0, "Gdi+��ʾ");

		//-------------------------------------------------------------
		txt1 = "����";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0100;

			txt2 = "�ӻ�ˢ�й��컭��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//CreatePenFromBrush_Click;
		tree.SetItemData(ch2, index1+index2);

			txt2 = "�Զ�������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//DashStyle_Custom_Click
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���ʵĶ��뷽ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Pen_Align_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���ʵ���������ת";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Pen_Tranform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���ʵ���ñ����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Pen_LineCap_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���ʵ�͸����֧��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Pen_TransColor_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "��ˢ";
		ch = tree.InsertItem(txt1, ch0);
	index1 = 0x0200;

			ch1 = tree.InsertItem("��ɫ��ˢ��ʹ��", ch);

			txt2 = "�򵥵ĵ�ɫ��ˢ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Brush_SolidBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "�����Ҷ����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Brush_FillVurve_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("Ӱ�߻�ˢ��ʹ��", ch);

			txt2 = "Ӱ�߻�ˢ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Brush_HatchBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ö������Ӱ�߻�ˢ���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Brush_EnumAllStyle_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���û���ԭ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Brush_SetRenderingOrigin_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("����ˢ", ch);

			txt2 = "����ˢ�Ļ���ʹ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Brush_Texture_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "����ˢ�����з�ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Brush_Texture_WrapMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "����ˢ�ı任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Brush_TextureTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��ѯ��ˢ�ı任��Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Brush_GetTextureMatrix_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("���Խ��仭ˢ��ʹ��", ch);

			txt2 = "���Խ��仭ˢ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Brush_LinearGradientBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���仭ˢ�Ĳ�ͬ��䷽ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Brush_LinearArrange_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��ɫ���仭ˢ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Brush_LinearInterpolation_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ʹ�ý��仭ˢ�Ľ���ģʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Brush_LinearGradientMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "����������ƫת�Ƕ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Brush_LinearAngle_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "�Զ������Խ��仭ˢ�Ľ������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Brush_LinearCustomize_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "�������߽���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Brush_LinearGradientBrush_BellShape_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "����GammaУ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Brsuh_LinearGradientBrush_UsingGamma_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("·�����仭ˢ", ch);

			txt2 = "��������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Brush_PathGradientBrush_Star_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��������(2)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 19;	//Brush_PathGradientBrush_Star2_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ʹ�ò�ͬ��·�����仭ˢ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 20;	//Brush_Using_MorePathGradientBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "·�����仭ˢ�����з�ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 21;	//Brush_PathGradientBrush_WrapMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "����·�����仭ˢ�����ĵ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 22;	//Brush_PathGradientBrush_CenterPoint_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ʹ�ö�ɫ����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 23;	//Brush_PathGradientBrush_InterpolationColors_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���Ļ�ˢ�Ľ������ű���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 24;	//Brsuh_PathGradietBrush_Focus_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "·�����仭ˢ�ı任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 25;	//Brush_PathGradientBrush_Transform_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "�ı�������";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0300;

			txt2 = "��GDI+��ʹ������(&A)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Font_UsingFontInGDIPlus_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��ȡ�Ѱ�װ������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Font_EnumAllFonts_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��ǿ������ѡ��Ի���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Font_EnhanceFontDialog_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��������ı�Ե����ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Font_UsingTextRenderHint_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��˽�����弯��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Font_Privatefontcollection_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��˽�����弯����ʹ�ö������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Font_Privatefontcollection2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��˽�����弯���м��������Ϣ�Ŀ�����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Font_IsStyleAvailable_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�ڳ����з�������(ϵ��)�Ĵ�С��Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Font_Size_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı�����Ļ���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Font_BaseLine_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��GDI+�����ı�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Font_DrawString_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Font_MeasureString_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "����ָ���������ܹ���ʾ���ַ�����������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Font_MeasureString2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʵ���ļ��ķ�����ʾ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Font_ColumnTextOut_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�ַ�����ȥβ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Font_StirngTrimming_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�ı�����ļ�������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Font_TextOutClip_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı��ľֲ��������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Font_MeasureCharacterRanges_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı��������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Font_TextoutDirection_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı����뷽ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Font_TextAlignment_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����ı����뷽ʽ(2)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 19;	//Font_TextAlignment2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���úͻ�ȡ�Ʊ����Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 20;	//Font_TextoutUsingTabs_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ���Ʊ�λ���б�����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 21;	//Font_UsingTabs_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ݼ�ǰ���ַ���ʾ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 22;	//Font_TextoutHotkeyPrefix_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��Ӱ����Ч";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 23;	//Font_TextoutShadow_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��Ӱ�߻�ˢ�����ı�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 24;	//Font_TextoutHashline_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "����������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 25;	//Font_TextoutTexture_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�ý��仭ˢ�����ı�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 26;	//Font_TextoutGradient_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "·��������";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0400;


			txt2 = "����·��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Path_Construct_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��·������Ӷ����߶�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Path_AddLines_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���ͼ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Path_CloseFigure_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·�������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Path_FillPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����·��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Path_AddSubPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "GraphicsPathIterator�Ļ���ʹ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Path_GetSubPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "����·���ĵ���Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Path_GetPoints_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ͬʱ��ȡ�˵����꼰������Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Path_PathData_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�鿴·���˵�ı����Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Path_ViewPointFLAG_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "���·������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Path_SubPathRange_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·����չƽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Path_Flatten_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·����Ť��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Path_Warp_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·�������Ա任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Path_Transform_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·�����ؿ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Path_Widen_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "·�����ؿ���ԭ����ʾ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Path_WidenDemo_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��·���д����ı�����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Region_FromPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Region_Calculate_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ȡ�������ɾ��μ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Region_GetRects_Click);
		tree.SetItemData(ch2, index1+index2);



		//-------------------------------------------------------------
		txt1 = "GDI+������任";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0500;

			txt2 = "��GDI+ʹ������任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Transform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ƽ�Ʊ任��ʵ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//TranslateTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "��תͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//RotateTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "������̱�Ļ���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//DrawWatch_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���ű任��ʹ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ScaleTransform_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���ζ��������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//RectScale_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��GDI+����ת����ı�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//FontRotate_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�鿴��������Ԫ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Matrix_ListElements_Click_1);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�þ����ǰ�����׺";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//MatrixPos_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "������ڱ任�е�����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Martrix_Invert_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�ø��ϱ任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Matrix_Multiply_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�þ��������޸ĵ���Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Matrix_TransformPoints_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��TransformPoints����ʵ��·���ı任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Matrix_TransformPoints2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ͨ�����������ά�����ľ�������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Matrix_TransformVectors_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��RotateAt����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Matrix_RotateAt_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�ò�ͬ��Ͷ��任��ʾͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Matrix_Shear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ͶӰ�ֵ���Ч���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Matrix_TextoutShear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���ִ�С���������Ч";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Matrix_ChangeFontHeight_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "GDI+��ɫ�ʱ任";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0600;


			txt2 = "����ɫ�ʱ任����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ColorMatrix_Start_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "ɫ��ƽ������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//TranslateColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ɫ�ʵ���������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//ScaleColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ɫ�ʵ�������ת��ʽ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//RotateColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ɫ�ʵ�Ͷ��任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ColorShear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ɫ��ӳ��ĳ���ʵ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//ColorRemap_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ��ɫ�ʱ任����ʵ��ɫ�����ͨ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//SetRGBOutputChannel_Click);
		tree.SetItemData(ch2, index1+index2);



		//-------------------------------------------------------------
		txt1 = "ͼ��Ļ�������";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0700;

			txt2 = "ͼԪ�ļ��еļ�¼��ط�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Metafile_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ͼ�εļ���������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//CroppingAndScaling_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�ò�ͬ�Ĳ�ֵģʽ����ͼ����������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3; //UsingInterpolationMode_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���ƾ���ͼƬʾ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//RotateFlip_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "����ӳ��ͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ImageSkewing_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��������ͼ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Cubeimage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "GDI+�д�������ͼ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//ThumbnailImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "�ֿ���ʾͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Clone_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "ͼƬ�ֲ��Ŵ�(��С)��ʾ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Picturescale_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "ͼ��ɫ����Ϣ�ĵ���";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0800;

			txt2  = "ɫ��У�������������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ImageAttributesSetNoOp_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "���ò�ͬ��ɫ�ʵ�������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//SetColorMatrices_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "ʹ��ɫ�������ļ�����ɫ��У��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//SetOutputChannelColorProfile_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "�޸�Gammaֵ����ͼƬ���";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Gammaadjust_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "����ɫ�����ͨ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//SetOutputChannel_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "ʹ�ùؼ�ɫ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Colorkey_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ֵ������ʾ����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Setthreshold_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ȡɫ��У����ɫ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//AdjustedPalette_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "����ɫ��У���Ļ���ģʽ����ɫ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//SetWrapMode_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "ͼ�εı��������";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0900;

			txt2  = "�����������Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ListAllImageEncoders_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����������Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//ListImageEncoder_Detail_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�г�ϵͳ���õĽ�������Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//ListImageDecoder_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�鿴��λͼ����ΪJPEGʱ��Ҫ���õĲ�����Ϣ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//GetEncoderParameter_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�鿴���еı�����Ϣ����Ĳ����б�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//GetAllEncoderParameter_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��BMP�ļ����ΪPNG��ʽ���ļ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//menuItem17_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "��BMP�ļ�����ΪTIF�ļ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//SaveBmp2tif_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ʹ�ò�ͬ��ѹ����������JPEG�ļ�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//SaveBMP2JPG_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "JPEG�ļ��ı�����任";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//TransformingJPEG_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�����֡ͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//MultipleFrameImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��ȡ��֡ͼƬ����ͼƬ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//GetImageFromMultyFrame_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "��ȡͼ�������б�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//QueryImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�޸�ͼƬ����";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//SetProp_Click);
		tree.SetItemData(ch2, index1+index2);

			
		//-------------------------------------------------------------
		txt1 = "ͼ���ؼ�����";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0A00;

			txt2  = "����ǳ��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//menuItem2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "�Ҷȴ����뻹ԭ";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//GrayScale_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "��Ƭ(��Ƭ)�˾�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Inverse_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "���񼰵��";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Emboss_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�ͻ�Ч��������";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//OnCanvas_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ľ���˾�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//OnWood_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "ǿ�������˾�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Flashligt_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "�ữ�����˾�";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//BlurAndSharpen_Click);
		tree.SetItemData(ch2, index1+index2);
}



void DoGdiplusFuns(int index1, int index2)
{
	switch (index1)
	{
		//-------------------------------------------------------------
		//txt1 = "����";
	case 0x01:
		switch (index2)
		{
		case 1: CreatePenFromBrush_Click(); break;
		case 2: DashStyle_Custom_Click(); break;
		case 3: Pen_Align_Click(); break;
		case 4: Pen_Tranform_Click(); break;
		case 5: Pen_LineCap_Click(); break;
		case 6: Pen_TransColor_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "��ˢ";
	case 0x02:
		switch (index2)
		{
		case 1: Brush_SolidBrush_Click(); break;
		case 2: Brush_FillVurve_Click(); break;
		case 3: Brush_HatchBrush_Click(); break;
		case 4: Brush_EnumAllStyle_Click(); break;
		case 5: Brush_SetRenderingOrigin_Click(); break;
		case 6: Brush_Texture_Click(); break;
		case 7: Brush_Texture_WrapMode_Click(); break;
		case 8: Brush_TextureTransform_Click(); break;
		case 9: Brush_GetTextureMatrix_Click(); break;
		case 10: Brush_LinearGradientBrush_Click(); break;
		case 11: Brush_LinearArrange_Click(); break;
		case 12: Brush_LinearInterpolation_Click(); break;
		case 13: Brush_LinearGradientMode_Click(); break;
		case 14: Brush_LinearAngle_Click(); break;
		case 15: Brush_LinearCustomize_Click(); break;
		case 16: Brush_LinearGradientBrush_BellShape_Click(); break;
		case 17: Brsuh_LinearGradientBrush_UsingGamma_Click(); break;
		case 18: Brush_PathGradientBrush_Star_Click(); break;
		case 19: Brush_PathGradientBrush_Star2_Click(); break;
		case 20: Brush_Using_MorePathGradientBrush_Click(); break;
		case 21: Brush_PathGradientBrush_WrapMode_Click(); break;
		case 22: Brush_PathGradientBrush_CenterPoint_Click(); break;
		case 23: Brush_PathGradientBrush_InterpolationColors_Click(); break;
		case 24: Brsuh_PathGradietBrush_Focus_Click(); break;
		case 25: Brush_PathGradientBrush_Transform_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "�ı�������";
	case 0x03:
		switch (index2)
		{
		case 1: Font_UsingFontInGDIPlus_Click(); break;
		case 2: Font_EnumAllFonts_Click(); break;
		case 3: Font_EnhanceFontDialog_Click(); break;
		case 4: Font_UsingTextRenderHint_Click(); break;
		case 5: Font_Privatefontcollection_Click(); break;
		case 6: Font_Privatefontcollection2_Click(); break;
		case 7: Font_IsStyleAvailable_Click(); break;
		case 8: Font_Size_Click(); break;
		case 9: Font_BaseLine_Click(); break;
		case 10: Font_DrawString_Click(); break;
		case 11: Font_MeasureString_Click(); break;
		case 12: Font_MeasureString2_Click(); break;
		case 13: Font_ColumnTextOut_Click(); break;
		case 14: Font_StirngTrimming_Click(); break;
		case 15: Font_TextOutClip_Click(); break;
		case 16: Font_MeasureCharacterRanges_Click(); break;
		case 17: Font_TextoutDirection_Click(); break;
		case 18: Font_TextAlignment_Click(); break;
		case 19: Font_TextAlignment2_Click(); break;
		case 20: Font_TextoutUsingTabs_Click(); break;
		case 21: Font_UsingTabs_Click(); break;
		case 22: Font_TextoutHotkeyPrefix_Click(); break;
		case 23: Font_TextoutShadow_Click(); break;
		case 24: Font_TextoutHashline_Click(); break;
		case 25: Font_TextoutTexture_Click(); break;
		case 26: Font_TextoutGradient_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "·��������";
	case 0x04:
		switch (index2)
		{
		case 1: Path_Construct_Click(); break;
		case 2: Path_AddLines_Click(); break;
		case 3: Path_CloseFigure_Click(); break;
		case 4: Path_FillPath_Click(); break;
		case 5: Path_AddSubPath_Click(); break;
		case 6: Path_GetSubPath_Click(); break;
		case 7: Path_GetPoints_Click(); break;
		case 8: Path_PathData_Click(); break;
		case 9: Path_ViewPointFLAG_Click(); break;
		case 10: Path_SubPathRange_Click(); break;
		case 11: Path_Flatten_Click(); break;
		case 12: Path_Warp_Click(); break;
		case 13: Path_Transform_Click(); break;
		case 14: Path_Widen_Click(); break;
		case 15: Path_WidenDemo_Click(); break;
		case 16: Region_FromPath_Click(); break;
		case 17: Region_Calculate_Click(); break;
		case 18: Region_GetRects_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "GDI+������任";
	case 0x05:
		switch (index2)
		{
		case 1: Transform_Click(); break;
		case 2: TranslateTransform_Click(); break;
		case 3: RotateTransform_Click(); break;
		case 4: DrawWatch_Click(); break;
		case 5: ScaleTransform_Click(); break;
		case 6: RectScale_Click(); break;
		case 7: FontRotate_Click(); break;
		case 8: Matrix_ListElements_Click_1(); break;
		case 9: MatrixPos_Click(); break;
		case 10: Martrix_Invert_Click(); break;
		case 11: Matrix_Multiply_Click(); break;
		case 12: Matrix_TransformPoints_Click(); break;
		case 13: Matrix_TransformPoints2_Click(); break;
		case 14: Matrix_TransformVectors_Click(); break;
		case 15: Matrix_RotateAt_Click(); break;
		case 16: Matrix_Shear_Click(); break;
		case 17: Matrix_TextoutShear_Click(); break;
		case 18: Matrix_ChangeFontHeight_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "GDI+��ɫ�ʱ任";
	case 0x06:
		switch (index2)
		{
		case 1: ColorMatrix_Start_Click(); break;
		case 2: TranslateColor_Click(); break;
		case 3: ScaleColor_Click(); break;
		case 4: RotateColor_Click(); break;
		case 5: ColorShear_Click(); break;
		case 6: ColorRemap_Click(); break;
		case 7: SetRGBOutputChannel_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ��Ļ�������";
	case 0x07:
		switch (index2)
		{
		case 1: Metafile_Click(); break;
		case 2: CroppingAndScaling_Click(); break;
		case 3: UsingInterpolationMode_Click(); break;
		case 4: RotateFlip_Click(); break;
		case 5: ImageSkewing_Click(); break;
		case 6: Cubeimage_Click(); break;
		case 7: ThumbnailImage_Click(); break;
		case 8: Clone_Click(); break;
		case 9: Picturescale_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ��ɫ����Ϣ�ĵ���";
	case 0x08:
		switch (index2)
		{
		case 1: ImageAttributesSetNoOp_Click(); break;
		case 2: SetColorMatrices_Click(); break;
		case 3: SetOutputChannelColorProfile_Click(); break;
		case 4: Gammaadjust_Click(); break;
		case 5: SetOutputChannel_Click(); break;
		case 6: Colorkey_Click(); break;
		case 7: Setthreshold_Click(); break;
		case 8: AdjustedPalette_Click(); break;
		case 9: SetWrapMode_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ�εı��������";
	case 0x09:
		switch (index2)
		{
		case 1: ListAllImageEncoders_Click(); break;
		case 2: ListImageEncoder_Detail_Click(); break;
		case 3: ListImageDecoder_Click(); break;
		case 4: GetEncoderParameter_Click(); break;
		case 5: GetAllEncoderParameter_Click(); break;
		case 6: menuItem17_Click(); break;
		case 7: SaveBmp2tif_Click(); break;
		case 8: SaveBMP2JPG_Click(); break;
		case 9: TransformingJPEG_Click(); break;
		case 10: MultipleFrameImage_Click(); break;
		case 11: GetImageFromMultyFrame_Click(); break;
		case 12: QueryImage_Click(); break;
		case 13: SetProp_Click(); break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ���ؼ�����";
	case 0x0A:
		switch (index2)
		{
		case 1: menuItem2_Click(); break;
		case 2: GrayScale_Click(); break;
		case 3: Inverse_Click(); break;
		case 4: Emboss_Click(); break;
		case 5: OnCanvas_Click(); break;
		case 6: OnWood_Click(); break;
		case 7: Flashligt_Click(); break;
		case 8: BlurAndSharpen_Click(); break;
		}
		break;
	}
}

//
CString GetGdiplusFunsName(int index1, int index2)
{
	CString s;
	switch (index1)
	{
		//-------------------------------------------------------------
		//txt1 = "����";
	case 0x01:
		switch (index2)
		{
		case 1: s="CreatePenFromBrush_Click()"; break;
		case 2: s="DashStyle_Custom_Click()"; break;
		case 3: s="Pen_Align_Click()"; break;
		case 4: s="Pen_Tranform_Click()"; break;
		case 5: s="Pen_LineCap_Click()"; break;
		case 6: s="Pen_TransColor_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "��ˢ";
	case 0x02:
		switch (index2)
		{
		case 1: s="Brush_SolidBrush_Click()"; break;
		case 2: s="Brush_FillVurve_Click()"; break;
		case 3: s="Brush_HatchBrush_Click()"; break;
		case 4: s="Brush_EnumAllStyle_Click()"; break;
		case 5: s="Brush_SetRenderingOrigin_Click()"; break;
		case 6: s="Brush_Texture_Click()"; break;
		case 7: s="Brush_Texture_WrapMode_Click()"; break;
		case 8: s="Brush_TextureTransform_Click()"; break;
		case 9: s="Brush_GetTextureMatrix_Click()"; break;
		case 10: s="Brush_LinearGradientBrush_Click()"; break;
		case 11: s="Brush_LinearArrange_Click()"; break;
		case 12: s="Brush_LinearInterpolation_Click()"; break;
		case 13: s="Brush_LinearGradientMode_Click()"; break;
		case 14: s="Brush_LinearAngle_Click()"; break;
		case 15: s="Brush_LinearCustomize_Click()"; break;
		case 16: s="Brush_LinearGradientBrush_BellShape_Click()"; break;
		case 17: s="Brsuh_LinearGradientBrush_UsingGamma_Click()"; break;
		case 18: s="Brush_PathGradientBrush_Star_Click()"; break;
		case 19: s="Brush_PathGradientBrush_Star2_Click()"; break;
		case 20: s="Brush_Using_MorePathGradientBrush_Click()"; break;
		case 21: s="Brush_PathGradientBrush_WrapMode_Click()"; break;
		case 22: s="Brush_PathGradientBrush_CenterPoint_Click()"; break;
		case 23: s="Brush_PathGradientBrush_InterpolationColors_Click()"; break;
		case 24: s="Brsuh_PathGradietBrush_Focus_Click()"; break;
		case 25: s="Brush_PathGradientBrush_Transform_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "�ı�������";
	case 0x03:
		switch (index2)
		{
		case 1: s="Font_UsingFontInGDIPlus_Click()"; break;
		case 2: s="Font_EnumAllFonts_Click()"; break;
		case 3: s="Font_EnhanceFontDialog_Click()"; break;
		case 4: s="Font_UsingTextRenderHint_Click()"; break;
		case 5: s="Font_Privatefontcollection_Click()"; break;
		case 6: s="Font_Privatefontcollection2_Click()"; break;
		case 7: s="Font_IsStyleAvailable_Click()"; break;
		case 8: s="Font_Size_Click()"; break;
		case 9: s="Font_BaseLine_Click()"; break;
		case 10: s="Font_DrawString_Click()"; break;
		case 11: s="Font_MeasureString_Click()"; break;
		case 12: s="Font_MeasureString2_Click()"; break;
		case 13: s="Font_ColumnTextOut_Click()"; break;
		case 14: s="Font_StirngTrimming_Click()"; break;
		case 15: s="Font_TextOutClip_Click()"; break;
		case 16: s="Font_MeasureCharacterRanges_Click()"; break;
		case 17: s="Font_TextoutDirection_Click()"; break;
		case 18: s="Font_TextAlignment_Click()"; break;
		case 19: s="Font_TextAlignment2_Click()"; break;
		case 20: s="Font_TextoutUsingTabs_Click()"; break;
		case 21: s="Font_UsingTabs_Click()"; break;
		case 22: s="Font_TextoutHotkeyPrefix_Click()"; break;
		case 23: s="Font_TextoutShadow_Click()"; break;
		case 24: s="Font_TextoutHashline_Click()"; break;
		case 25: s="Font_TextoutTexture_Click()"; break;
		case 26: s="Font_TextoutGradient_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "·��������";
	case 0x04:
		switch (index2)
		{
		case 1: s="Path_Construct_Click()"; break;
		case 2: s="Path_AddLines_Click()"; break;
		case 3: s="Path_CloseFigure_Click()"; break;
		case 4: s="Path_FillPath_Click()"; break;
		case 5: s="Path_AddSubPath_Click()"; break;
		case 6: s="Path_GetSubPath_Click()"; break;
		case 7: s="Path_GetPoints_Click()"; break;
		case 8: s="Path_PathData_Click()"; break;
		case 9: s="Path_ViewPointFLAG_Click()"; break;
		case 10: s="Path_SubPathRange_Click()"; break;
		case 11: s="Path_Flatten_Click()"; break;
		case 12: s="Path_Warp_Click()"; break;
		case 13: s="Path_Transform_Click()"; break;
		case 14: s="Path_Widen_Click()"; break;
		case 15: s="Path_WidenDemo_Click()"; break;
		case 16: s="Region_FromPath_Click()"; break;
		case 17: s="Region_Calculate_Click()"; break;
		case 18: s="Region_GetRects_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "GDI+������任";
	case 0x05:
		switch (index2)
		{
		case 1: s="Transform_Click()"; break;
		case 2: s="TranslateTransform_Click()"; break;
		case 3: s="RotateTransform_Click()"; break;
		case 4: s="DrawWatch_Click()"; break;
		case 5: s="ScaleTransform_Click()"; break;
		case 6: s="RectScale_Click()"; break;
		case 7: s="FontRotate_Click()"; break;
		case 8: s="Matrix_ListElements_Click_1()"; break;
		case 9: s="MatrixPos_Click()"; break;
		case 10: s="Martrix_Invert_Click()"; break;
		case 11: s="Matrix_Multiply_Click()"; break;
		case 12: s="Matrix_TransformPoints_Click()"; break;
		case 13: s="Matrix_TransformPoints2_Click()"; break;
		case 14: s="Matrix_TransformVectors_Click()"; break;
		case 15: s="Matrix_RotateAt_Click()"; break;
		case 16: s="Matrix_Shear_Click()"; break;
		case 17: s="Matrix_TextoutShear_Click()"; break;
		case 18: s="Matrix_ChangeFontHeight_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "GDI+��ɫ�ʱ任";
	case 0x06:
		switch (index2)
		{
		case 1: s="ColorMatrix_Start_Click()"; break;
		case 2: s="TranslateColor_Click()"; break;
		case 3: s="ScaleColor_Click()"; break;
		case 4: s="RotateColor_Click()"; break;
		case 5: s="ColorShear_Click()"; break;
		case 6: s="ColorRemap_Click()"; break;
		case 7: s="SetRGBOutputChannel_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ��Ļ�������";
	case 0x07:
		switch (index2)
		{
		case 1: s="Metafile_Click()"; break;
		case 2: s="CroppingAndScaling_Click()"; break;
		case 3: s="UsingInterpolationMode_Click()"; break;
		case 4: s="RotateFlip_Click()"; break;
		case 5: s="ImageSkewing_Click()"; break;
		case 6: s="Cubeimage_Click()"; break;
		case 7: s="ThumbnailImage_Click()"; break;
		case 8: s="Clone_Click()"; break;
		case 9: s="Picturescale_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ��ɫ����Ϣ�ĵ���";
	case 0x08:
		switch (index2)
		{
		case 1: s="ImageAttributesSetNoOp_Click()"; break;
		case 2: s="SetColorMatrices_Click()"; break;
		case 3: s="SetOutputChannelColorProfile_Click()"; break;
		case 4: s="Gammaadjust_Click()"; break;
		case 5: s="SetOutputChannel_Click()"; break;
		case 6: s="Colorkey_Click()"; break;
		case 7: s="Setthreshold_Click()"; break;
		case 8: s="AdjustedPalette_Click()"; break;
		case 9: s="SetWrapMode_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ�εı��������";
	case 0x09:
		switch (index2)
		{
		case 1: s="ListAllImageEncoders_Click()"; break;
		case 2: s="ListImageEncoder_Detail_Click()"; break;
		case 3: s="ListImageDecoder_Click()"; break;
		case 4: s="GetEncoderParameter_Click()"; break;
		case 5: s="GetAllEncoderParameter_Click()"; break;
		case 6: s="menuItem17_Click()"; break;
		case 7: s="SaveBmp2tif_Click()"; break;
		case 8: s="SaveBMP2JPG_Click()"; break;
		case 9: s="TransformingJPEG_Click()"; break;
		case 10: s="MultipleFrameImage_Click()"; break;
		case 11: s="GetImageFromMultyFrame_Click()"; break;
		case 12: s="QueryImage_Click()"; break;
		case 13: s="SetProp_Click()"; break;
		}
		break;

		//-------------------------------------------------------------
		//txt1 = "ͼ���ؼ�����";
	case 0x0A:
		switch (index2)
		{
		case 1: s="menuItem2_Click()"; break;
		case 2: s="GrayScale_Click()"; break;
		case 3: s="Inverse_Click()"; break;
		case 4: s="Emboss_Click()"; break;
		case 5: s="OnCanvas_Click()"; break;
		case 6: s="OnWood_Click()"; break;
		case 7: s="Flashligt_Click()"; break;
		case 8: s="BlurAndSharpen_Click()"; break;
		}
		break;
	}
	return s;
}

//��ȡ������Դ����
CString GetGdiplusFunsCode(int index1, int index2)
{
	CString key=GetGdiplusFunsName(index1, index2);
	if (key.IsEmpty())
		return "δ�ҵ�����";

	//����ԭ������ <exePath> ../WalkLtDemo/WalkLtDemo���ʵ��.cpp
	TCHAR ModuleDirectory[_MAX_PATH];
	::GetModuleFileName(NULL, ModuleDirectory, _MAX_PATH);
	TCHAR *p=::_tcsrchr(ModuleDirectory, '\\');
	if (p)
	{
		*p=0;
		p=::_tcsrchr(ModuleDirectory, '\\'); *p=0;
		::_tcscat(ModuleDirectory, "\\WalkLtDemo\\WalkLtDemo���ʵ��.cpp");
	}

	CString fname=ModuleDirectory;
	FILE *pf = ::fopen(fname, "rt");
	if (!pf)
		return "���ļ�ʧ��";

	CString res;

	char buf[1024];
	while (!feof(pf))
	{
		::fgets(buf, 1024, pf);
		if (strstr(buf, key))
		{
			CString s=buf; s.TrimRight(); s+="\r\n";
			res = s;
			while (!feof(pf))
			{
				::fgets(buf, 1024, pf);
				s=buf; s.TrimRight(); s+="\r\n";
				res += s;
				if (buf[0]=='}')
				{
					::fclose(pf);
					return res;
				}
			}
		}
	}
	::fclose(pf);
	return res;
}

////////////////////////////////////////////////////////////////

Graphics *gz_graphics;
Graphics &GetGraphics()
{
	return *gz_graphics;
}
Rect MyClient;

extern void DoGdiplusFuns(int index1, int index2);
void DoGdiplusDemo(Graphics &gc, CView *pView, int index1, int index2)
{
	//------------- ȫ�ֱ����ĳ�ʼ�� -------------------------
	gz_graphics = &gc;
	CRect rect;
	pView->GetClientRect(&rect);
	MyClient.X=rect.left; MyClient.Y=rect.top;
	MyClient.Width=rect.Width(); MyClient.Height=rect.Height();

	//------------ Action ------------------------------------
	DoGdiplusFuns(index1, index2);
}
