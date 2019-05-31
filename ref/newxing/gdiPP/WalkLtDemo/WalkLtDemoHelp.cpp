//Download by http://www.NewXing.com
//	WalkLtDemoHelp.cpp
//
#include "stdafx.h"
#include "WalkLtDemo.h"

#include "WalkLtDemoHelp.h"
#include "GdiplusDemoFuns.h"

#include <math.h>
#include <io.h>

//屏蔽 4244 编译警告
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


	tree.SetItemText(ch0, "Gdi+演示");

		//-------------------------------------------------------------
		txt1 = "画笔";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0100;

			txt2 = "从画刷中构造画笔";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//CreatePenFromBrush_Click;
		tree.SetItemData(ch2, index1+index2);

			txt2 = "自定义线型";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//DashStyle_Custom_Click
		tree.SetItemData(ch2, index1+index2);

			txt2 = "画笔的对齐方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Pen_Align_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "画笔的缩放与旋转";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Pen_Tranform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "画笔的线帽属性";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Pen_LineCap_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "画笔的透明度支持";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Pen_TransColor_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "画刷";
		ch = tree.InsertItem(txt1, ch0);
	index1 = 0x0200;

			ch1 = tree.InsertItem("单色画刷的使用", ch);

			txt2 = "简单的单色画刷";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Brush_SolidBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "填充正叶曲线";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Brush_FillVurve_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("影线画刷的使用", ch);

			txt2 = "影线画刷";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Brush_HatchBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "枚举所有影线画刷风格";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Brush_EnumAllStyle_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "设置绘制原点";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Brush_SetRenderingOrigin_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("纹理画刷", ch);

			txt2 = "纹理画刷的基本使用";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Brush_Texture_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "纹理画刷的排列方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Brush_Texture_WrapMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "纹理画刷的变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Brush_TextureTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "查询画刷的变换信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Brush_GetTextureMatrix_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("线性渐变画刷的使用", ch);

			txt2 = "线性渐变画刷";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Brush_LinearGradientBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "渐变画刷的不同填充方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Brush_LinearArrange_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "多色渐变画刷";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Brush_LinearInterpolation_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "使用渐变画刷的渐变模式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Brush_LinearGradientMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "调整渐变线偏转角度";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Brush_LinearAngle_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "自定义线性渐变画刷的渐变过程";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Brush_LinearCustomize_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "钟形曲线渐变";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Brush_LinearGradientBrush_BellShape_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "启用Gamma校正";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Brsuh_LinearGradientBrush_UsingGamma_Click);
		tree.SetItemData(ch2, index1+index2);

			ch1 = tree.InsertItem("路径渐变画刷", ch);

			txt2 = "构造五星";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Brush_PathGradientBrush_Star_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "构造五星(2)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 19;	//Brush_PathGradientBrush_Star2_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "使用不同的路径渐变画刷";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 20;	//Brush_Using_MorePathGradientBrush_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "路径渐变画刷的排列方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 21;	//Brush_PathGradientBrush_WrapMode_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "更改路径渐变画刷的中心点";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 22;	//Brush_PathGradientBrush_CenterPoint_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "使用多色渐变";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 23;	//Brush_PathGradientBrush_InterpolationColors_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "更改画刷的焦点缩放比例";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 24;	//Brsuh_PathGradietBrush_Focus_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "路径渐变画刷的变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 25;	//Brush_PathGradientBrush_Transform_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "文本与字体";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0300;

			txt2 = "在GDI+中使用字体(&A)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Font_UsingFontInGDIPlus_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "获取已安装的字体";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Font_EnumAllFonts_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "增强型字体选择对话框";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Font_EnhanceFontDialog_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "设置字体的边缘处理方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Font_UsingTextRenderHint_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用私有字体集合";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Font_Privatefontcollection_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "在私有字体集合中使用多个字体";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Font_Privatefontcollection2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "在私有字体集合中检查字体信息的可用性";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Font_IsStyleAvailable_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "在程序中访问字体(系列)的大小信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Font_Size_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "设置文本输出的基线";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Font_BaseLine_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用GDI+绘制文本";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Font_DrawString_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "测量文本";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Font_MeasureString_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "计算指定区域中能够显示的字符总数及行数";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Font_MeasureString2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "实现文件的分栏显示";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Font_ColumnTextOut_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "字符串的去尾";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Font_StirngTrimming_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "文本输出的剪裁修正";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Font_TextOutClip_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "测量文本的局部输出区域";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Font_MeasureCharacterRanges_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "控制文本输出方向";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Font_TextoutDirection_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "设置文本对齐方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Font_TextAlignment_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "设置文本对齐方式(2)";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 19;	//Font_TextAlignment2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "设置和获取制表符信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 20;	//Font_TextoutUsingTabs_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用制表位进行表格输出";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 21;	//Font_UsingTabs_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "快捷键前导字符显示";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 22;	//Font_TextoutHotkeyPrefix_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "阴影字特效";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 23;	//Font_TextoutShadow_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用影线画刷绘制文本";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 24;	//Font_TextoutHashline_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "绘制纹理字";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 25;	//Font_TextoutTexture_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用渐变画刷绘制文本";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 26;	//Font_TextoutGradient_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "路径和区域";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0400;


			txt2 = "构造路径";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Path_Construct_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "在路径中添加多条线段";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//Path_AddLines_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "封闭图形";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Path_CloseFigure_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的填充";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Path_FillPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "添加子路径";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//Path_AddSubPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "GraphicsPathIterator的基本使用";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Path_GetSubPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "访问路径的点信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Path_GetPoints_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "同时获取端点坐标及类型信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Path_PathData_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "查看路径端点的标记信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Path_ViewPointFLAG_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "标记路径区间";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Path_SubPathRange_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的展平";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Path_Flatten_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的扭曲";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Path_Warp_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的线性变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Path_Transform_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的拓宽";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Path_Widen_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "路径的拓宽处理原理演示";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Path_WidenDemo_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "从路径中创建文本区域";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Region_FromPath_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "区域的运算";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Region_Calculate_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "获取区域的组成矩形集";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Region_GetRects_Click);
		tree.SetItemData(ch2, index1+index2);



		//-------------------------------------------------------------
		txt1 = "GDI+的坐标变换";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0500;

			txt2 = "在GDI+使用坐标变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Transform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "平移变换的实现";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//TranslateTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "旋转图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//RotateTransform_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "汽车里程表的绘制";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//DrawWatch_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "缩放变换的使用";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ScaleTransform_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "矩形对象的缩放";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//RectScale_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "在GDI+中旋转输出文本";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//FontRotate_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "查看矩阵的组成元素";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Matrix_ListElements_Click_1);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用矩阵的前置与后缀";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//MatrixPos_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "逆矩阵在变换中的运用";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//Martrix_Invert_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用复合变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//Matrix_Multiply_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用矩阵批量修改点信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//Matrix_TransformPoints_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用TransformPoints函数实现路径的变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//Matrix_TransformPoints2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "普通矩阵运算与二维向量的矩阵运算";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 14;	//Matrix_TransformVectors_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用RotateAt函数";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 15;	//Matrix_RotateAt_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用不同的投射变换显示图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 16;	//Matrix_Shear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "投影字的特效输出";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 17;	//Matrix_TextoutShear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "文字大小渐变输出特效";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 18;	//Matrix_ChangeFontHeight_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "GDI+的色彩变换";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0600;


			txt2 = "启用色彩变换矩阵";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ColorMatrix_Start_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "色彩平移运算";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//TranslateColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "色彩的缩放运算";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//ScaleColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "色彩的三种旋转方式";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//RotateColor_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "色彩的投射变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ColorShear_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "色彩映射的程序实现";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//ColorRemap_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用色彩变换矩阵实现色彩输出通道";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//SetRGBOutputChannel_Click);
		tree.SetItemData(ch2, index1+index2);



		//-------------------------------------------------------------
		txt1 = "图像的基本处理";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0700;

			txt2 = "图元文件中的记录与回放";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//Metafile_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "图形的剪裁与缩放";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//CroppingAndScaling_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用不同的插值模式控制图形缩放质量";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3; //UsingInterpolationMode_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "绘制镜像图片示例";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//RotateFlip_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "绘制映射图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//ImageSkewing_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "立方体贴图";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Cubeimage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "GDI+中处理缩略图";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//ThumbnailImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "分块显示图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//Clone_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "图片局部放大(缩小)显示";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//Picturescale_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "图像色彩信息的调整";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0800;

			txt2  = "色彩校正的启用与禁用";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ImageAttributesSetNoOp_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "设置不同的色彩调整对象";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//SetColorMatrices_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "使用色彩配置文件进行色彩校正";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//SetOutputChannelColorProfile_Click);
		tree.SetItemData(ch2, index1+index2);

			txt2 = "修改Gamma值进行图片输出";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Gammaadjust_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "设置色彩输出通道";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//SetOutputChannel_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "使用关键色";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//Colorkey_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "阈值运用演示程序";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Setthreshold_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "获取色彩校正调色板";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//AdjustedPalette_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "设置色彩校正的环绕模式和颜色";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//SetWrapMode_Click);
		tree.SetItemData(ch2, index1+index2);


		//-------------------------------------------------------------
		txt1 = "图形的编码与解码";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0900;

			txt2  = "输出编码器信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//ListAllImageEncoders_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "输出编码器信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//ListImageEncoder_Detail_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "列出系统可用的解码器信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//ListImageDecoder_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "查看将位图保存为JPEG时需要设置的参数信息";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//GetEncoderParameter_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "查看所有的编码信息所需的参数列表";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//GetAllEncoderParameter_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "将BMP文件另存为PNG格式的文件";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//menuItem17_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "将BMP文件保存为TIF文件";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//SaveBmp2tif_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "使用不同的压缩质量保存JPEG文件";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//SaveBMP2JPG_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "JPEG文件的保存与变换";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 9;	//TransformingJPEG_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "保存多帧图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 10;	//MultipleFrameImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "读取多帧图片的子图片";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 11;	//GetImageFromMultyFrame_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "获取图像属性列表";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 12;	//QueryImage_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "修改图片属性";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 13;	//SetProp_Click);
		tree.SetItemData(ch2, index1+index2);

			
		//-------------------------------------------------------------
		txt1 = "图形特技处理";
		ch1 = tree.InsertItem(txt1, ch0);
	index1 = 0x0A00;

			txt2  = "淡入浅出";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 1;	//menuItem2_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2  = "灰度处理与还原";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 2;	//GrayScale_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "底片(负片)滤镜";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 3;	//Inverse_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "浮雕及雕刻";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 4;	//Emboss_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "油画效果的制作";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 5;	//OnCanvas_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "木刻滤镜";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 6;	//OnWood_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "强光照射滤镜";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 7;	//Flashligt_Click);
		tree.SetItemData(ch2, index1+index2);
			
			txt2 = "柔化与锐化滤镜";
			ch2 = tree.InsertItem(txt2, ch1);
		index2 = 8;	//BlurAndSharpen_Click);
		tree.SetItemData(ch2, index1+index2);
}



void DoGdiplusFuns(int index1, int index2)
{
	switch (index1)
	{
		//-------------------------------------------------------------
		//txt1 = "画笔";
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
		//txt1 = "画刷";
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
		//txt1 = "文本与字体";
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
		//txt1 = "路径和区域";
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
		//txt1 = "GDI+的坐标变换";
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
		//txt1 = "GDI+的色彩变换";
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
		//txt1 = "图像的基本处理";
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
		//txt1 = "图像色彩信息的调整";
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
		//txt1 = "图形的编码与解码";
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
		//txt1 = "图形特技处理";
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
		//txt1 = "画笔";
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
		//txt1 = "画刷";
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
		//txt1 = "文本与字体";
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
		//txt1 = "路径和区域";
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
		//txt1 = "GDI+的坐标变换";
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
		//txt1 = "GDI+的色彩变换";
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
		//txt1 = "图像的基本处理";
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
		//txt1 = "图像色彩信息的调整";
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
		//txt1 = "图形的编码与解码";
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
		//txt1 = "图形特技处理";
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

//获取函数的源代码
CString GetGdiplusFunsCode(int index1, int index2)
{
	CString key=GetGdiplusFunsName(index1, index2);
	if (key.IsEmpty())
		return "未找到函数";

	//假设原代码在 <exePath> ../WalkLtDemo/WalkLtDemo设计实例.cpp
	TCHAR ModuleDirectory[_MAX_PATH];
	::GetModuleFileName(NULL, ModuleDirectory, _MAX_PATH);
	TCHAR *p=::_tcsrchr(ModuleDirectory, '\\');
	if (p)
	{
		*p=0;
		p=::_tcsrchr(ModuleDirectory, '\\'); *p=0;
		::_tcscat(ModuleDirectory, "\\WalkLtDemo\\WalkLtDemo设计实例.cpp");
	}

	CString fname=ModuleDirectory;
	FILE *pf = ::fopen(fname, "rt");
	if (!pf)
		return "打开文件失败";

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
	//------------- 全局变量的初始化 -------------------------
	gz_graphics = &gc;
	CRect rect;
	pView->GetClientRect(&rect);
	MyClient.X=rect.left; MyClient.Y=rect.top;
	MyClient.Width=rect.Width(); MyClient.Height=rect.Height();

	//------------ Action ------------------------------------
	DoGdiplusFuns(index1, index2);
}
