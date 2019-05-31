//Download by http://www.NewXing.com
// WalkLtDemo���ʵ��.cpp : implementation of the CWalkLtDemoView class
//

#include "stdafx.h"
#include "WalkLtDemo.h"

#include "WalkLtDemoDoc.h"
#include "WalkLtDemoView.h"

#include "WalkLtDemoHelp.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//���� 4244 ���뾯��
#pragma warning( disable : 4244 )


extern Rect MyClient;



void menuItem2_Click()
{
	Graphics &g=GetGraphics();
	g.Clear(Color::Black);
	Bitmap bitmap(L"demo.bmp");
	int iWidth = bitmap.GetWidth();
	int iHeight = bitmap.GetHeight();

	//��ʼ��ɫ�ʱ任����
	ColorMatrix colorMatrix=
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	ImageAttributes imageAtt;

	//��0��1�����޸�ɫ�ʱ任�������Խ����ϵ���ֵ
	//ʹ���ֻ�׼ɫ�ı��ͶȽ���
	for(float i=0.0f;i<=1.0f;i+=0.02f)
	{	
		colorMatrix.m[0][0]=i;
		colorMatrix.m[1][1]=i;
		colorMatrix.m[2][2]=i;
		colorMatrix.m[3][3]=i;
		//����ɫ��У������
		imageAtt.SetColorMatrix(&colorMatrix,
			ColorMatrixFlagsDefault, ColorAdjustTypeBitmap);
		//����ͼƬ
		g.DrawImage(
			&bitmap, Rect(0, 0, iWidth, iHeight), 
			0,0,        
			iWidth,iHeight,
			UnitPixel, 
			&imageAtt);
	}

	MyDrawString(g, "������ʾ����Ч��...", Font(L"Arial",12),
		SolidBrush(Color::White), Point(20,iHeight+20));

	//��1��0�����޸�ɫ�ʱ任�������Խ����ϵ���ֵ
	//���μ���ÿ��ɫ�ʷ���
	for(i=1.0f;i>=0.0f;i-=0.02f)
	{	
		colorMatrix.m[0][0]=i;
		colorMatrix.m[1][1]=i;
		colorMatrix.m[2][2]=i;
		colorMatrix.m[3][3]=i;
		//����ɫ��У������
		imageAtt.SetColorMatrix(&colorMatrix,
			ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);
		//����ͼƬ
		g.DrawImage(
			&bitmap, Rect(0, 0, iWidth, iHeight), 
			0,0,
			iWidth,iHeight,
			UnitPixel, 
			&imageAtt);
	}

	MyDrawString(g, "���", Font(L"Arial",12),
		SolidBrush(Color::White), Point(20,iHeight+40));
}

		
//
void GrayScale_Click()
{
	Graphics &g=GetGraphics();
	g.Clear(Color::White);
	Bitmap image(L"head.bmp");			
	int Width =image.GetWidth()-1;
	int Height =image.GetHeight()-1;

	//����ԭͼ
	g.DrawImage(&image,0, 0);
	g.TranslateTransform((REAL)image.GetWidth(),0.f);

	/*image2��image3�ֱ������������ֵ��
	�ͼ�Ȩƽ��������ĻҶ�ͼ��*/
	Bitmap *image2=image.Clone(Rect(0,0,image.GetWidth(), image.GetHeight()),PixelFormatDontCare);
	Bitmap *image3=image.Clone(Rect(0,0,image.GetWidth(), image.GetHeight()),PixelFormatDontCare);

	Color color;
	//ʹ��ƽ��ֵ���лҶȴ���
	for(int i=Width; i>=0;i--)
		for( int j=Height; j>=0;j--)
		{
			image.GetPixel(i,j, &color);	
			//���ƽ������ɫ�ʷ�����ƽ��ֵ
			int middle=(color.GetR()+color.GetG()+color.GetB())/3;
			Color colorResult(255,middle,middle,middle);
			image.SetPixel(i,j, colorResult);
		}	
	//���»��ƻҶȻ�ͼ
	g.DrawImage(&image, Rect(0, 0, Width, Height));

	//����λ����ʾ���ֵ�����лҶȴ���Ľ��
	g.TranslateTransform((REAL)image.GetWidth(),0.f);
	//ʹ�����ֵ�����лҶȴ���
	for(i=Width; i>=0;i--)
	{
		for(int j=Height; j>=0;j--)
		{
			image2->GetPixel(i,j, &color);
			int tmp=color.GetR()>color.GetG()? color.GetR():color.GetG();
			int maxcolor=tmp>color.GetB()? tmp:color.GetB();
			Color colorResult(255,maxcolor,maxcolor,maxcolor);
			//���ô����ĻҶ���Ϣ
			image2->SetPixel(i, j, colorResult);
		}
	}

	//���»��ƻҶȻ�ͼ
	g.DrawImage(image2, Rect(0, 0, Width, Height));
	//�ڵڶ��л���ͼƬ
	g.ResetTransform();
	g.TranslateTransform(0.f, (REAL)image.GetHeight());

	//ʹ�ü�Ȩƽ�������лҶȴ���	
	for(i=Width; i>=0;i--)
	{
		for(int j=Height; j>=0;j--)
		{
			image3->GetPixel(i, j, &color);	
			int R=(int)(0.3f*color.GetR());
			int G=(int)(0.59f*color.GetG());
			int B=(int)(0.11f*color.GetB());

			Color colorResult(255,R,G,B);
			//���ô����ĻҶ���Ϣ
			image3->SetPixel(i, j, colorResult);
		}	
	}
	//���»��ƻҶȻ�ͼ
	g.DrawImage(image3, Rect(0, 0, Width, Height));
	
	g.TranslateTransform((REAL)image.GetWidth(),0.f);
	//�ҶȵĻ�ԭ��ʾ����ԭʹ�����ֵ������ĻҶ�ͼ��image2
	for(i=Width; i>0;i--)
	{
		for(int j=Height; j>0;j--)
		{
			image2->GetPixel(i,j, &color);
			int R=color.GetR();
			int G=color.GetG();
			int B=color.GetB();
			//�ֱ��RGB����ɫ�ʷ�������α��ɫ��ԭ

			//���к�ɫ�����Ļ�ԭ
			if(R<127)
				R=0;
			if(R>=192)
				R=255;
			if(R<=191&&R>=128)
				R=4*R-510;

			/*������ɫ�����Ļ�ԭ,Ϊ�˻�ԭ�����ɫ�����ٴβμӱȽϣ�
			��������һ������YES��ʾG�Ƿ��Ѿ��μ��˱Ƚ�*/

			bool yes;
			yes=false;
			if(G<=191&&G>=128&&(!yes))
			{
				G=255;
				yes=true;
			}
			if(G>=192&&(!yes))
			{
				G=1022-4*G;
				yes=true;
			}
			if(G<=63&&(!yes))
			{
				G=254-4*G;
				yes=true;
			}
			if(G<=127&&G>=67&&(!yes))
				G=4*G-257;
			
			//������ɫ�����Ļ�ԭ
			if(B<=63)
				B=255;
			if(B>=128)
				B=0;
			if(B>=67&&B<=127)
				B=510-4*B;
			
			//��ԭ���α��ɫ
			Color colorResult(255,R,G,B);
			//����ԭ���RGB��Ϣ����д��λͼ
			image2->SetPixel(i, j, colorResult);
					
		}	
	}
	//���»��ƻ�ԭ���α��ɫλͼ
	//���»��ƻҶȻ�ͼ
	g.DrawImage(image2, Rect(0, 0, Width, Height));

	delete image2;
	delete image3;
}

//
void Inverse_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.7f,0.7f);
	
	Bitmap image(L"head.bmp");				
	int Width =image.GetWidth();
	int Height =image.GetHeight();

	Color colorTemp,color2;
	Color color;
	//����ԭͼ
	graphics.DrawImage(&image, Rect(0, 0, Width, Height));
	
	for(int  i=0;i<Width;i++)
	{
		for( int j=0; j<Height;j++)
		{
			image.GetPixel(i, j, &color);
			//��ɫ�ʽ��з�ת����õ�ƬЧ��
			int r=255-color.GetRed();
			int g=255-color.GetGreen();
			int b=255-color.GetBlue();
			Color colorResult(255,r,g,b);
			//����ԭ���RGB��Ϣ����д��λͼ
			image.SetPixel(i, j, colorResult);
		}
		//��̬���Ƶ�Ƭ�˾�Ч��ͼ
		graphics.DrawImage(&image, Rect(Width, 0, Width, Height));
	}
	//���Ѿ�ʵ���˵�ƬЧ����λͼ�ٷ�ɫ(�ָ���ԭͼ)
	for(i=0;i<Width;i++)
	{
		for( int j=0; j<Height;j++)
		{
			image.GetPixel(i, j, &color);
			int r=255-color.GetRed();
			int g=255-color.GetGreen();
			int b=255-color.GetBlue();
			Color colorResult(255,r,g,b);
			//����ԭ���RGB��Ϣ����д��λͼ
			image.SetPixel(i, j, colorResult);
		}
		//���ƾ������η�ɫ��λͼ
		graphics.DrawImage(&image, Rect(Width*2, 0, Width, Height));
	}
}

//
void Emboss_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.7f,0.7f);

	Bitmap image(L"head.bmp");				
	int Width =image.GetWidth();
	int Height =image.GetHeight();

	//image2:���е�̴���
	Bitmap *image2=image.Clone(Rect(0,0,Width,Height), PixelFormatDontCare);

	//����ԭͼ
	graphics.DrawImage(&image, Rect(0, 0, Width, Height));
	Color color, colorTemp,colorLeft;

	//����ͼƬ�ĸ�����
	//���η���ÿ�����ص�RGBֵ
	for(int i=Width-1; i>0;i--)
	{
		for( int j=Height-1; j>0;j--)
		{
			//��ȡ�����������ص�R��G��Bֵ
			image.GetPixel(i, j, &color);
			image.GetPixel(i-1, j-1, &colorLeft);
			//���������Ͻ����ص�RGB����֮��
			//67������ͼƬ����ͻҶȣ�128������������������ֵ��õ���ͬ��Ч��
			int r=max(67,min(255,
				abs(color.GetRed()-colorLeft.GetRed()+128)));
			int g=max(67,min(255,
				abs(color.GetGreen()-colorLeft.GetGreen()+128)));
			int b=max(67,min(255,
				abs(color.GetBlue()-colorLeft.GetBlue()+128)));
			Color colorResult(255,r,g,b);
			//��������RGBֵ��д��λͼ
			image.SetPixel(i, j,colorResult);
		}

		//���Ƹ���ͼ
		graphics.DrawImage(&image, Rect(Width+10, 0, Width, Height));
	}

	//����ͼƬ�ĵ�̴���
	for(i=0; i<Height-1;i++)
	{
		for( int j=0; j<Width-1;j++)
		{
			image2->GetPixel(j, i, &color);	
			image2->GetPixel(j+1, i+1, &colorLeft);	
			//���������½����صķ���֮��
			//67������ͼƬ����ͻҶȣ�128������������������ֵ��õ���ͬ��Ч��
			int r=max(67,min(255,abs(color.GetRed()-colorLeft.GetRed()+128)));
			int g=max(67,min(255,abs(color.GetGreen()-colorLeft.GetGreen()+128)));
			int b=max(67,min(255,abs(color.GetBlue()-colorLeft.GetBlue()+128)));
			Color colorResult(255,r,g,b);
			image2->SetPixel(j, i,colorResult);
		}

		//���Ƶ��ͼ
		graphics.DrawImage(image2, Rect(Width*2+20, 0, Width, image.GetHeight()));
	}
	delete image2;
}

void CreatePenFromBrush_Click()
{
	Graphics &g=GetGraphics();
	g.Clear(Color::White);
	//�������Խ��仭ˢ
	LinearGradientBrush LineargradientBrush(Rect(0,0,10,10),
		Color::Blue,Color::Red, LinearGradientModeBackwardDiagonal);
	//�����Խ��仭ˢ�й��컭��
	Pen pen(&LineargradientBrush);
	pen.SetWidth(10);
	//���ƾ���
	g.DrawRectangle(&pen,10,10,100,100);

	//װ������ͼƬ
	Bitmap image(L"butterfly.bmp");
	//��������ˢ
	TextureBrush  tBrush(&image);
	//����ˢ���뻭�ʵĹ��캯��
	Pen texturedPen(&tBrush,42);

	//���ñ��������ߵ���ֹ�㼰���Ƶ�
	Point p1(10, 100);   
	Point c1= Point(100, 10);   
	Point c2= Point(150, 150);  
	Point p2= Point(200, 100);  
	g.TranslateTransform(130,0);
	//���Ʊ���������
	g.DrawBezier(&texturedPen, p1, c1, c2, p2);
}

//���ʵ�������ʾ
void DashStyle_Custom_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 5);

	//�����ı�������뷽ʽ������
	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentNear);
	fmt.SetLineAlignment(StringAlignmentCenter);
	//����
	Font font(L"Arial",12);
	SolidBrush sBrush(Color::Black);
	graphics.TranslateTransform(0,30);

	int i=0;
	//�ֱ�ʹ�ó������������ͻ���ֱ��
	for(;i<5;i++)
	{
		//��������
		pen.SetDashStyle((DashStyle)i);
		graphics.DrawLine(&pen, 10, 30*i, 260, 30*i);
		//�����ǰ���͵�����
		CString s; s.Format(_T("%d"), i+1);
		MyDrawString(graphics, s, font, sBrush, PointF(260.f,30.f*i), fmt);
		s.ReleaseBuffer();
	}

	//ʹ���Զ���������
	float dashVals[]=
	{
		5.0f,   // �߳�5������
		2.0f,   // ���2������
		15.0f,  // �߳�15������
		4.0f    // ���4������
	};
	pen.SetDashPattern(dashVals, 4);
	pen.SetColor(Color::Red);
	graphics.DrawLine(&pen, 10, 30*i, 260, 30*i);
	CString s; s.Format(_T("%d"), i+1);
	MyDrawString(graphics, s, font, sBrush, PointF(260.f,30.f*i), fmt);
}

void Pen_Align_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	
	Pen pen(Color::Gray, 1.0f);

	Pen pen2(Color(155,255,0,0),10);
	int i=0;
	for(; i<5;i++)
	{
		pen2.SetAlignment((PenAlignment)i);
		graphics.DrawLine(&pen2, Point(0,10), Point(60,10));
		graphics.TranslateTransform(70,0);
	}

	graphics.ResetTransform();
	graphics.DrawLine(&pen,0,10,600,10);
}

void Pen_Tranform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����һ֧���Ϊ5�ĺ�ɫ����
	Pen pen(Color::Red, 3.0f);
	//�����ʴӴ�ֱ��������6����ˮƽ���򱣳ֲ���
	pen.ScaleTransform(1, 6);
	//ʹ��δ����ת����Ļ��ʻ�Բ
	graphics.DrawEllipse(&pen, 0, 50, 80, 80);
	//60����ת
	graphics.TranslateTransform(100,0);
	pen.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 0, 50, 80, 80);
	//120����ת
	graphics.TranslateTransform(100,0);
	pen.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 0, 50, 80, 80);
	//180����ת
	graphics.TranslateTransform(100,0);
	pen.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 0, 50, 80, 80);
}
//��ñ��ʾ
void Pen_LineCap_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�����ı�������뷽ʽ������
	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentNear);
	fmt.SetLineAlignment(StringAlignmentCenter);
	//����
	Font font(L"Arial",12);
	SolidBrush sBrush(Color::Black);

	//�������Ϊ15�Ļ���
	Pen pen(Color::Black,15);
	//�ֱ�ʹ�ò�ͬ����ñ
	LineCap lincap[]=
	{
		LineCapFlat,
		LineCapSquare,
		LineCapRound,
		LineCapTriangle,

		LineCapNoAnchor,
		LineCapSquareAnchor,
		LineCapRoundAnchor,
		LineCapDiamondAnchor,
		LineCapArrowAnchor,

		LineCapCustom,

		LineCapAnchorMask
	};

	for (int i=0; i<sizeof(lincap)/sizeof(LineCap); i++)
	{
		pen.SetStartCap(lincap[i]);//���
		pen.SetEndCap(lincap[i]);//�յ�

		graphics.DrawLine(&pen,50,10,300,10);
		//�����ǰ��ñ���ͣ�LineCapö�ٳ�Ա����
		CString s; s.Format(_T("%d"), lincap[i]);
		MyDrawString(graphics, s, font, sBrush, PointF(320.f,10.f), fmt);
		//ƽ�ƻ�ͼƽ��
		graphics.TranslateTransform(0,30);
	}
}

//���ʵ�͸����֧��
void Pen_TransColor_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�ֱ�����ɫ����ɫ����
	Pen	blue(Color::Blue);
	Pen red(Color::Red);
	//��������
	int y = 256;
	for (int x = 0; x < 256; x += 5)
	{
		graphics.DrawLine(&blue, 0, y, x, 0);
		graphics.DrawLine(&red, 256, x, y, 256);  
		y -= 5;
		//��ʱ�Բ鿴��̬Ч��
		::Sleep(20);
	}		
	//ʹ����ɫ���ʻ��Ʋ�ͬ͸���ȵ�����
	//͸�������ϵ������εݼ�
	for (y = 0; y < 256; y++)
	{
		Pen pen(_MakeA_RGB(y,Color::Green));  
		graphics.DrawLine(&pen, 0, y, 256, y);
		//��ʱ�Ա�鿴��̬Ч��
		::Sleep(20);
	}

	//ʹ����ɫ���ʻ��Ʋ�ͬ͸���ȵ�����
	//͸�������������εݼ�
	for (x = 0; x < 256; x++)
	{
		Pen pen(_MakeA_RGB(x, Color::Blue));
		graphics.DrawLine(&pen, x, 100, x, 200);
		//��ʱ�Բ鿴��̬Ч��
		::Sleep(20);
	}
}
//�򵥵ĵ�ɫ��ˢʾ��
void Brush_SolidBrush_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//������ɫ��ˢ
	SolidBrush greenBrush(Color::Green);
	//�������ߡ�����ζ˵�����
	PointF point1(100.0f, 100.0f);
	PointF point2(200.0f, 50.0f);
	PointF point3(250.0f, 200.0f);
	PointF point4(50.0f, 150.0f);
	PointF point5(100.0f, 100.0f);
	PointF points[]={point1, point2, point3, point4};
	//���պ�����
	graphics.FillClosedCurve(&greenBrush, points, 4, FillModeAlternate, 1.0f);

	//��������(�պ�)
	PointF poly[]={point1, point2, point3, point4,point5};
	//����һ��λ���������
	graphics.TranslateTransform(300,0);
	graphics.FillPolygon(&greenBrush, poly, 5, FillModeAlternate);
}
//�����Ҷ����
void Brush_FillVurve_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//������ɫ��ˢ
	SolidBrush greenBrush(Color::Green);
	int cx,cy;
	//�Ե�ǰ���ڵ����ĵ������Ҷ����
	cx=MyClient.Width/2;
	cy=MyClient.Height/2;
	//����"Ҷ"��
	int LeafLength=80;
	//����ҶƬ����=2* LeafNum
	int LeafNum=5;
	double x,y,x2,y2,r;

	//����һ��ͼ��·����������������Ҷ���ߵı߽���
	GraphicsPath tmpPath(FillModeAlternate);
	//�������߽߱����ݣ��Ƕȱ仯Ϊһ��PI*2
	for(float i=0.0f;i<PI*2+0.1f;i+=(float)PI/180)
	{
		r=(int)abs(LeafLength*cos(double(LeafNum*i)));
		x=r*cos(i);
		y=r*sin(i);
		x2=cx+x;
		y2=cy+y;
		/*�����ߵı߽���Ϣ������ʱ·��,�����Ҫ�鿴��Щ��Ϣ�����ɵ�����
		�������ڴ˼���graphics.DrawLine(&pen,x2,y2,x2-1,y2-1);*/
		tmpPath.AddLine((int)x2,(int)y2,(int)x2,(int)y2);
	}

	//���·��
	graphics.FillPath(&greenBrush, &tmpPath);

	//��������������
	Pen pen(Color::Gray);
	graphics.DrawLine(&pen,0,cy,cx*2,cy);
	graphics.DrawLine(&pen,cx,0,cx,cy*2);
}
//Ӱ�߻�ˢʾ��
void Brush_HatchBrush_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����Ӱ�߻�ˢ��ǰ��ɫ��
	Color black=Color::Black;
	Color white=Color::White;

	//ʹ�õ�һ�ַ���Ӱ�߻�ˢ
	HatchBrush brush(HatchStyleHorizontal, black, white);
	graphics.FillRectangle(&brush, 20, 20, 100, 50);

	//ʹ�õڶ��ַ���Ӱ�߻�ˢ
	HatchBrush brush1(HatchStyleVertical, black, white);
	graphics.FillRectangle(&brush1, 120, 20, 100, 50);

	//ʹ�õ����ַ���Ӱ�߻�ˢ
	HatchBrush brush2(HatchStyleForwardDiagonal, black, white);
	graphics.FillRectangle(&brush2, 220, 20, 100, 50);

	//ʹ�õ����ַ���Ӱ�߻�ˢ
	HatchBrush brush3(HatchStyleBackwardDiagonal, black, white);
	graphics.FillRectangle(&brush3, 320, 20, 100, 50);

	//ʹ�õ����ַ���Ӱ�߻�ˢ
	HatchBrush brush4(HatchStyleCross, black, white);
	graphics.FillRectangle(&brush4, 420, 20, 100, 50);

	//ʹ�õ����ַ���Ӱ�߻�ˢ
	HatchBrush brush5(HatchStyleDiagonalCross, black, white);
	graphics.FillRectangle(&brush5, 520, 20, 100, 50);
}
//�оٳ����з���Ӱ�߻�ˢ
void Brush_EnumAllStyle_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�趨��ˢ��ǰ��ɫΪ��ɫ������ɫΪ��ɫ
	Color black=Color::Black;
	Color white=Color::White;

	//Ԥ�����������Ŀ�ȼ��߶�
	int WIDTH=140;
	int HEIGHT=40;

	//�趨����ı�������Ϣ
	SolidBrush redBrush(Color::Red);
	Font myFont(L"Arial", 10);

	//column_count������ÿһ���ܹ����ƾ��ε�����
	int column_count=MyClient.Width/WIDTH;
	int rol=0;
	int column=0;

	//�ڵ�ǰ����ʹ�����е�Ӱ�߻�ˢ�ַ��������
	Pen pen(Color::Blue, 1);
	for (int i=HatchStyleHorizontal; i<HatchStyleTotal; i++)
	{
		HatchStyle style=(HatchStyle)i;
		//���һ���Ѿ�������ϣ�����
		if (rol>column_count-1)
		{
			column+=2;
			rol=0;
		}
		//������ʱ��ˢ
		HatchBrush brush_tmp(style, black, white);
		//�����Σ����ÿ��ΪWIDTH-20��Ŀ�����þ���֮���������
		graphics.FillRectangle(&brush_tmp, rol*WIDTH, column*HEIGHT, WIDTH-20, HEIGHT);
		//���ƾ��α߿�
		graphics.DrawRectangle(&pen, rol*WIDTH, column*HEIGHT, WIDTH-20, HEIGHT);

		//��ʾÿ�ֻ�ˢ����ö������
		//�����ı��������
		RectF layoutRect(rol*WIDTH, (column+1)*HEIGHT, WIDTH, HEIGHT);
		StringFormat format;
		//�����ı������ʽ��ˮƽ����ֱ����
		format.SetAlignment(StringAlignmentNear);
		format.SetLineAlignment(StringAlignmentCenter);
		//�ھ��ο��������ö��ֵ
		CString s; s.Format(_T("%d"), style);
		MyDrawString(graphics, s, myFont, redBrush, layoutRect, format);
		rol+=1;
	}
}
//���û���ԭ��
void Brush_SetRenderingOrigin_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�趨��ˢ��ǰ��ɫΪ��ɫ������ɫΪ��ɫ
	Color black=Color::Black;
	Color white=Color::White;
	HatchBrush hatchBrush(HatchStyleDarkDownwardDiagonal,black,white);

	//����ֱ�������8�����Σ�ʹ��Ĭ�ϵĻ�ˢԭ��
	for(int i=0;i<8;i++)
	{
		graphics.FillRectangle(&hatchBrush, 0, i*50, 100, 50);  
	}

	//ʹ�ò�ͬ�Ļ���ԭ������������
	for(i=0;i<8;i++)
	{
		//���û�ˢԭ��(ˮƽ�������)
		graphics.SetRenderingOrigin(i, 0);
		graphics.FillRectangle(&hatchBrush, 100, i*50, 100, 50);
	}
}
//����ˢ�Ĳ�ͬ���ط�ʽ
void Brush_Texture_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"����",12);

	//��������ˢ�Ĳ�ͬ�������
	RectF rect1(10, 10, 200,200);
	RectF rect2(210, 10, 200, 200);
	RectF rect3(410, 10, 200, 200);

	//װ������ͼƬ
	Bitmap image(L"nemo.bmp");
	//��������ˢ1��ʹ��Ĭ�ϵķ�ʽ
	TextureBrush tBrush(&image);
	//ʹ������ˢ���Բ������
	graphics.FillEllipse(&tBrush,rect1);
	//����Բ��
	graphics.DrawEllipse(&pen,rect1);
	MyDrawString(graphics, "ͼƬԭʼ��С", myFont, brush, PointF(40,220));

	//��������ˢ2��ֻʹ�ø���ͼƬ�Ĳ�������
	TextureBrush tBrush2(&image, Rect(55,35,55,35));
	graphics.FillEllipse(&tBrush2,rect2);
	graphics.DrawEllipse(&pen,rect2);
	MyDrawString(graphics, "ʹ�ò��ֽ�ͼ", myFont, brush, PointF(240,220)); 

	//��������ˢ3����ʹ��ͼƬ�Ļ�ˢ��������
	TextureBrush tBrush3(&image);
	//�Ի�ˢ����50%������
	Matrix mtr(0.5f, 0.0f, 0.0f,0.5f, 0.0f, 0.0f);
	tBrush3.SetTransform(&mtr);
	graphics.FillEllipse(&tBrush3,rect3);
	graphics.DrawEllipse(&pen,rect3);
	MyDrawString(graphics, "������СͼƬ",myFont,brush, PointF(440,220));
}

//ʹ��ͼƬ���з�ʽ
void Brush_Texture_WrapMode_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 13);

	//װ������ͼƬ
	Bitmap image(L"nemo.bmp");
	//��������ˢ
	TextureBrush tBrush(&image);
	//����ˢ��������
	Matrix mtr(0.5f, 0.0f, 0.0f,0.5f, 0.0f, 0.0f);
	tBrush.SetTransform(&mtr);

	int i=0;
	//��ͼƬ��ʹ�����з�ʽ
	tBrush.SetWrapMode(WrapModeClamp);
	graphics.FillRectangle(&tBrush, Rect(i*150,0,150,150));
	graphics.DrawRectangle(&pen, Rect(i*150,0,150,150));
	MyDrawString(graphics, "Clamp", myFont,brush, PointF(0,155)); 

	i+=1;
	//��ͼƬʹ��ƽ�����з�ʽ	
	tBrush.SetWrapMode(WrapModeTile);
	graphics.FillRectangle(&tBrush, Rect(i*150+10,0,150,150));
	graphics.DrawRectangle(&pen, Rect(i*150+10,0,150,150));
	MyDrawString(graphics, "Tile",myFont,brush, PointF(170,155) ); 

	//��ͼƬʹ��ˮƽ��ת���з�ʽ
	i+=1;
	tBrush.SetWrapMode(WrapModeTileFlipX);
	graphics.FillRectangle(&tBrush, Rect(i*150+20,0,150,150));
	graphics.DrawRectangle(&pen, Rect(i*150+20,0,150,150));

	MyDrawString(graphics, "TileFlipX",myFont,brush, PointF(320,155)); 

	//��ͼƬʹ�ô�ֱ��ת���з�ʽ
	tBrush.SetWrapMode(WrapModeTileFlipY);
	graphics.FillRectangle(&tBrush, Rect(0,180,150,150));
	graphics.DrawRectangle(&pen, Rect(0,180,150,150));
	MyDrawString(graphics, "TileFlipY",myFont,brush,  PointF(0,335)); 

	//��ͼƬʹ��ˮƽ����ֱͬʱ��ת���з�ʽ
	tBrush.SetWrapMode(WrapModeTileFlipXY);
	graphics.FillRectangle(&tBrush, Rect(160,180,150,150));
	graphics.DrawRectangle(&pen, Rect(160,180,150,150));
	MyDrawString(graphics, "TileFlipXY",myFont,brush, PointF(170,335)); 
}
//����ˢ�ı任
void Brush_TextureTransform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//Ϊ���ֲ�ͬ�ı任��ʽ�Ļ�ˢ�����������
	RectF rect1= RectF (10, 10, 200,200);
	RectF rect2= RectF (210, 10, 200, 200);
	RectF rect3= RectF (410, 10, 200, 200);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"����", 12);

	//װ������ͼƬ
	Bitmap image(L"nemo.bmp");
	//��������ˢ
	TextureBrush tBrush(&image);

	//����ˢ��ת30��
	tBrush.RotateTransform(30);                     
	graphics.FillEllipse(&tBrush,rect1);
	graphics.DrawEllipse(&pen,rect1);
	MyDrawString(graphics, "��ת30��",myFont,brush, PointF(40,220)); 

	//���ñ任���󣺻ָ����仯ǰ��״̬
	tBrush.ResetTransform();
	//����ˢ��ˮƽ��������������
	tBrush.ScaleTransform(3, 1);
	graphics.FillEllipse(&tBrush, rect2);
	graphics.DrawEllipse(&pen,rect2);
	MyDrawString(graphics, "������������",myFont,brush,  PointF(240,220)); 

	//ƽ�Ʊ任
	tBrush.ResetTransform();
	//����ˢ��ˮƽ������ƽ��30������
	tBrush.TranslateTransform(30, 0, MatrixOrderAppend);
	graphics.FillEllipse(&tBrush, rect3);
	graphics.DrawEllipse(&pen,rect3);
	MyDrawString(graphics, "����ƽ��30������",myFont,brush, PointF(440,220)); 
}
//��ѯ��ˢ�ı任��Ϣ
void Brush_GetTextureMatrix_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Matrix matrix;
	float elements[6];
	RectF rect1(10, 10, 200,200);
	Pen pen(Color::Black, 2);
	SolidBrush brush(Color::Black);

	Bitmap image(L"nemo.bmp");
	TextureBrush tBrush(&image);
	//������������任
	tBrush.RotateTransform(30);
	tBrush.TranslateTransform(5,3);
	tBrush.ScaleTransform(0.5f,2.0f);

	//��ȡĿǰ�Ѿ����еĻ�ˢ�任
	tBrush.SetTransform(&matrix);
	//�Ӿ��ε�����
	matrix.GetElements(elements);	
	graphics.FillEllipse(&tBrush,rect1);
	graphics.DrawEllipse(&pen,rect1);

	//��������Ԫ��
	for(int j = 0; j <6; ++j)
	{
		CString s; s.Format(_T("%d %f ����Ԫ��ֵ"), j, elements[j]);
		AfxMessageBox(s);
	}
}
//���Խ��仭ˢ����
void Brush_LinearGradientBrush_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����һ���ɺ�ɫ����ɫ����Ļ�ˢ:ˮƽ�任����Ŀ��Ϊ40
	//��ֱ���򲻽���ɫ�ʽ���
	LinearGradientBrush linGrBrush(
		Point(0, 0),
		Point(40, 0),
		Color::Red,  //���ɫ��	
		Color::Blue);  //ֹ��ɫ��

	//����һ��ɫ�ʳʶԽ��߱任�����������СΪ40*40
	LinearGradientBrush linGrBrush2(
		Point(0, 0),
		Point(40, 40),
		Color::Red,  //���ɫ��	
		Color::Blue); //ֹ��ɫ��	

	//�ֱ���ʾ��ͬ�����Խ��仭ˢ��Ŀ������Ĳ�ͬ���Ч��
	graphics.FillRectangle(&linGrBrush, 0, 0, 200, 200);
	graphics.FillRectangle(&linGrBrush2, 240, 0, 200, 200);

	Pen pen(Color::Gray,1);
	//�ڶԽ��߷����ϻ��Ƶ�����ˢ���������
	for(int i=0;i<5;i++)
	{
		graphics.DrawRectangle(&pen, 240+i*40,i*40,40,40);
	}
}
//�������Խ��仭ˢ����䷽ʽ
void Brush_LinearArrange_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 13);

	//����һ��ɫ�ʳʶԽ��߱任�����������СΪ40*40
	LinearGradientBrush linGrBrush(
		Point(0, 0),
		Point(40, 40),
		Color::Red, //���ɫ��	
		Color::Blue); //ֹ��ɫ��	

	int i=0;
	//�Խ��仭ˢʹ��ƽ�����з�ʽ(Ĭ�Ϸ�ʽ)
	linGrBrush.SetWrapMode(WrapModeTile);
	//���һ����СΪ160��������
	graphics.FillRectangle(&linGrBrush, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,0,160,160));
	MyDrawString(graphics, "Tile", myFont, brush, Point(20,165)); 

	//�Խ��仭ˢʹ��ˮƽ��ת���з�ʽ
	i+=1;
	linGrBrush.SetWrapMode(WrapModeTileFlipX);
	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(160,0);
	graphics.FillRectangle(&linGrBrush, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,160,0,160));
	MyDrawString(graphics, "TileFlipX", myFont, brush, Point(170,165)); 

	//�Խ��仭ˢʹ�ô�ֱ��ת���з�ʽ
	linGrBrush.SetWrapMode(WrapModeTileFlipY);
	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(0,200);
	graphics.FillRectangle(&linGrBrush, Rect(0,200,160,160));
	graphics.DrawRectangle(&pen, Rect(0,200,200,160));
	MyDrawString(graphics, "TileFlipY",myFont,brush, Point(0,375)); 

	//�Խ��仭ˢʹ��ˮƽ����ֱͬʱ��ת���з�ʽ
	linGrBrush.SetWrapMode(WrapModeTileFlipXY);
	graphics.SetRenderingOrigin(160,200);
	graphics.FillRectangle(&linGrBrush, Rect(160,200,160,160));
	graphics.DrawRectangle(&pen, Rect(160,200,160,160));
	MyDrawString(graphics, "TileFlipXY",myFont,brush, Point(170,375)); 

	//��ע���仭ˢ��������Ĵ�С��������
	Pen pen2(Color::Gray, 1);
	for(i=0;i<8;i++)
		graphics.DrawLine(&pen2,0,i*40,320,i*40);
	for(i=0;i<9;i++)
		graphics.DrawLine(&pen2,i*40,0,i*40,360);
}
//�������Խ��仭ˢ�Ľ���ģʽ
void Brush_LinearGradientMode_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 12);

	//����һ��ˮƽ���仭ˢ����С40*20
	LinearGradientBrush linGrBrush1(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,LinearGradientModeHorizontal);  

	//����һ����ֱ���仭ˢ
	LinearGradientBrush linGrBrush2(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,LinearGradientModeVertical); 

	//�����ϵ����µĽ��仭ˢ
	LinearGradientBrush linGrBrush3(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,LinearGradientModeForwardDiagonal);  

	//�����ϵ����µĽ��仭ˢ
	LinearGradientBrush linGrBrush4(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,LinearGradientModeBackwardDiagonal);  

	int i=0;
	//ʹ��ˮƽ����Ļ�ˢ�������
	graphics.FillRectangle(&linGrBrush1, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,0,160,160));
	MyDrawString(graphics, "ˮƽ����",myFont,brush, PointF(20,165));

	i+=1;
	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(160,0);
	//ʹ�ô�ֱ����Ļ�ˢ�������
	graphics.FillRectangle(&linGrBrush2, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,160,0,160));
	MyDrawString(graphics, "��ֱ����",myFont,brush, PointF(170,165)); 

	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(0,200);
	//ʹ�ô����ϵ����½���Ļ�ˢ�������
	graphics.FillRectangle(&linGrBrush3, Rect(0,200,160,160));
	graphics.DrawRectangle(&pen, Rect(0,200,200,160));
	MyDrawString(graphics, "����->����",myFont,brush, PointF(0,375)); 

	graphics.SetRenderingOrigin(160,200);
	graphics.FillRectangle(&linGrBrush4, Rect(160,200,160,160));
	//ʹ�ô����ϵ����½���Ļ�ˢ�������
	graphics.DrawRectangle(&pen, Rect(160,200,160,160));
	MyDrawString(graphics, "����->����",myFont,brush, PointF(170,375)); 

	//�ڲ�ͬ�������б�ע���彥�䷽��ľ���
	Pen pen2(Color::Gray, 1);
	for(i=0;i<18;i++)
		graphics.DrawLine(&pen2,0,i*20,320,i*20);
	for(i=0;i<9;i++)
		graphics.DrawLine(&pen2,i* 40,0,i*40,360);
}
//������ƫת�Ƕ�
void Brush_LinearAngle_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 12);

	//����һ��������ƫת�Ƕ�Ϊ30�ȵĽ��仭ˢ����С40*20
	LinearGradientBrush linGrBrush1(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,30.0f);  
	//����һ��������ƫת�Ƕ�Ϊ45�ȵĽ��仭ˢ
	LinearGradientBrush linGrBrush2(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,45.0f); 
	//����һ��������ƫת�Ƕ�Ϊ90�ȵĽ��仭ˢ
	LinearGradientBrush linGrBrush3(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,90.0f);  
	//����һ��������ƫת�Ƕ�Ϊ180�ȵĽ��仭ˢ
	LinearGradientBrush linGrBrush4(
		Rect(0, 0, 40, 20),
		Color::Red,  
		Color::Blue,180.0f);  

	int i=0;
	//ʹ��ƫת�Ƕ�Ϊ30�ȵĽ��仭ˢ�������
	graphics.FillRectangle(&linGrBrush1, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,0,160,160));
	MyDrawString(graphics, "30��ƫת",myFont,brush, PointF(20,165)); 

	i+=1;
	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(160,0);
	//ʹ��ƫת�Ƕ�Ϊ45�ȵĽ��仭ˢ�������
	graphics.FillRectangle(&linGrBrush2, Rect(i*160,0,160,160));
	graphics.DrawRectangle(&pen, Rect(i*160,160,0,160));
	MyDrawString(graphics, "45��ƫת",myFont,brush, PointF(170,165));

	//���û�ͼƽ��ԭ��
	graphics.SetRenderingOrigin(0,200);
	//ʹ��ƫת�Ƕ�Ϊ90�ȵĽ��仭ˢ�������
	graphics.FillRectangle(&linGrBrush3, Rect(0,200,160,160));
	graphics.DrawRectangle(&pen, Rect(0,200,200,160));
	MyDrawString(graphics, "90��ƫת",myFont,brush, PointF(0,375));

	graphics.SetRenderingOrigin(160,200);
	graphics.FillRectangle(&linGrBrush4, Rect(160,200,160,160));
	//ʹ��ƫת�Ƕ�Ϊ180�ȵĽ��仭ˢ�������
	graphics.DrawRectangle(&pen, Rect(160,200,160,160));
	MyDrawString(graphics, "180��ƫת",myFont,brush, PointF(170,375));

	//�ڲ�ͬ�������б�ע���彥�䷽��ľ���
	Pen pen2(Color::Gray, 1);
	for(i=0;i<18;i++)
		graphics.DrawLine(&pen2,0,i*20,320,i*20);
	for(i=0;i<9;i++)
		graphics.DrawLine(&pen2,i* 40,0,i*40,360);
}

//��ɫ���仭ˢ
void Brush_LinearInterpolation_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�������ֲ��뽥���ɫ��
	Color colors[] = 
	{
		Color::Red,   // ��ɫ
		Color::Green,//����ɫΪ��ɫ
		Color::Blue // ��ɫ
	};

	float positions[] = 
	{
		0.0f,   // �ɺ�ɫ��
		0.3f,   // ��ɫʼ�ڻ�ˢ���ȵ�����֮һ
		1.0f   // ����ɫֹ
	};  

	//����һ���Ӻ�ɫ����ɫ�Ľ��仭ˢ
	LinearGradientBrush linGrBrush(
		Point(0, 0), 
		Point(180, 0), 
		Color::Black,Color::White);

	//���ý��仭ˢ�Ķ�ɫ������Ϣ
	//linGrBrush.InterpolationColors=clrBlend;
	linGrBrush.SetInterpolationColors(colors, positions, 3);
	//ʹ�ö�ɫ���仭ˢ���Ŀ������
	graphics.FillRectangle(&linGrBrush, 0, 0, 180, 100);

	//ʹ����ͨ�ķ���ʵ�ֶ�ɫ����
	//�ɺ쵽�̣�����60
	LinearGradientBrush linGrBrush1(
		Point(0, 0), 
		Point(60, 0),
		Color::Red,         
		Color::Green);  
	//���̵���������120
	LinearGradientBrush linGrBrush2(
		Point(60, 0), 
		Point(181, 0),
		Color::Green,        
		Color::Blue);  
	//�ֱ�ʹ��������ˢ����������������γɶ�ɫ����
	graphics.FillRectangle(&linGrBrush1, 0, 120, 60, 100);
	graphics.FillRectangle(&linGrBrush2, 60, 120, 120, 100);
}
//�Զ��彥����̣�������
void Brush_LinearCustomize_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Black);
	Font myFont(L"����", 12);
	//����һ��˫ɫ���仭ˢ
	LinearGradientBrush linGrBrush(
		Point(0, 0),
		Point(250, 0),
		Color::Red,   
		Color::Blue);  

	//��������ʹ��Ĭ�Ͻ��䷽ʽ���ľ��Σ��������Ƚ�
	graphics.FillRectangle(&linGrBrush, 0, 0, 250, 15);
	graphics.FillRectangle(&linGrBrush, 500, 0, 250, 15);

	//���θı�ϳɵ�λ��
	int row=1;
	for(float i=0.0f;i<1.0f;i+=0.1f)
	{
		linGrBrush.SetBlendTriangularShape(i);	
		graphics.FillRectangle(&linGrBrush, 0, row*15, 250, 15);
		row++;
	}
	MyDrawString(graphics, "�ı�ϳɵ�λ��",
		myFont,brush, PointF(40,200));

	//���θı��ɫ�ϳ�����
	row=1;
	for(i=0.0f;i<1.0f;i+=0.1f)
	{
		//���ϳɵ����λ�����������������50%��
		linGrBrush.SetBlendTriangularShape (0.5f,i);	
		graphics.FillRectangle(&linGrBrush, 500, row*15, 250, 15);
		row++;
	}
	MyDrawString(graphics, "�ı�ɫ�ʺϳ�����",
		myFont,brush, PointF(540,200));

}
//�����������ߵĽ��仭ˢ		
void Brush_LinearGradientBrush_BellShape_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Rect myRect(10, 10, 150, 75);
	//�������Խ��仭ˢ
	LinearGradientBrush myLGBrush(
		myRect,Color::Blue,Color::Red,0.0f,true);

	//ʹ��Ĭ�ϵ����Խ��仭ˢ�����Բ
	graphics.FillEllipse(&myLGBrush, myRect);

	//������������óɻ����������ߵĽ���
	myLGBrush.SetBlendBellShape(.5f, 1.0f);

	//ʹ���Զ��彥����̵Ļ�ˢ�����Բ
	graphics.TranslateTransform(160,0);
	graphics.FillEllipse(&myLGBrush, myRect);
}

void Brush_PathGradientBrush_Star_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Gray,1);
	SolidBrush pthGrBrush(Color::Red);
	SolidBrush blackbrush(Color::Blue);
	graphics.TranslateTransform(20,20);

	//�������ǵ�10���ߵĶ˵�����
	Point points[] = 
	{
		 Point(75, 0), Point(100, 50), 
		 Point(150, 50), Point(112, 75),
		 Point(150, 150), Point(75, 100), 
		 Point(0, 150), Point(37, 75), 
		 Point(0, 50), Point(50, 50),
		 Point(75, 0)
	 };

	// ����·��
	GraphicsPath path;
	//��·���м���ֱ��
	path.AddLines(points, sizeof(points)/sizeof(Point));
	//���·��
	graphics.FillPath(&pthGrBrush, &path);
	//���Ʊ߽�
	graphics.DrawLines(&pen, points, sizeof(points)/sizeof(Point));
	//���ƶ���10���ߵĶ˵�
	for(int i=0;i<10;i++)
		//ÿ��Բ���ֱ��Ϊ10
		graphics.FillEllipse(&blackbrush, points[i].X-5,points[i].Y-5,10,10);
}
//ʹ��·�����仭ˢ��������
void Brush_PathGradientBrush_Star2_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�������ǵ�10���ߵĶ˵�����
	Point points[] =
	{
		 Point(75, 0), Point(100, 50), 
		 Point(150, 50), Point(112, 75),
		 Point(150, 150), Point(75, 100), 
		 Point(0, 150), Point(37, 75), 
		 Point(0, 50), Point(50, 50),
		 Point(75, 0)
	};
	// ����·��
	GraphicsPath path;
	//��·�������ֱ��
	path.AddLines(points, sizeof(points)/sizeof(Point));
	//����·�����仭ˢ
	PathGradientBrush pthGrBrush(&path);
	//�������ĵ�ɫ��(�յ�ɫ)
	pthGrBrush.SetCenterColor(Color::Red);

	//����ÿ���˵��ɫ��(�յ�ɫ)
	Color colors[] =
	{
		Color::Black, Color::Green,
		Color::Blue, Color::White, 
		Color::Black, Color::Green, 
		Color::Blue, Color::White,
		Color::Black, Color::Green
	};
	//����·�����仭ˢ�ı�Եɫ
	int clrCount=sizeof(colors)/sizeof(Color);
	pthGrBrush.SetSurroundColors(colors, &clrCount);
	// ���Ŀ��·��
	graphics.FillPath(&pthGrBrush, &path);

	//������ɫ���߽�ɫ�����ó����ɫ���鿴����Ч��
	for(int z=0;z<10;z++)
	{
		//��ˮƽ������ƽ�ƻ�ͼƽ��
		graphics.TranslateTransform(200.0f, 0.0f);
		//�������ĵ�ɫ��Ϊ���ɫ
		pthGrBrush.SetCenterColor(_MakeA_RGB(rand_Next(255)%155,rand_Next(255)%255,rand_Next(255)%255));
		//ʹ��ԭ�еı�Եɫ
		pthGrBrush.SetSurroundColors(colors, &clrCount);
		graphics.FillPath(&pthGrBrush, &path);
	}
}
//ʹ�ö��·�����仭ˢ
void Brush_Using_MorePathGradientBrush_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����һ�������Σ��߳�Ϊ50	
	float fHalf = 50 * (float)sin(120.0f/360.0f*PI); 
	PointF pts[] =
	{
		PointF( 50, 0),           
		PointF( 50 * 1.5f,  0),
		PointF( 50,         0),           
		PointF( 50 / 2,    -fHalf),
		PointF(-50 / 2,    -fHalf),
		PointF(-50,         0),
		PointF(-50 * 1.5f,  0), 
		PointF(-50,         0),
		PointF(-50 / 2,     fHalf),     
		PointF( 50 / 2,     fHalf)
	};

	//���������ν��仭ˢ
	PathGradientBrush pgbrush1(pts, 10);

	//��ˮƽ�ʹ�ֱ������ƽ�������εĶ���
	for (int i = 0; i <10; i++)
	{
		pts[i].X += 50*1.5f;
		pts[i].Y += fHalf;
	}

	//���ݸı������ĵ���������·�����仭ˢ
	PathGradientBrush pgbrush2(pts, 10);

	//����·�����仭ˢ�ķ�ת��ʽΪƽ��
	pgbrush1.SetWrapMode(WrapModeTile);
	pgbrush2.SetWrapMode(WrapModeTile);

	//�ֱ�����������ˢ�����ĵ�ɫ��Ϊ�졢��ɫ
	pgbrush1.SetCenterColor(Color::Red);
	pgbrush2.SetCenterColor(Color::Green);

	//��䵱ǰ����
	graphics.FillRectangle(&pgbrush1, 0, 0,MyClient.Width,MyClient.Height);
	//���ϴ�δ�������������ٴ���䵱ǰ���ڵĿհײ���
	graphics.FillRectangle(&pgbrush2, 0, 0,MyClient.Width,MyClient.Height);
}
//·�����仭ˢ����䷽ʽ
void Brush_PathGradientBrush_WrapMode_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 2);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 12);

	//�������ǵı������꣬Ϊ��ʾ��תЧ���������ǵ�һ������
	Point points[] =
	{
		Point(75, 0), Point(100, 50), 
		Point(150, 50), Point(112, 75),
		Point(150, 150), Point(75, 100), 
		Point(0, 190), Point(37, 75), 
		Point(10, 50), Point(50, 50)
	};

	GraphicsPath path;
	path.AddLines(points, sizeof(points)/sizeof(Point));

	// ����·�����仭ˢ
	PathGradientBrush pthGrBrush(&path);
	//�������ĵ�ɫ��(�յ�ɫ)
	pthGrBrush.SetCenterColor(Color::Red);

	//����ÿ���˵��ɫ��(�յ�ɫ)
	Color colors[]=
	{
		Color::Black,   Color::Green,
		Color::Blue, Color::White, 
		Color::Black,   Color::Green, 
		Color::Blue, Color::White,
		Color::Black,   Color::Green
	};

	int clrCount=sizeof(colors)/sizeof(Color);
	pthGrBrush.SetSurroundColors(colors, &clrCount);
	//��С��ˢ
	pthGrBrush.ScaleTransform(0.2f,0.2f);
	int i=0;

	//�Խ��仭ˢʹ��ƽ�����з�ʽ(Ĭ�Ϸ�ʽ)
	pthGrBrush.SetWrapMode(WrapModeTile);
	graphics.FillRectangle(&pthGrBrush, Rect(i*120,0,120,120));
	graphics.DrawRectangle(&pen, Rect(i*120,0,120,120));
	MyDrawString(graphics, "Tile",myFont,brush, PointF(20,125));

	i+=1;
	pthGrBrush.SetWrapMode(WrapModeTileFlipX);
	graphics.FillRectangle(&pthGrBrush, Rect(i*120,0,120,120));
	graphics.DrawRectangle(&pen, Rect(i*120,0,120,120));
	MyDrawString(graphics, "TileFlipX",myFont,brush, PointF(170,125));

	//�Խ��仭ˢʹ�ô�ֱ��ת���з�ʽ
	pthGrBrush.SetWrapMode(WrapModeTileFlipY);
	graphics.FillRectangle(&pthGrBrush, Rect(0,200,120,120));
	graphics.DrawRectangle(&pen, Rect(0,200,120,120));
	MyDrawString(graphics, "TileFlipY",myFont,brush, PointF(0,325));

	//�Խ��仭ˢʹ��ˮƽ����ֱͬʱ��ת���з�ʽ
	pthGrBrush.SetWrapMode(WrapModeTileFlipXY);
	graphics.FillRectangle(&pthGrBrush, Rect(120,200,120,120));
	graphics.DrawRectangle(&pen, Rect(120,200,120,120));
	MyDrawString(graphics, "TileFlipXY",myFont,brush, PointF(170,325));

	//���·����Լ�����Ρ����ĵ���Ϣ
	RectF rect;
	//��ȡ��ˢ��Լ�����ζ���
	pthGrBrush.GetRectangle(&rect);
	PointF CenterPoint;
	//��ȡ��ˢ�����ĵ���Ϣ
	pthGrBrush.GetCenterPoint(&CenterPoint);
	CString tmp;

	//��ʽ���ַ���
	tmp.Format("��ǰԼ�����ε���������Ϊ(%f,%f),���=%f �߶�=%f\n��ǰ����·�������ĵ�����Ϊ(%.2f,%.2f)",
		rect.X,rect.Y,rect.Height,rect.Width,
		CenterPoint.X,CenterPoint.Y);
	//������ĵ㼰Լ�����ζ������Ϣ
	MyDrawString(graphics, tmp,myFont,brush, PointF(0,395));
}
//����·�����仭ˢ�����ĵ�
void Brush_PathGradientBrush_CenterPoint_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����һ��Բ������
	GraphicsPath path;
	path.AddEllipse(0, 0, 200, 200);
	SolidBrush brush(_MakeA_RGB(155,Color::Red));
	//����һ��Բ��·�����仭ˢ
	PathGradientBrush pthGrBrush(&path);

	//�������ĵ�ɫ��
	pthGrBrush.SetCenterColor(_MakeA_RGB(155,Color::White));
	Color colors[] ={_MakeA_RGB(55, Color::Blue)};
	//���ñ�Եɫ
	int clrCount=1;
	pthGrBrush.SetSurroundColors(colors, &clrCount);
	//�������ʹ�õ�ɫ��ˢ
	graphics.FillEllipse(&pthGrBrush, 0, 0, 200, 200);
	//��ȡ���ĵ�ɫ��
	PointF center(0,0);
	pthGrBrush.GetCenterPoint(&center);

	//���Ļ�ˢ�����ĵ���Բ�ܵ��ϰ벿��ƽ��
	for(int i=0;i<200;i++)
	{
		center.X=(REAL)i;
		center.Y=10.f;
		pthGrBrush.SetCenterPoint(center);
		graphics.FillEllipse(&pthGrBrush, 0, 0, 200, 200);
		//��ǵ�ǰ���ĵ�
		graphics.FillEllipse(&brush, center.X, center.Y, 2.f, 2.f);
	}

	//���Ļ�ˢ�����ĵ���Բ�ܵ��°벿��ƽ��
	for(i=200;i>0;i--)
	{
		center.X=(REAL)i;
		center.Y=190;
		pthGrBrush.SetCenterPoint(center);
		graphics.FillEllipse(&pthGrBrush, 0, 0, 200, 200);
		//��ǵ�ǰ���ĵ�
		graphics.FillEllipse(&brush, center.X, center.Y, 2.f, 2.f);
	}

}
//��·�����仭ˢʹ�ö�ɫ����
void Brush_PathGradientBrush_InterpolationColors_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Red);
	//���������ε�������
	Point points[]=
	{
		Point(100, 0), 
		Point(200, 200),
		Point(0, 200)
	};
	//����һ�������ν��仭ˢ
	PathGradientBrush pthGrBrush(points, 3);
	//-������뽥���ɫ��
	Color  colors[]=
	{
		Color::Red,     //��
		Color::Green,     //��
		Color::Blue // ��
	}; 

	//���úϳɵ��λ��
	float pos[] =
	{
		0.0f,    // ��ɫ������߽�Ϊ��ɫ
		0.4f,    //�ھ�������40%��λ�ô�ʹ����ɫ
		1.0f	//���ĵ�ʹ����ɫ
	};   

	//���ý���Ĺ���ɫ
	pthGrBrush.SetInterpolationColors(colors, pos, 3);
	//�������
	graphics.FillRectangle(&pthGrBrush, 0, 0, 300, 300);  
	//������ĵ�
	PointF centerpoint(0,0);;
	pthGrBrush.GetCenterPoint(&centerpoint);
	graphics.FillEllipse(&brush, centerpoint.X-5.f, centerpoint.Y-5.f, 10.f, 10.f);
}
//����·�����仭ˢ�Ľ������ű���
void Brsuh_PathGradietBrush_Focus_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Black,3);
	SolidBrush brush(Color::Black);
	Font myFont(L"Arial", 12);

	//ָ����������������,���������ν��仭
	Point points[]=
	{
		Point(100, 0),
		Point(200, 200),
		Point(0, 200)
	};

	PathGradientBrush pthGrBrush(points, 3);
	//ָ������ɫ
	Color colors[] = {Color::Red, Color::Blue};
	//ָ��ɫ�ʺϳ�λ��
	float relativePositions[]=
	{
		0.0f,    // ��ɫ���߽�
		1.0f // ��ɫΪ����
	};

	//���ý���ɫ
	pthGrBrush.SetInterpolationColors(colors, relativePositions, 2);

	//ʹ��Ĭ���������ӽ������
	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200); 

	//��ȡĬ���������� 
	PointF FocusScales(0,0);
	pthGrBrush.GetFocusScales(&FocusScales.X, &FocusScales.Y);
	//���������Ϣ
	CString tmp;
	tmp.Format("ˮƽ:x=%.2f\n��ֱ:y=%.2f",FocusScales.X,FocusScales.Y);
	MyDrawString(graphics, tmp,myFont,brush, PointF(0,210));

	//ƽ�ƻ�ͼƽ��
	graphics.TranslateTransform(200,0);
	//������������
	FocusScales.X=0.6f;
	FocusScales.Y=0.6f;
	pthGrBrush.SetFocusScales(FocusScales.X,FocusScales.Y);

	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200);  
	MyDrawString(graphics, "ˮƽ:x=0.6\n��ֱ:y=0.6", myFont,brush, PointF(0,210));

	//ˮƽ���Ų����ڴ�ֱ����ʱ����
	graphics.TranslateTransform(200,0);
	//������������
	FocusScales.X=0.1f;
	FocusScales.Y=0.8f;
	pthGrBrush.SetFocusScales(FocusScales.X,FocusScales.Y);

	graphics.FillRectangle(&pthGrBrush,0, 0, 200, 200); 
	MyDrawString(graphics, "ˮƽ:x=0.1\n��ֱ:y=0.8", myFont,brush, PointF(0,210));

	//ˮƽ����=��ֱ����=1.0
	graphics.TranslateTransform(200,0);
	FocusScales.X=1.0f;
	FocusScales.Y=1.0f;
	pthGrBrush.SetFocusScales(FocusScales.X,FocusScales.Y);

	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200); 
	MyDrawString(graphics, "ˮƽ:x=1.0\n��ֱ:y=1.0", myFont,brush, PointF(0,210));

	//ˮƽ���Ų����ڴ�ֱ����ʱ�������Ŵ�ԭ������
	graphics.TranslateTransform(200,0);
	FocusScales.X=2.0f;
	FocusScales.Y=1.5f;
	pthGrBrush.SetFocusScales(FocusScales.X,FocusScales.Y);

	graphics.FillRectangle(&pthGrBrush, 0, 0, 200, 200);
	MyDrawString(graphics, "ˮƽ:x=2.0\n��ֱ:y=1.5", myFont,brush, PointF(0,210));
}
//·�����仭ˢ�ı任
void Brush_PathGradientBrush_Transform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	// ����һ��������·�����仭ˢ
	Point pts[]={Point(50, 0), Point(100, 100), Point(0, 100)};
	PathGradientBrush pthGrBrush(pts, 3);

	//�Ի�ˢʹ�ô�ֱ��ת��ʽ
	pthGrBrush.SetWrapMode(WrapModeTileFlipY);
	//��С��ˢ	
	pthGrBrush.ScaleTransform(0.5f, 0.5f);
	//��䵱ǰ����
	graphics.FillRectangle(&pthGrBrush, 0, 0, MyClient.Width,MyClient.Height);

	//����ˢ��ת90��
	pthGrBrush.RotateTransform(90.0f, MatrixOrderAppend);
	//�ٴ���䵱ǰ����
	graphics.FillRectangle(&pthGrBrush, 0, 0, MyClient.Width,MyClient.Height);
}

void Brsuh_LinearGradientBrush_UsingGamma_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	LinearGradientBrush linGrBrush(
		Point(0, 10),
		Point(200, 10),
		Color::Red,
		Color::Blue);

	graphics.FillRectangle(&linGrBrush, 0, 0, 200, 50);
	linGrBrush.SetGammaCorrection(true);
	graphics.FillRectangle(&linGrBrush, 0, 60, 200, 50);

}
//�򵥵�ʹ������ʾ��
void Font_UsingFontInGDIPlus_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//�½�һ������Ի���
	CFontDialog dlg;
	//������������ɫ������
	//dlg.ShowColor=true;
	//��������ѡ��Ի���
	if(dlg.DoModal()!=IDOK)
		return;
	//��ȡ������Ի����е�������Ϣ
	LOGFONT lf; dlg.GetCurrentFont(&lf);
	Font myFont(CWideCharString(dlg.GetFaceName()), lf.lfHeight);
	//��������ɫ�ʴ�����ˢ
	SolidBrush brush(dlg.GetColor());
	//�����ı������ʽ���ڵ�ǰ�����о�����ʾ
	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentCenter);
	fmt.SetLineAlignment(StringAlignmentCenter);
	//����ı�
	graphics.DrawString(L"����ı�", 4, &myFont, RectF(0,0,MyClient.Width,MyClient.Height),&fmt, &brush);
}

//ö�����е�����ϵ��
void Font_EnumAllFonts_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush   solidBrush(Color::Black);
	FontFamily   fontFamily(L"Arial");
	Font         font(&fontFamily, 8, FontStyleRegular, UnitPoint);
	//�����ı������ʽ
	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentNear);
	fmt.SetLineAlignment(StringAlignmentNear);

	CString tmp="";
	//��ȡ�����Ѿ���װ������ϵ��
	InstalledFontCollection installedFontCollection;
	int ffcount=installedFontCollection.GetFamilyCount();
	FontFamily *fontfamily = ::new FontFamily[ffcount];
	installedFontCollection.GetFamilies(ffcount, fontfamily, &ffcount);
	int index=0;
	//����fontfamily�����ÿһ����Ա
	for( int i=0; i<ffcount; i++)
	{
		//��ȡ��ǰ����ϵ������
		WCHAR name[LF_FACESIZE];
		fontfamily[i].GetFamilyName(name);
		CString t=name;
		CString s; s.Format(_T("%s%s"), (i? _T(", "):_T("")), t);
		tmp+=s;
		index++;
	}
	::delete []fontfamily;

	//�ڴ�����������е�����ϵ����
	RectF r(0,10,MyClient.Width,MyClient.Height);
	MyDrawString(graphics, tmp, font, solidBrush, r, fmt);
	//�������ϵ����Ϣ
	tmp.Format("�����ϵͳ���Ѿ���װ��������%d�֣������Ʒֱ�Ϊ:\n",index);
	MyDrawString(graphics, tmp,font,solidBrush, Point(0,0));
}

//������ǿ��ѡ��Ի����
void Font_EnhanceFontDialog_Click()
{
	MyDrawString(GetGraphics(), "����ǿ��ѡ��Ի����",
		Font(L"Arial",12), SolidBrush(Color::Red), Point(0,0));
/*
	Form3 f= Form3();
	f.ShowDialog();
*/
}


//ʹ�ò�ͬ�������Ե����ʽ
void Font_UsingTextRenderHint_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brs(Color::Black);
	FontFamily  fontFamily(L"Arial");
	Font        font(&fontFamily, 60, FontStyleRegular, UnitPixel);

	//ʹ�ò�ͬ�ı�Ե����ʽ��������ı�
	for (int i=TextRenderingHintSystemDefault; i<=TextRenderingHintClearTypeGridFit; i++)
	{
		//���ñ�Ե����ʽ
		graphics.SetTextRenderingHint((TextRenderingHint)i);
		//����ı�
		MyDrawString(graphics, "Render",font,brs, PointF(0, 0));
		//��ͼƽ�����Ƶ���
		graphics.TranslateTransform(0, font.GetHeight(&graphics));
	}
}
//ʹ��˽�����弯��
void Font_Privatefontcollection_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	PointF      pointF(0.0f, 10.0f);
	SolidBrush  solidBrush(Color::Red);
	//����˽�����弯
	PrivateFontCollection privateFontCollection;

	//��˽�����弯��׷���㷱�����ֿ��ļ�"������.TTF"
	WCHAR fontfile[]= L"c:\\������.TTF";
	if (Ok != privateFontCollection.AddFontFile(fontfile))
	{
		AfxMessageBox("�����ļ�����ʧ��\n��������");
		return;
	}

	//��˽�����弯���й��췱���壬��СΪ35����
	FontFamily pFontFamily(L"���㷱����", &privateFontCollection);
	Font tmpFont(&pFontFamily, 35);
	//�������������
	MyDrawString(graphics, "���۲���ǧ����", tmpFont,solidBrush, pointF);
	//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
	pointF.Y +=tmpFont.GetHeight(&graphics);
	MyDrawString(graphics, "����ǰͷ��ľ��", tmpFont,solidBrush, pointF);
}

//��˽�����弯����ʹ�ö�������
void Font_Privatefontcollection2_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	PointF      pointF(0.0f, 10.0f);
	SolidBrush  solidBrush(Color::Red);
	//����˽�����弯
	PrivateFontCollection privateFontCollection;
	//��˽�����弯��׷��������ͬ�������ļ�
	privateFontCollection.AddFontFile(L"C:\\WINDOWS\\Fonts\\STCAIYUN.TTF");
	privateFontCollection.AddFontFile(L"C:\\WINDOWS\\Fonts\\SIMLI.TTF");
	privateFontCollection.AddFontFile(L"C:\\WINDOWS\\Fonts\\Arial.ttf");

	FontFamily fontfamily[200];
	int ffcount=privateFontCollection.GetFamilyCount();
	if (ffcount>200) ffcount=200;
	privateFontCollection.GetFamilies(ffcount, fontfamily, &ffcount);
	int index=0;
	//����˽�����弯���е���������ϵ��
	for(int i=0; i<ffcount; i++)
	{
		Font tmpFont(&fontfamily[i], 35);
		//��ȡ��ǰ����ϵ������
		WCHAR name[LF_FACESIZE];
		fontfamily[i].GetFamilyName(name);
		CString s; s.Format(_T("������:  %s"), name);
		//�������������
		MyDrawString(graphics, s, tmpFont, solidBrush, pointF);
		graphics.TranslateTransform(0, tmpFont.GetHeight(&graphics));
	}
/*
	//ͨ������PrivateFontCollection���Families�����Ա������
	for(int index=0;index< privateFontCollection..Families.Length;index++)
	{
		Font tmpFont(privateFontCollection.Families[index].Name,35);
		//�������������
		MyDrawString(graphics, "������:  "+privateFontCollection.Families[index].Name,
			tmpFont,solidBrush, pointF);
		graphics.TranslateTransform(0,tmpFont.Height);
	}
*/
}
//����������Ƿ����
void Font_IsStyleAvailable_Click()
{

	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Gray);
	PointF      pointF(10.0f, 0.0f);
	SolidBrush  solidBrush(Color::Black);
	//��Ϣ�����ʹ�õ�����
	Font msgfont(L"Arial",12);

	//����˽�����弯
	PrivateFontCollection privateFontCollection;
	//��˽�����弯��׷�����������ļ�
	//����
	privateFontCollection.AddFontFile(L"C:\\windows\\Fonts\\simhei.ttf");
	//Courier New����
	privateFontCollection.AddFontFile(L"C:\\windows\\Fonts\\CourBI.ttf");
	//��������
	privateFontCollection.AddFontFile(L"C:\\windows\\Fonts\\STLITI.ttf");

	CString     familyName;
	CString     tmpmsg;

	//��ѯ˽�����弯������ϵ������
	int count=privateFontCollection.GetFamilyCount();
	//��ȡ����ϵ������
	FontFamily *pFontFamily = ::new FontFamily[count];			
	//������ϵ���е��������м���pFontFamily��
	privateFontCollection.GetFamilies(count, pFontFamily, &count);

	/*��˽�����弯��ÿһ������ϵ�н�������������
	�Ĳ�ѯ�������������ã�ʹ�ø÷������ı�����
	*/
	for(int j = 0; j< count; ++j)
	{
		//������ϵ���л�ȡ������
		WCHAR name[LF_FACESIZE];
		pFontFamily[j].GetFamilyName(name);
		familyName=name;
		// �������Ƿ����
		if(pFontFamily[j].IsStyleAvailable(FontStyleRegular))
		{
			tmpmsg="  ����ĳ��������";
			//��������
			FontFamily fm(CWideCharString(familyName), &privateFontCollection);
			Font tmpFont(&fm, 12, FontStyleRegular, UnitPixel);
			//���ʹ�ó����������
			MyDrawString(graphics, familyName+tmpmsg,tmpFont,solidBrush,pointF );
			//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
			pointF.Y += tmpFont.GetHeight(&graphics);
		}
		else
		{
			MyDrawString(graphics, familyName+tmpmsg+
				CString(L"  ����ĳ����񲻿���"),msgfont,solidBrush,pointF);
			pointF.Y += msgfont.GetHeight(&graphics);
		}
		tmpmsg.Empty();

		// �������Ƿ����
		if(pFontFamily[j].IsStyleAvailable(FontStyleBold))
		{
			tmpmsg="  ����Ĵ��������";
			//��������
			FontFamily fm(CWideCharString(familyName), &privateFontCollection);
			Font tmpFont(&fm, 12, FontStyleBold, UnitPixel);
			//���ʹ�ó����������
			MyDrawString(graphics, familyName+tmpmsg,tmpFont,solidBrush,pointF );
			//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
			pointF.Y += tmpFont.GetHeight(&graphics);
		}
		else
		{
			MyDrawString(graphics, familyName+tmpmsg+
				CString("  ����Ĵ����񲻿���"),msgfont,solidBrush,pointF);
			pointF.Y += msgfont.GetHeight(&graphics);
		}
		tmpmsg.Empty();

		// б�����Ƿ����
		if(pFontFamily[j].IsStyleAvailable(FontStyleItalic))
		{
			tmpmsg="  �����б�������";
			//��������
			FontFamily fm(CWideCharString(familyName),&privateFontCollection);
			Font tmpFont(&fm, 12, FontStyleItalic, UnitPixel);
			//���ʹ�ó����������
			MyDrawString(graphics, familyName+tmpmsg,tmpFont,solidBrush,pointF );
			//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
			pointF.Y += tmpFont.GetHeight(&graphics);
		}
		else
		{
			MyDrawString(graphics, familyName+tmpmsg+
				"  �����б���񲻿���",msgfont,solidBrush,pointF);
			pointF.Y += msgfont.GetHeight(&graphics);
		}
		tmpmsg.Empty();

		// ��ѯ�»��߷���Ƿ����
		if(pFontFamily[j].IsStyleAvailable(FontStyleUnderline))
		{
			tmpmsg="  ������»��߷�����";
			//��������
			FontFamily fm(CWideCharString(familyName),&privateFontCollection);
			Font tmpFont(&fm, 12, FontStyleUnderline, UnitPixel);
			//���ʹ�ó����������
			MyDrawString(graphics, familyName+tmpmsg,tmpFont,solidBrush,pointF );
			//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
			pointF.Y += tmpFont.GetHeight(&graphics);
		}
		else
		{
			MyDrawString(graphics, familyName+tmpmsg+
				"  ������»��߷�񲻿���",msgfont,solidBrush,pointF);
			pointF.Y += msgfont.GetHeight(&graphics);
		}
		tmpmsg.Empty();

		// ��ѯǿ���߷���Ƿ����
		if(pFontFamily[j].IsStyleAvailable(FontStyleStrikeout))
		{
			tmpmsg="  �����ǿ���߷�����";
			//��������
			FontFamily fm(CWideCharString(familyName),&privateFontCollection);
			Font tmpFont(&fm, 12, FontStyleStrikeout, UnitPixel);
			//���ʹ�ó����������
			MyDrawString(graphics, familyName+tmpmsg,tmpFont,solidBrush,pointF );
			//��ֱ����һ��һ�У��и�Ϊ  ����ĸ߶�
			pointF.Y += tmpFont.GetHeight(&graphics);
		}
		else
		{
			MyDrawString(graphics, familyName+tmpmsg+
				"  �����ǿ���߷�񲻿���",msgfont,solidBrush,pointF);
			pointF.Y += msgfont.GetHeight(&graphics);
		}
		tmpmsg.Empty();

		// �ڲ�ͬ������ϵ��֮����ϼ����
		graphics.DrawLine(&pen,0,(int )pointF.Y,400,(int)pointF.Y);
		pointF.Y += 10.0f;
	}
	::delete []pFontFamily;
}
//��ȡ����Ĵ�С
void Font_Size_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	PointF      pointF(0.0f, 0.0f);
	SolidBrush  solidBrush(Color::Black);

	CString infoString;
	int  ascent;
	float  ascentPixel;            
	int  descent;               
	float  descentPixel;          
	int  lineSpacing;           
	float  lineSpacingPixel;      

	FontFamily   fontFamily(L"Arial");
	//����һ����СΪ16���ص�Aria����
	Font  font(&fontFamily, 16, FontStyleRegular, UnitPixel);
	Font  font2(&fontFamily, 14, FontStyleRegular, UnitPixel);

	// ��ʾ�����С
	infoString.Format("font��Size����ֵΪ%.2f",font.GetSize());
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);
	// ����һ��
	pointF.Y += font2.GetHeight(&graphics);
	//��ʾ����߶ȣ�����
	infoString.Format("font��Height����ֵΪ%.2f", font.GetHeight(&graphics));
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);
	// ����һ��
	pointF.Y += font2.GetHeight(&graphics);

	// ��ʾ����ϵ�еĸ߶�(��Ƶ�λ)
	infoString.Format("ʹ��fontFamily.GetEmHeight�������ص�����߶�Ϊ %d ����Ƶ�λ��"
		,fontFamily.GetEmHeight(FontStyleRegular));
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);

	// ��������(Height���Ե�ֵ������ĸ߶ȣ���λΪ����)
	pointF.Y += 2.0f*font2.GetHeight(&graphics);

	// ��ȡ�����Ascent(�ϲ�����)
	ascent = fontFamily.GetCellAscent(FontStyleRegular);

	//���ϲ��������Ƶ�λת�������ص�λ
	ascentPixel= 
		font.GetSize() * ascent / fontFamily.GetEmHeight(FontStyleRegular);
	infoString.Format("�ϲ�����Ϊ %d����Ƶ�λ, %.2f�����ء�",
		ascent, ascentPixel);
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);

	// ����һ��
	pointF.Y += font2.GetHeight(&graphics);
	// ��ȡ�����Descent(�²�����),��Ƶ�λ
	descent = fontFamily.GetCellDescent(FontStyleRegular);

	//���²��������Ƶ�λת�������ص�λ
	descentPixel = 
		font.GetSize() * descent / fontFamily.GetEmHeight(FontStyleRegular);
	infoString.Format("�²�����Ϊ%d ����Ƶ�λ, %.2f�����ء�",
		descent, descentPixel);
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);

	// ����һ��
	pointF.Y += font2.GetHeight(&graphics);
	//��ȡ�о�(��Ƶ�λ)
	lineSpacing = fontFamily.GetLineSpacing(FontStyleRegular);
	//���о����Ƶ�λת�������ص�λ
	lineSpacingPixel = 
		font.GetSize() * lineSpacing / fontFamily.GetEmHeight(FontStyleRegular);
	infoString.Format("�о�Ϊ%d ����Ƶ�λ, %.2f ���ء�",
		lineSpacing, lineSpacingPixel);
	MyDrawString(graphics, infoString,font2,solidBrush,pointF);
}
//�����ı��������
void Font_BaseLine_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	FontFamily   fontFamily(L"Arial");
	//����һ����СΪ60���ص�Aria����
	Font  font(&fontFamily, 60, FontStyleRegular, UnitPixel);
	//��ȡ��ǰ���ڵľ��ο���
	int  cy=MyClient.Height;
	int cx=MyClient.Width;

	Pen pen(Color::Blue, 1);
	SolidBrush brush(Color::Blue);

	//�����ڴ�ֱ�����1/2������Ϊ����
	float yBaseline = cy / 2.f;
	//���ƻ���
	graphics.DrawLine(&pen, PointF(0, yBaseline), PointF((REAL)cx,yBaseline));
	//�õ�����߶�
	float cyLineSpace = font.GetHeight(&graphics);
	//��ȡ�о�
	int   iCellSpace  = fontFamily.GetLineSpacing(FontStyleRegular);
	//�õ��ϰ벿�־���
	int   iCellAscent = fontFamily.GetCellAscent(FontStyleRegular);
	//�����ı��������ʼλ������ڻ��ߵ�ƫ��
	float cyAscent    = cyLineSpace * iCellAscent / iCellSpace;

	//���������ϻ�������ֱ�ߣ����ΪcyAscent
	graphics.DrawLine(&pen, 
		PointF(0, yBaseline-cyAscent), PointF(cx,yBaseline-cyAscent));
	graphics.DrawLine(&pen, 
		PointF(0, yBaseline-2.0f*cyAscent), PointF(cx,yBaseline-2.0f*cyAscent));

	//�ֱ�����������������ı�
	MyDrawString(graphics, "AaFfgSs}", font,brush, PointF(0,yBaseline - cyAscent));
	MyDrawString(graphics, "AaFfgSs}",font,brush, PointF(0,yBaseline - 2.0f*cyAscent));

}

void Font_DrawString_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ı�
	CString msg="ʾ���ı�";

	Font myFont(L"����", 16);
	RectF layoutRect(50, 50, 200, 50);
	//���ö��뷽ʽ
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	SolidBrush blackBrush(Color::Black);

	// �����ı�
	MyDrawString(graphics, msg, myFont, blackBrush, layoutRect, format);
	// �����ı�����ľ�������
	Pen pen(Color::Black, 3);
	graphics.DrawRectangle(&pen, layoutRect);

}

void Font_MeasureString_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����һ�����������ı����ַ���
	CString txtOut="123456789\n";
	txtOut+="ABCDEFGHIJKLM\n";
	txtOut+="һ�����������߰˾�";

	FontFamily   fontFamily(L"Arial");
	//������������С��ͬ��Aria����
	Font  font(&fontFamily, 30, FontStyleRegular, UnitPixel);
	Font  font2(&fontFamily, 14, FontStyleRegular, UnitPixel);
	SolidBrush brush(Color::Black);

	StringFormat fmt;
	fmt.SetAlignment(StringAlignmentCenter);
	fmt.SetLineAlignment(StringAlignmentCenter);

	SizeF stringSize, strSize(1000,1000);			
	//��������ַ�������Ҫ�ľ��οռ�
	CWideCharString txtOutW(txtOut);
	graphics.MeasureString(txtOutW, txtOutW.GetLength(), &font, strSize, &fmt, &stringSize);

	CString tmp;
	tmp.Format("����ַ�������Ҫ�Ŀ��Ϊ:%2f  �߶�Ϊ%2f", stringSize.Width,stringSize.Height);

	// ��������ı������ƾ���
	Pen pen(Color::Red);
	graphics.DrawRectangle(&pen,
		10.0f,10.0f,stringSize.Width,stringSize.Height);
	//����ַ����Ĳ�����Ϣ
	MyDrawString(graphics, txtOut, font, brush,
		RectF(10.0f,10.0f,stringSize.Width,stringSize.Height),fmt);
	graphics.TranslateTransform(0,10+stringSize.Height);
	MyDrawString(graphics, tmp,font2,brush, PointF(0,0));
}
//������ָ������������ʾ���ַ�����������
void Font_MeasureString2_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	CString txtOut="123456789";
	txtOut+="ABCDEFGHIJKLM";
	txtOut+="һ�����������߰˾�";

	FontFamily   fontFamily(L"Arial");
	//������������С��ͬ��Aria����
	Font  font(&fontFamily, 30, FontStyleRegular, UnitPixel);
	Font  font2(&fontFamily, 14, FontStyleRegular, UnitPixel);
	//�����ı��������
	RectF layoutRect(10, 10,100,100);
	SolidBrush brush(Color::Black);

	//�����ı���ʾ��ʽ
	StringFormat fmt;		
	fmt.SetAlignment(StringAlignmentCenter);
	fmt.SetLineAlignment(StringAlignmentCenter);

	int codepointsFitted=0;
	int linesFilled=0;

	SizeF stringSize;
	//����ָ���������ܹ���ʾ���ַ�����������
	CWideCharString txtOutW(txtOut);
	graphics.MeasureString(txtOutW, txtOutW.GetLength(), 
		&font, SizeF(layoutRect.Width,layoutRect.Height),
		&fmt, &stringSize, &codepointsFitted, &linesFilled);

	CString tmp;
	tmp.Format("��������ִ���%d���ַ�\n����,��ָ�������������\nֻ�����%d�й�%d���ַ�",
		txtOutW.GetLength(), linesFilled, codepointsFitted);

	// ����ָ�����ı��������
	Pen pen(Color::Blue,2);
	graphics.DrawRectangle(&pen, layoutRect);
	//��ָ���������������ʾ�ı�
	MyDrawString(graphics, txtOut, font, brush, layoutRect, fmt);

	//����ַ����Ĳ�����Ϣ
	graphics.TranslateTransform(0,10+stringSize.Height);
	MyDrawString(graphics, tmp, font2, brush, PointF(0,0));
}
//�ı��ķ������
void Font_ColumnTextOut_Click()
{
	CString s_Filename;

	//�����ȡ <exePath> ../ReadMe.txt
	TCHAR ModuleDirectory[_MAX_PATH];
	::GetModuleFileName(NULL, ModuleDirectory, _MAX_PATH);
	TCHAR *p=::_tcsrchr(ModuleDirectory, '\\'); *p=0;
	p=::_tcsrchr(ModuleDirectory, '\\'); *p=0;
	::_tcscat(ModuleDirectory, "\\ReadMe.txt");

	s_Filename=ModuleDirectory;

	FILE *stream = ::fopen(s_Filename, "rt");
	if (!stream)
		return;

	CString str;

	//��ȡ���е��ļ�����	
	char buffer[1024]="";
	while (!feof(stream))
	{
		CString s;
		::fgets(buffer, 1024, stream);
		s=buffer; s.TrimLeft(); s.TrimRight(); s+="\r\n";
		str+=s;
	}
	//�ر��ļ�
	fclose(stream);

	//��������������֮��ļ��
	int COLUMWIDTH=256;
	int SPACE=10;

	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Black);
	Font myFont(L"����", 10);
	int codepointsFitted=0;
	int linesFilled=0;

	//���������ʽ
	StringFormat format;
	//�����Զ�����
	format.SetFormatFlags(StringFormatFlagsNoClip);
	//����ı��Ե��ʽ���
	format.SetTrimming(StringTrimmingWord);

	CWideCharString strW(str);
	//�������Ұ���(��)����ı�
	for (int x = 0; strW.GetLength()> 0&&x<MyClient.Width; x +=(COLUMWIDTH+SPACE))
	{
		//�����ı���Ӧ�ľ�������(һ��)
		RectF layoutRect(x, 0, COLUMWIDTH,MyClient.Height-myFont.GetHeight(&graphics));
		SizeF stringSize;
		//����ָ���������ܹ���ʾ���ַ�����������
		graphics.MeasureString(strW, strW.GetLength(),
			&myFont, SizeF(layoutRect.Width,layoutRect.Height),
			&format, &stringSize, &codepointsFitted, &linesFilled);

		//��ʾһ���ı�
		graphics.DrawString(strW, strW.GetLength(), &myFont, layoutRect, &format, &brush); 
		//ȥ���Ѿ�������ַ����Ա���һ���ܹ�������ʾ			  
		strW=strW.Mid(codepointsFitted);
	}
}
//�����ı���ȥβ��ʽ
void Font_StirngTrimming_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush  solidBrush(Color::Black); 
	FontFamily  fontFamily(L"Times New Roman");
	//�����ı����������
	Font        font(&fontFamily, 25, FontStyleRegular, UnitPixel);

	Pen pen(Color::Red);
	StringFormat stringFormat;
	//������ʾ��Ϣ�����弰��ʽ
	Font        font2(&fontFamily, 14, FontStyleRegular, UnitPixel);
	//�����ı�����ĸ�ʽ
	StringFormat msgFormat;
	msgFormat.SetAlignment(StringAlignmentCenter);
	msgFormat.SetLineAlignment(StringAlignmentCenter);

	//��ʾ��Ϣ�������
	RectF outrect(30, 100, 160, font2.GetHeight(&graphics)*2);

	//ȥβ��ʽ��Character
	stringFormat.SetTrimming(StringTrimmingCharacter);
	//����ı�
	CString text="One two three four five seven eight nine ten";
	MyDrawString(graphics, text, font, solidBrush, 
		RectF(30, 30, 160, 60), stringFormat);

	//�����ı��������
	graphics.DrawRectangle(&pen, 30, 30, 160, 60);
	//�����ʾ��Ϣ
	MyDrawString(graphics, "Character",font2,solidBrush,outrect, 
		msgFormat);

	//��ͼƽ����ˮƽ����ƽ��160������
	graphics.TranslateTransform(160,0);

	//����ȥβ��ʽ��Word
	stringFormat.SetTrimming(StringTrimmingWord);
	MyDrawString(graphics, text,font,solidBrush,Rect(30, 30, 160, 60), stringFormat);
	graphics.DrawRectangle(&pen, 30, 30, 160, 60);
	MyDrawString(graphics, "Word",font2,solidBrush,outrect, msgFormat);


	//����ȥβ��ʽ��EllipsisCharacter
	graphics.TranslateTransform(160,0);
	stringFormat.SetTrimming(StringTrimmingEllipsisCharacter);
	MyDrawString(graphics, text,font,solidBrush, Rect(30, 30, 160, 60), stringFormat);
	graphics.DrawRectangle(&pen, 30, 30, 160, 60);
	MyDrawString(graphics, "EllipsisCharacter",font2,solidBrush,outrect, msgFormat);


	//����ȥβ��ʽ��EllipsisWord
	graphics.TranslateTransform(160,0);
	stringFormat.SetTrimming(StringTrimmingEllipsisWord);
	MyDrawString(graphics, text,font,solidBrush, Rect(30, 30, 160, 60), stringFormat);
	graphics.DrawRectangle(&pen, 30, 30, 160, 60);
	MyDrawString(graphics, "EllipsisWord",font2,solidBrush,outrect, msgFormat);

	//����ȥβ��ʽ��EllipsisPath
	graphics.TranslateTransform(160,0);
	stringFormat.SetTrimming(StringTrimmingEllipsisPath);
	MyDrawString(graphics, text,font,solidBrush, Rect(30, 30, 160, 60), stringFormat);
	graphics.DrawRectangle(&pen, 30, 30, 160, 60);
	MyDrawString(graphics, "EllipsisPath",font2,solidBrush,outrect, msgFormat);

}
//�ı�����ļ��ô���
void Font_TextOutClip_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush  solidBrush(Color::Black); 
	FontFamily  fontFamily(L"����");
	Font        font(&fontFamily, 25, FontStyleRegular, UnitPixel);

	Pen pen(Color::Red);
	StringFormat stringFormat;
	RectF outtext(10, 10, 120, 45);
	//ʹ��Ĭ��ֵ����ı�
	CString text="�ı��ļ���ʾ��";
	MyDrawString(graphics, text,font,solidBrush,outtext, 
		stringFormat);
	//�����ı��������
	graphics.DrawRectangle(&pen, outtext.X,
		outtext.Y,outtext.Width,outtext.Height);

	//��ˮƽ����ƽ��170�����ظ�
	graphics.TranslateTransform(120,0);
	RectF out2=outtext;
	//���������ĸ߶ȵ���Ϊ����߶ȵ�������
	out2.Height=font.GetHeight(&graphics)*2;
	MyDrawString(graphics, text,font,solidBrush,out2, stringFormat);
	//�����ı��������
	graphics.DrawRectangle(&pen, out2.X,
		out2.Y,out2.Width,out2.Height);

	graphics.TranslateTransform(120,0);
	//������ı�ʱ��ʹ�ü���
	stringFormat.SetFormatFlags(StringFormatFlagsNoClip);
	MyDrawString(graphics, text,font,solidBrush,outtext, stringFormat);

	//�����ı��������
	graphics.DrawRectangle(&pen, outtext.X,outtext.Y, outtext.Width,outtext.Height);
}
//�����ı��ֲ��������
void Font_MeasureCharacterRanges_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	// ���û����ı����������Ļ�ˢ
	SolidBrush TextBrush(Color::Red);
	SolidBrush RegionBrush(_MakeA_RGB(100, Color::Black));
	Pen        blackPen(Color::Black);

	// ʹ��������Ȳ�ͬ�ľ�����������ı���ʾ�ⲻͬ�ֲ�����������
	RectF   layoutRect_A(20.0f, 20.0f, 120.0f, 180.0f);
	RectF   layoutRect_B(140.0f, 20.0f, 140.0f, 180.0f);
	RectF   layoutRect_C(280.0f, 20.0f, 180.0f, 180.0f);

	//�����Ҫ������ִ�
	CString ts="��ʱ���º�ʱ�أ�";
	ts+="���ﳤ����δ����";
	ts+="��ʹ���Ƿɽ��ڣ�";
	ts+="���̺������ɽ��";

	// ���ִ�����Ҫ�ֲ��������ı���������ÿ��ʫ�����������
	CharacterRange charRanges[] =
	{ 
		CharacterRange(4, 3),
		CharacterRange(12, 3),
		CharacterRange(20, 3), 
		CharacterRange(28, 3)
	};

	// �����ı�ʱʹ�õ����弰��С 
	FontFamily   fontFamily(L"������κ");
	Font  myFont(&fontFamily, 25,  FontStyleItalic, UnitPixel);

	StringFormat strFormat;
	//ָ����Ҫ�ֲ��������������
	Region CharRangeRegions[4];

	//�������ʽ��������Ҫ�ֲ�����������
	strFormat.SetMeasurableCharacterRanges(4, charRanges);

	//�ھ���layoutRect_A�ж��ı����оֲ������������Ľ��������CharRangeRegions��
	CWideCharString tsW(ts);
	graphics.MeasureCharacterRanges(tsW,tsW.GetLength(),&myFont,layoutRect_A, &strFormat,4,CharRangeRegions);
	//����ı�
	MyDrawString(graphics, ts, myFont,TextBrush,layoutRect_A, strFormat);
	//�����ı�����߿�
	graphics.DrawRectangle(&blackPen, layoutRect_A.X,layoutRect_A.Y,layoutRect_A.Width,layoutRect_A.Height);
	short   i;                 
	//�����CharRangeRegions���������
	for ( i = 0; i < 4; i++)
	{
		graphics.FillRegion(&RegionBrush, CharRangeRegions+i);
	}

	//�ھ���layoutRect_B�ж��ı����оֲ������������Ľ��������CharRangeRegions��
	graphics.MeasureCharacterRanges(tsW, tsW.GetLength(), &myFont, layoutRect_B, &strFormat,4,CharRangeRegions);
	//����ı�
	MyDrawString(graphics, ts, myFont,TextBrush,layoutRect_B, strFormat );
	graphics.DrawRectangle(&blackPen, 
		layoutRect_B.X,layoutRect_B.Y,layoutRect_B.Width,layoutRect_B.Height);
	//�������
	for ( i = 0; i <4; i++)
	{
		graphics.FillRegion(&RegionBrush, CharRangeRegions+i);
	}

	//�ھ���layoutRect_c�ж��ı����оֲ������������Ľ��������CharRangeRegions��
	graphics.MeasureCharacterRanges(tsW,tsW.GetLength(),&myFont,layoutRect_C, &strFormat,4,CharRangeRegions);
	//����ı�
	MyDrawString(graphics, ts, myFont,TextBrush,layoutRect_C, strFormat);
	graphics.DrawRectangle(&blackPen,
		layoutRect_C.X,layoutRect_C.Y,layoutRect_C.Width,layoutRect_C.Height);
	//�������
	for ( i = 0; i <4; i++)
	{
		graphics.FillRegion(&RegionBrush, CharRangeRegions+i);
	}

}
//�ؼ��ı��������
void Font_TextoutDirection_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�����Ҫ������ִ�
	CString ts="��ʱ���º�ʱ�أ�";
	ts+="���ﳤ����δ����";
	ts+="��ʹ���Ƿɽ��ڣ�";
	ts+="���̺������ɽ��";

	//�����������
	FontFamily   fontFamily(L"��Բ");
	Font  myFont(&fontFamily, 20,  FontStyleBold, UnitPixel);
	SolidBrush brush(Color::Red);
	Pen pen(Color::Black);

	//�����������
	Rect f(10,10,120,myFont.GetHeight(&graphics)*8);
	//����StringFormat����
	StringFormat strFormat;
	//����������ı�
	int flag=StringFormatFlagsDirectionRightToLeft;
	//�ı�����ֱ���������
	flag|=StringFormatFlagsDirectionVertical;
	//���������ʽ��־
	strFormat.SetFormatFlags(flag);

	//�����ı����뷽ʽ
	strFormat.SetAlignment(StringAlignmentCenter);
	strFormat.SetLineAlignment(StringAlignmentCenter);

	//����������估�ı�
	graphics.DrawRectangle(&pen,f);
	MyDrawString(graphics, ts,myFont,brush,f,strFormat);
}
//�����ı����뷽ʽ
void Font_TextAlignment_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ǰ���ڴ�С��Ϣ����
	Rect   rect(0, 0,
		MyClient.Width, MyClient.Height);
	SolidBrush brush(Color::Black);
	Pen pen(Color::Gray);

	//�Ե�ǰ�������ĵ�Ϊԭ�����������
	graphics.DrawLine(&pen,
		PointF(rect.Width/2,0), PointF(rect.Width/2,rect.Height));
	graphics.DrawLine(&pen,
		PointF(0,rect.Height/2), PointF(rect.Width,rect.Height/2));

	//��StringAlignmentö�ٵ����ֲ�ͬ�Ķ��뷽ʽ���ó������Ա���Ա�ֱ�ӷ���
	StringAlignment Align[3]=
	{
		StringAlignmentNear,
		StringAlignmentCenter,
		StringAlignmentFar
	};
	CString strAlign[] ={ "��", "��", "Զ" };

	//�����������
	FontFamily   fontFamily(L"��Բ");
	Font  font(&fontFamily, 12,  FontStyleRegular);
	StringFormat strfmt;

	//�ֱ��ڴ�ֱ��ˮƽ������ʹ�����ֲ�ͬ�Ķ��뷽ʽ
	for (int iVert = 0; iVert < 3; iVert++)
		for (int iHorz = 0; iHorz < 3; iHorz++)
		{
			//���ô�ֱ���뷽ʽ
			strfmt.SetLineAlignment((StringAlignment)Align[iVert]);
			//����ˮƽ���뷽ʽ
			strfmt.SetAlignment((StringAlignment)Align[iHorz]);
			//��������Ϣ���
			CString s;
			s.Format("ˮƽ����:%d\n��ֱ����:%d", strAlign[iVert],strAlign[iHorz]);

			//�ڵ�ǰ�����а������õĶ��뷽ʽ�����ı�
			MyDrawString(graphics, s,font,brush,rect, strfmt);
		}
}

void Font_TextAlignment2_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ǰ���ڴ�С��Ϣ����
	Rect   rect(0, 0, MyClient.Width, MyClient.Height);
	SolidBrush brush(Color::Black);
	Pen pen(Color::Gray);

	//�Ե�ǰ�������ĵ�Ϊԭ�����������
	graphics.DrawLine(&pen,
		PointF(rect.Width/2,0), PointF(rect.Width/2,rect.Height));
	graphics.DrawLine(&pen,
		PointF(0,rect.Height/2), PointF(rect.Width,rect.Height/2));

	//��StringAlignmentö�ٵ����ֲ�ͬ�Ķ��뷽ʽ���ó������Ա���Ա�ֱ�ӷ���
	StringAlignment Align[3]=
	{
		StringAlignmentNear,
		StringAlignmentCenter,
		StringAlignmentFar
	};
	CString strAlign[]={ "��", "��", "Զ" };

	//�����������
	FontFamily   fontFamily(L"��Բ");
	Font  font(&fontFamily, 12,  FontStyleRegular);
	StringFormat strfmt;

	//�ֱ��ڴ�ֱ��ˮƽ������ʹ�����ֲ�ͬ�Ķ��뷽ʽ
	for (int iVert = 0; iVert < 3; iVert+=2)
		for (int iHorz = 0; iHorz < 3; iHorz+=2)
		{
			//���ô�ֱ���뷽ʽ
			strfmt.SetLineAlignment((StringAlignment)Align[iVert]);
			//����ˮƽ���뷽ʽ
			strfmt.SetAlignment((StringAlignment)Align[iHorz]);
			//��������Ϣ���
			CString s;
			s.Format("ˮƽ����:%d\n��ֱ����:%d", strAlign[iVert],strAlign[iHorz]);

			//�ڵ�ǰ�����а������õĶ��뷽ʽ�����ı�
			MyDrawString(graphics, s,font,brush, PointF(MyClient.Width/2,MyClient.Height/2),strfmt);
		}
}
//ʹ���Ʊ�λ
void Font_TextoutUsingTabs_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	StringFormat stringFormat;
	//����ı�ʹ�õ�����
	FontFamily   fontFamily(L"Arial");
	Font         font(&fontFamily, 30, FontStyleBold, UnitPixel);
	SolidBrush solidBrush(Color::Black);

	//��ʹ���Ʊ�λ��Ϣ�����
	CString text = "A\tB\tC\t\t\tD";
	MyDrawString(graphics, text, font,  solidBrush, PointF(0,10), stringFormat);

	//�����Ʊ�λ��Ϣ1
	float  tabs[]={40.0f, 30.0f,40};
	stringFormat.SetTabStops(0.0f, sizeof(tabs)/sizeof(float), tabs);

	//ʹ���Ʊ�λ��Ϣ�Ľ����ı����
	graphics.TranslateTransform(0,30);
	text="A\tB\tC\tD";
	MyDrawString(graphics, text, font,  solidBrush, PointF(0,10), stringFormat);

	//�����Ʊ�λ��Ϣ2
	float tabs2[] = {60.0f, 60.0f, 60};
	stringFormat.SetTabStops(0.0f, 3, tabs2);
	graphics.TranslateTransform(0,30);
	MyDrawString(graphics, text, font, solidBrush, PointF(0,10), stringFormat);

	//��ȡ�Ʊ���Ϣ	
	float  firstTabOffset = 0;
	float tabStops[3];
	stringFormat.GetTabStops(3, &firstTabOffset, tabStops);

	//����Ʊ�λ
	for(int j = 0; j <3; ++j)
		tabStops[j]=0;
	stringFormat.SetTabStops(0.0f, 3, tabStops);

	//������Ʊ�λ��Ϣ������ı�
	graphics.TranslateTransform(0,30);
	MyDrawString(graphics, text, font,  solidBrush, PointF(0,10), stringFormat);
}

//������Ʒ��Ϣ�ṹ
struct SListItem
{
	public: CString name;//��Ʒ��
	public: float price;//����
	public: float  num;//����
	//���绯
	public: SListItem(CString p1, float p2,float p3) 
	{
		name = p1;
		price=p2;
		num = p3;    
	}
};
void Font_UsingTabs_Click()
{
	//��ʼ����Ʒ��Ϣ
	SListItem items[5]=
	{
		SListItem(L"MP3���Ż�",1228,10),
		SListItem(L"�ʼǱ�����",17200,1),
		SListItem(L"�����ӡ��",3200,5),
		SListItem(L"��ī��ӡ��",620,1),
		SListItem(L"�������",4800,5)
	};

	//�����ͷ
	CString title;
	title.Format("\n%s\t%s\t%s\t%s\n","��Ʒ��","����","����","�ܼ�");
	//��ʽ��ÿ����Ʒ��Ӧ���ַ���
	CString iteminfo[5];
	for (int i=0;i<5;i++)
	{
		//�����ܼ�
		float total=items[i].price*items[i].num;
		//���������ʽ
		CString s;
		s.Format("%d\t%.2f\t%.2f\t%.2f\n",
			items[i].name,items[i].price,items[i].num,total);
		iteminfo[i]=s;
	}

	//�ڱ��ÿһ�е����ݺϲ�
	CString xxx;;
	for (i=0;i<5;i++)
		xxx+=iteminfo[i];
	//��ͷ+����
	title+=xxx;

	//�ڵ�ǰ������������
	RectF  rect(0.0f,0.0f,
		MyClient.Width,MyClient.Height);

	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush   solidBrush(Color::Black);
	//�����������
	FontFamily   fontFamily(L"����");
	Font         font(&fontFamily,
		16, FontStyleRegular, UnitPixel);

	StringFormat stringFormat;
	//�����Ʊ�λ��Ϣ
	float   tabs[] = {120.0f, 120.0f,60.0f};
	stringFormat.SetTabStops(0.0f, sizeof(tabs)/sizeof(float), tabs);
	//������
	MyDrawString(graphics, title,font, solidBrush,rect, stringFormat);
}

void Font_TextoutHotkeyPrefix_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush  solidBrush(Color::Black); 
	FontFamily  fontFamily(L"����");
	Font   font(&fontFamily, 20, FontStyleRegular, UnitPixel);
	Pen pen(Color::Red);

	StringFormat stringFormat;
	//��ʾ��ݼ��ַ���������"&"��
	stringFormat.SetHotkeyPrefix(HotkeyPrefixNone);
	MyDrawString(graphics, "������(&T )\n״̬��(&S )", font, solidBrush,
		RectF(30, 30, 160, font.GetHeight(&graphics)*2),stringFormat);

	//���Ʊ߿�
	graphics.DrawRectangle(&pen, Rect(30, 30, 160,font.GetHeight(&graphics)*2));

	//����""��Ϊ�»���
	stringFormat.SetHotkeyPrefix(HotkeyPrefixShow);
	graphics.TranslateTransform(0,font.GetHeight(&graphics)*3);
	MyDrawString(graphics, "������(&T )\n״̬��(&S )", font, solidBrush,
		RectF(30, 30, 160, font.GetHeight(&graphics)*2),stringFormat);

	//���Ʊ߿�
	graphics.DrawRectangle(&pen, Rect(30, 30, 160,font.GetHeight(&graphics)*2));

	//����""��
	graphics.TranslateTransform(0,font.GetHeight(&graphics)*3);
	stringFormat.SetHotkeyPrefix(HotkeyPrefixHide);
	MyDrawString(graphics, "������(&T )\n״̬��(&S )", font, solidBrush,
		RectF(30, 30, 160, font.GetHeight(&graphics)*2),stringFormat);

	graphics.DrawRectangle(&pen, Rect(30, 30, 160,font.GetHeight(&graphics)*2));

}

void Font_TextoutShadow_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//���ı�ʹ��ȥ��ݵı�Ե����
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	FontFamily  fontFamily(L"���Ŀ���");
	Font        font(&fontFamily, 100, FontStyleBold, UnitPixel);

	//�ı������
	RectF textout(font.GetHeight(&graphics),
		MyClient.Height/2,MyClient.Width,MyClient.Height);

	//��������ͬ��λ�û����ı����γ���Ӱ
	//solidBrush��ɫ��͸����Ϊ100������
	SolidBrush solidBrush(_MakeA_RGB(100,Color::Black));
	SolidBrush redBrush(Color::Red);
	MyDrawString(graphics, "��Ӱ��",font, solidBrush,
		PointF(27.0f, 27.0f));
	MyDrawString(graphics, "��Ӱ��",font, redBrush,
		PointF(12.0f, 20.0f));

	//��һ����Ӱ�֣���ӰΪ����
	//����Ӱ�߻�ˢ
	HatchBrush brush_tmp(
		HatchStyleDarkDownwardDiagonal,Color::Black, Color::White);

	int reptime=40;
	//�Ȼ�����
	for(int i=0;i<reptime;i++)
		MyDrawString(graphics, "��Ӱ��",font,brush_tmp,
			PointF(textout.X+i+2,textout.Y+i+2));

	//�ٻ�ǰ��
	MyDrawString(graphics, "��Ӱ��",font, redBrush, PointF(textout.X,textout.Y));
}

void Font_TextoutHashline_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//���ı�ʹ��ȥ��ݵı�Ե����
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	FontFamily  fontFamily(L"���Ŀ���");
	Font        font(&fontFamily, 100, FontStyleBold, UnitPixel);

	//�ı������
	RectF textout(font.GetHeight(&graphics),0,MyClient.Width,MyClient.Height);
	//��ˢ������ʾ��
	RectF brushdemo(0,0,font.GetHeight(&graphics),font.GetHeight(&graphics));
	//����һ��Ӱ�߻�ˢ
	HatchBrush brush_tmp(HatchStyle75Percent,Color::Black, Color::White);

	//�����ı������ʽ��ˮƽ���󡢴�ֱ����
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentCenter);

	//��ʾ��ˢ����
	graphics.FillRectangle(&brush_tmp,brushdemo);
	//ʹ�û�ˢ�����ı�
	MyDrawString(graphics, "Ӱ����",font,brush_tmp,textout,format);

}

void Font_TextoutTexture_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//���ı�ʹ��ȥ��ݵı�Ե����
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	FontFamily  fontFamily(L"���Ŀ���");
	Font        font(&fontFamily, 70, FontStyleBold, UnitPixel);

	//�ı������
	RectF textout(0,0,MyClient.Width,MyClient.Height);
	//��ˢ������ʾ��
	RectF brushdemo(0,0,font.GetHeight(&graphics),font.GetHeight(&graphics));

	//װ������ͼƬ
	Bitmap image(L"TEXTURE3.bmp");
	//��������ˢ
	TextureBrush brush_tmp(&image);

	//�����ı������ʽ��ˮƽ����ֱ����
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);

	//��ʾ��ˢ����
	graphics.FillRectangle(&brush_tmp,brushdemo);
	//ʹ�û�ˢ�����ı�
	MyDrawString(graphics, "������",font,brush_tmp,textout,format);
}

void Font_TextoutGradient_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//���ı�ʹ��ȥ��ݵı�Ե����
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	FontFamily  fontFamily(L"���Ŀ���");
	Font        font(&fontFamily, 70, FontStyleBold, UnitPixel);

	RectF textout(0,0,MyClient.Width,MyClient.Height);
	//��ˢ������ʾ��
	RectF brushdemo(0,0,font.GetHeight(&graphics),font.GetHeight(&graphics));
	//����һ����ɫ���仭ˢ
	Color colors[] =
	{
		Color::Red,   // ��ɫ
		Color::Green,//����ɫΪ��ɫ
		Color::Blue  // ��ɫ
	};
	float positions[] = 
	{
		0.0f,   // �ɺ�ɫ��
		0.3f,   // ��ɫʼ�ڻ�ˢ���ȵ�����֮һ
		1.0f // ����ɫֹ
	}; 

	//����һ���Ӻ�ɫ����ɫ�Ľ��仭ˢ
	LinearGradientBrush brush_tmp(
		Point(0, 0), 
		Point(100, font.GetHeight(&graphics)), 
		Color::White,         // ��
		Color::White);  // ��

	//���ý��仭ˢ�Ķ�ɫ������Ϣ
	//ColorBlend clrBlend(3);
	//clrBlend.Colors=colors;
	//clrBlend.Positions=positions;
	brush_tmp.SetInterpolationColors(colors, positions, 3);

	//�����ı������ʽ��ˮƽ���󡢴�ֱ����
	StringFormat format;
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentCenter);
	//��ʾ��ˢ����
	graphics.FillRectangle(&brush_tmp,brushdemo);
	//ʹ�û�ˢ�����ı�
	MyDrawString(graphics, "������",font,brush_tmp,textout,format);
}
//����·��
void Path_Construct_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//���幹��·���ĵ�����
	PointF data[]=
{
	PointF(40,140),
	PointF(275,200),
	PointF(105,225),
	PointF(190,300),
	PointF(50,350),
	PointF(20,180)
};

	//���ö��������ͽ�ÿ�㶼�����ֱ�ߵĶ˵�
	BYTE typeline[]=
{
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine
};

	//����·��
	GraphicsPath tmp1(data,typeline,6);
	//���·��
	graphics.FillPath(&SolidBrush(Color::Red),&tmp1);

	//���ƶ���·���Ķ˵�
	for(int i=0;i<6;i++)
		graphics.FillEllipse(&SolidBrush(Color::Black),
			RectF(data[i].X-5,data[i].Y-5,10,10));

	//��ͼƽ������
	graphics.TranslateTransform(360,0);

	//����·���Ķ˵�����
	BYTE type[]=
{
	(BYTE)PathPointTypeStart,
	(BYTE)PathPointTypeBezier,
	(BYTE)PathPointTypeBezier,
	(BYTE)PathPointTypeBezier,
	(BYTE)PathPointTypeLine,
	(BYTE)PathPointTypeLine
};
	//���첢���·��
	GraphicsPath tmp(data,type,6);
	graphics.FillPath(&SolidBrush(Color::Red),&tmp);

	//���ƶ���·���Ķ˵�
	for(i=0;i<6;i++)
		graphics.FillEllipse(&SolidBrush(Color::Black),
			RectF(data[i].X-5,data[i].Y-5,10,10));
}

void Path_AddLines_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue,2);
	//����·������
	GraphicsPath path;

	Rect rect1(20, 20, 100, 200);
	Rect rect2(40, 40, 100, 200);
	//������λ���
	path.AddArc(rect1, 0.0f, 180.0f); 
	path.AddArc(rect2, 0.0f, 180.0f); 
	graphics.DrawPath(&pen, &path);
}
//���ͼ��
void Path_CloseFigure_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue,2);
	//����·������
	GraphicsPath path;

	Rect rect1(20, 20, 100, 200);
	Rect rect2(40, 40, 100, 200);
	GraphicsPath path2;
	path2.AddArc(rect1, 0.0f, 180.0f);  
	//��ջ���1
	path2.CloseFigure();
	path2.AddArc(rect2, 0.0f, 180.0f);  
	//��ջ���2
	path2.CloseFigure();
	graphics.DrawPath(&pen, &path2);
}
//·�������
void Path_FillPath_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	GraphicsPath path1;
	GraphicsPath path;
	Pen pen(_MakeA_RGB(128, Color::Blue), 5);
	SolidBrush brush(Color::Red);

	//�������ֱ�ߣ����ŵ�ͼ��
	path1.AddLine(10,10,10,50);
	path1.AddLine(10,50,50,50);
	path1.AddLine(50,50,50,10);
	path1.StartFigure();

	//���һ���պϵ�ͼ��
	RectF rect(110,10,40,40);
	//��ʼ�ڶ�����·����ͼ��׷��
	path1.AddRectangle(rect);
	//���ơ����·��
	graphics.DrawPath(&pen, &path1);
	graphics.FillPath(&brush, &path1);

	//��ӿ��ŵĻ���
	path.AddArc(0, 0, 150, 120, 30, 120);
	//��ӷ�յ���Բ
	path.AddEllipse(50, 50, 50, 100);

	//ʹ��Ĭ�ϵ���䷽ʽ���·��
	graphics.FillPath(&brush, &path);
	graphics.DrawPath(&pen, &path);
}

void Path_AddSubPath_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue,2);
	Rect rect(0, 0, 100, 50);
	GraphicsPath path;

	//��·���а���ֱ���������λ���
	path.AddArc(0, 0, 100, 50, 0.0f, 180.0f);
	path.AddArc(0, 30, 100, 50, 0.0f, 180.0f);
	path.AddArc(0, 60, 100, 50, 0.0f, 180.0f);
	path.AddArc(0, 90, 100, 50, 0.0f, 180.0f);
	path.AddArc(0, 120, 100, 50, 0.0f, 180.0f);
	graphics.DrawPath(&pen, &path);

	//��ȡ·����ռ����
	RectF rect2; path.GetBounds(&rect2);

	//��ͼƽ������
	graphics.TranslateTransform(rect2.Width+10,0);

	GraphicsPath path2;
	//�����һ����·��
	path2.AddArc(0, 0, 100, 50, 0.0f, 180.0f);
	path2.AddArc(0, 30, 100, 50, 0.0f, 180.0f);
	path2.AddArc(0, 60, 100, 50, 0.0f, 180.0f);

	//�ڲ���յ�ǰ��·��������¿�ʼ�ڶ�����·���Ļ���
	path2.StartFigure();
	//��ӻ���
	path2.AddArc(0, 90, 100, 50, 0.0f, 180.0f);

	//�ڷ�յ�ǰ��·��������¿�ʼ��������·���Ļ���
	path2.CloseFigure();
	path2.AddArc(0, 120, 100, 50, 0.0f, 180.0f);

	//������·��
	graphics.DrawPath(&pen, &path2);
}

void Path_GetSubPath_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen bluePen(Color::Blue,3);
	GraphicsPath path;
	// ��·��1
	path.AddRectangle(Rect(20, 20, 60, 30));   
	// ��·��2
	path.AddLine(100, 20, 160, 50);            
	path.AddArc(180, 20, 60, 30, 0.0f, 180.0f);
	// ��·��3
	path.AddRectangle(Rect(260, 20, 60, 30)); 
	// ��·��4
	path.AddLine(340, 20, 400, 50);           
	path.AddArc(340, 20, 60, 30, 0.0f, 180.0f);
	path.CloseFigure();
	// ��·��5
	path.AddRectangle(Rect(420, 20, 60, 30));  
	//����·��
	graphics.DrawPath(&bluePen, &path);

	// ����·����������iterator
	GraphicsPathIterator iterator(&path);
	GraphicsPath subpath;
	int isClosed=false;
	int count=0;
	//������������NextSubpath,��ȡ��·��
	//��·���ĵ�ǰλ���ƶ���1
	count =iterator.NextSubpath(&subpath, &isClosed);
	//��·���ĵ�ǰλ���ƶ���2
	count = iterator.NextSubpath(&subpath, &isClosed);

	//�ڵڶ��л�����ȡ����·��
	graphics.TranslateTransform(0,50);   
	graphics.DrawPath(&bluePen, &subpath);

	//��λ���е�λ���ƶ���Ϣ
	iterator.Rewind();
	count = iterator.NextSubpath(&subpath, &isClosed);
	//�ڵ����л����³�ȡ����·��
	graphics.TranslateTransform(0,50);   
	Pen redPen(Color::Red,3);
	graphics.DrawPath(&redPen, &subpath);

	//������������NextSubpath���Ի�ȡ��·���Ķ������Ϣ
	int start=0;
	int end=0;
	CString msg;
	//��λ���е�λ���ƶ���Ϣ
	iterator.Rewind();
	count = iterator.NextSubpath(&start, &end, &isClosed);
	//����λ��������Ϣ
	msg.Format(_T("��һ���ƶ���·���Ķ������ֹλ��Ϊ%d\t��\t%d\n"),start,end);
	count = iterator.NextSubpath(&start, &end, &isClosed);
	CString s;
	s.Format(_T("�ڶ����ƶ���·���Ķ������ֹλ��Ϊ%d\t��\t%d\n"),start,end);
	msg+=s;
	//������·���Ķ����λ��������Ϣ
	FontFamily  fontFamily(L"����");
	Font font(&fontFamily,12);
	graphics.TranslateTransform(0,60);
	MyDrawString(graphics, msg,font,SolidBrush(Color::Black), PointF(0,0));
}

void Path_GetPoints_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����·������
	GraphicsPath path;
	//���ֱ��
	path.AddLine(20, 100, 150, 120);
	//��Ӿ���
	path.AddRectangle(Rect(40, 30, 20, 60));
	//�����Բ
	path.AddEllipse(Rect(70, 30, 100, 40));
	//������ߡ�
	Point points[] =
	{
		Point(300, 40),
		Point(350, 60),
		Point(300, 80),
		Point(300, 100),
		Point(350, 150)
	};
	path.AddCurve(points,5);

	//����·��
	Pen pen(Color::Blue);
	graphics.DrawPath(&pen, &path);

	// ��ȡ����·���ĵ�����
	int count =path.GetPointCount();
	//���Ƶ㶨��·���ĵ�
	SolidBrush brush(Color::Red);
	PointF *points0 = new PointF[count];
	path.GetPathPoints(points, count);
	for(int j = 0; j < count; ++j)
	{
		graphics.FillEllipse(
			&brush, 
			points0[j].X - 3.0f, 
			points0[j].Y - 3.0f,
			6.0f,
			6.0f);
	}
	delete points0;
	/*����һһ�ֱ�������ķ�ʽ
	foreach( PointF x in path.PathPoints)
		graphics.FillEllipse(
			brush, 
			x.X - 3.0f, 
			x.Y - 3.0f,
			6.0f,
			6.0f);
	*/
}

void Path_PathData_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//���ߵĶ����
	Point points[] =
{
	Point(40, 60), 
	Point(50, 70), 
	Point(30, 90)
};

	Pen pen(Color::Red, 2);
	GraphicsPath path;
	//����
	path.AddArc(175, 50, 50, 50, 0.0f, -180.0f);
	//ֱ��
	path.AddLine(100, 0, 250, 20);
	path.StartFigure();
	//ֱ��
	path.AddLine(50, 20, 5, 90);
	//����
	path.AddCurve(points, 3);
	path.AddLine(50, 150, 150, 180);
	path.CloseAllFigures();
	//����·��
	graphics.DrawPath(&pen, &path);
	//��ȡPathData����ֵ
	PathData pathData; 
	path.GetPathData(&pathData);
	SolidBrush brush(Color::Red);

	//���ƶ����
	for (int i=0; i<pathData.Count; i++)
		graphics.FillEllipse(&SolidBrush(Color::Black),
			pathData.Points[i].X - 5.0f,pathData.Points[i].Y - 5.0f,10.0f,10.0f);
	//���ÿһ��·������������
	FontFamily  fontFamily(L"����");
	Font font(&fontFamily,12);
	RectF rect;
	path.GetBounds(&rect);
	graphics.TranslateTransform(rect.Width+10,0);
	for (i=0; i<pathData.Count; i++)
	{
		CString msg;
		msg.Format("��%d�������Ϊ:\t%d", i+1, pathData.Types[i]);
		MyDrawString(graphics, msg,
			font,SolidBrush(Color::Black), PointF(0,(i+1)*font.GetHeight(&graphics)));
	}
}

void Path_ViewPointFLAG_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.8f,0.8f);


	SolidBrush brush(Color::Red);
	//����һ�������ĸ���·����·��
	GraphicsPath path;
	path.AddRectangle(Rect(20, 20, 60, 30));
	path.AddLine(100, 20, 160, 50);
	path.AddArc(180, 20, 60, 30, 0, 180);
	path.AddRectangle(Rect(260, 20, 60, 30));
	path.AddLine(340, 20, 400, 50);
	path.AddArc(340, 20, 60, 30, 0, 180);
	path.CloseAllFigures();
	//���·��
	graphics.FillPath(&brush, &path);

	//��·���ı����Ϣ����GraphicsPathIterator����
	GraphicsPathIterator iterator(&path);

	//��ȡ��ǵ���Ϣ
	int start=0;
	int end=0;
	int count=0;
	//��ȡ��һ���������
	count = iterator.NextMarker(&start, &end);
	//Ϊ�����ꡢ���ͷ���ռ�
	PointF *points = new PointF[count];
	BYTE *types = new BYTE[count];
	//��iterator������Ϣ
	iterator.CopyData(points, types, start, end);
	//���ݸ��Ƶ���Ϣ�´���һ��·��
	GraphicsPath pathnew(points, types, count);

	//����λ�û���·���Ķ����
	graphics.TranslateTransform(0,60);
	for(int j = 0; j < count; ++j)
		graphics.FillEllipse(&SolidBrush(Color::Black),points[j].X - 2.0f,
			points[j].Y - 2.0f,	4.0f,4.0f);

	//����´�����·��
	graphics.TranslateTransform(0,60);
	graphics.FillPath(&brush, &pathnew);
	graphics.TranslateTransform(0,60);

	//������еı�ǵ���Ϣ
	CString msg;
	for(j = 0; j < count; ++j)
	{
		CString s;
		s.Format("��%s����Ϣ:X=%.2f\tY=%.2f\t����=%d\n",
			j,points[j].X,points[j].Y,types[j]);
		msg+=s;
	}

	//�����ַ���
	FontFamily  fontFamily(L"����");
	Font   font(&fontFamily, 12, FontStyleRegular, UnitPixel);
	MyDrawString(graphics, msg, font,SolidBrush(Color::Black), PointF(0,0));

	delete types;
	delete points;
}

void Path_SubPathRange_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Red);
	//����һ�����������·����·��
	GraphicsPath path;
	// *************path.SetMarkers();**************
	//��ӵ�һ����·��
	path.AddRectangle(Rect(20, 20, 60, 30));

	//��ӵڶ�����·��
	path.AddLine(100, 20, 160, 50);
	//�ڶ�����ǽ��ڶ�����·��������ض�
	path.SetMarker(); 
	path.AddArc(180, 20, 60, 30, 0, 180);

	//��ӵ�������·��
	path.AddRectangle(Rect(260, 20, 60, 30));
	//���������
	path.SetMarker(); 

	//��ӵ��ĸ���·��
	path.AddLine(340, 20, 400, 50);
	path.AddArc(340, 20, 60, 30, 0, 180);

	//���·��
	graphics.FillPath(&brush,&path);

	//��·���ı����Ϣ����GraphicsPathIterator����
	GraphicsPathIterator iterator(&path);
	int d=iterator.GetSubpathCount();
	//��ȡ��ǵ���Ϣ
	int start;
	int end;
	int count;
	//�Ƶ��ڶ������
	count = iterator.NextMarker(&start, &end);
	//�Ƶ����������
	count = iterator.NextMarker(&start, &end);
	//Ϊ�����ꡢ���ͷ���ռ�
	PointF *points = new PointF[count];
	BYTE *types = new BYTE[count];

	//��iterator������Ϣ
	iterator.CopyData(points, types, start, end);
	//���ݸ��Ƶ���Ϣ�´���һ��·��
	GraphicsPath pathnew(points, types, count);

	//����λ�û��Ʊ�ǵ�
	graphics.TranslateTransform(0,60);
	for(int j = 0; j < count; ++j)
		graphics.FillEllipse(&SolidBrush(Color::Black),
			points[j].X - 2.0f,points[j].Y - 2.0f,
			4.0f,
			4.0f);

	//����´�����·��
	graphics.TranslateTransform(0,60);
	graphics.FillPath(&brush,&pathnew);

	//������еı�ǵ���Ϣ
	CString msg;
	for( j = 0; j < count; ++j)
	{
		CString s;
		s.Format(_T("��%d�����Ϣ:X=%.2f\tY=%.2f \t���ͣ�%d\n"),
			j,points[j].X,points[j].Y,types[j]);
		msg+=s;
	}

	FontFamily  fontFamily(L"����");
	Font        font(&fontFamily, 12, FontStyleRegular, UnitPixel);
	//�����ַ���
	graphics.TranslateTransform(0,60);
	MyDrawString(graphics, msg, font,SolidBrush(Color::Black), PointF(0,0));

	delete points;
	delete types;
}


void Path_Flatten_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//���߶����
	Point pts[] =
	{
		Point(20,50), 
		Point(60,70), 
		Point(80,10), 
		Point(120,50)
	};

	GraphicsPath path;
	path.AddCurve(pts, 4);
	path.AddEllipse(160, 10, 150, 80);
	path.AddBezier(20, 100, 20, 150, 50, 80, 100, 60);

	//����Ĭ�ϵķ�ʽ����·��
	Pen pen(Color::Black,3);
	graphics.DrawPath(&pen, &path);
	//��ȡ·������Ϣ
	PathData pathData;
	path.GetPathData(&pathData);

	// ����·�������
	SolidBrush brush(Color::Red);
	for(int j = 0; j <pathData.Count; ++j)
	{
		graphics.FillEllipse(&brush, pathData.Points[j].X - 3.0f,
			pathData.Points[j].Y - 3.0f,6.0f, 6.0f);
	}

	//��ͼƽ������100����λ 
	graphics.TranslateTransform(0,120);
	//��������ת  
	path.Flatten(&Matrix(), 14.0f);
	pen.SetColor(Color::Green);
	//����ת�����·��  
	graphics.DrawPath(&pen, &path);
}


void Path_Warp_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	// ����һ��ȫ����������ɵ�·��
	PointF points[] =
	{
		PointF(20.0f, 60.0f),
		PointF(30.0f, 90.0f),
		PointF(15.0f, 110.0f),
		PointF(15.0f, 145.0f),
		PointF(55.0f, 145.0f),
		PointF(55.0f, 110.0f),
		PointF(40.0f, 90.0f),
		PointF(50.0f, 60.0f)
	};

	GraphicsPath path;
	path.AddLines(points, sizeof(points)/sizeof(PointF));
	path.CloseFigure();

	// ����Ť��ǰ��·��
	Pen bluePen(Color::Blue,3);
	graphics.DrawPath(&bluePen, &path);

	// �������·����Դ����
	RectF srcRect(10.0f, 50.0f, 50.0f, 100.0f);
	//�������ӳ���Ŀ���
	PointF destPts[] =
	{
		PointF(220.0f, 10.0f),
		PointF(280.0f, 10.0f),
		PointF(100.0f, 150.0f),
		PointF(300.0f, 150.0f)
	};

	//Ť������
	path.Warp(destPts, 4, srcRect);
	// ����Ť�����·��
	graphics.DrawPath(&bluePen, &path);

	// ����Դ���κ�Ŀ��Ķ����
	Pen blackPen(Color::Black,1);
	graphics.DrawRectangle(&blackPen, 
		srcRect.X,srcRect.Y,srcRect.Width,srcRect.Height);
	graphics.DrawLine(&blackPen, destPts[0], destPts[1]);
	graphics.DrawLine(&blackPen, destPts[0], destPts[2]);
	graphics.DrawLine(&blackPen, destPts[1], destPts[3]);
	graphics.DrawLine(&blackPen, destPts[2], destPts[3]);
}

void Path_Transform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	GraphicsPath path;
	//���һ��������·��   
	path.AddRectangle(Rect(40, 10, 200, 50));
	//��������任ǰ��·��
	graphics.DrawPath(&Pen(Color::Blue,4), &path);

	//��ת·��
	Matrix matrix;
	matrix.Rotate(15.0f);
	path.Transform(&matrix);
	//���ƽ�������任���·��
	graphics.DrawPath(&Pen(Color::Red,4), &path);
}

void Path_Widen_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen bluePen(Color::Blue,1);
	Pen greenPen(Color::Green, 10);
	//��������
	PointF points[] =
	{
		PointF(10.0f, 10.0f),
		PointF(130.0f, 90.0f),
		PointF(140.0f, 60.0f),
		PointF(60.0f, 90.0f)
	};

	GraphicsPath path;
	//�����������
	path.AddClosedCurve(points, 4);

	//����������ͬ��·�����������ؿ���
	GraphicsPath *path2=path.Clone();
	GraphicsPath *path3=path.Clone();
	GraphicsPath *path4=path.Clone();

	//ʹ�ÿ��Ϊ10�Ļ��ʻ���·��
	graphics.DrawPath(&Pen(Color::Blue,10), &path);
	RectF rect; path.GetBounds(&rect);

	//ʹ����ɫ�����ؿ�·������
	path2->Widen(&greenPen);
	//��ͼƽ�����ƣ������ؿ��·��
	graphics.TranslateTransform(rect.Width+10,0);
	graphics.DrawPath(&bluePen, path2);

	//����
	graphics.TranslateTransform(-rect.Width,rect.Height);
	//ʹ�ü���߷�����ɫ�����ؿ�·��
	greenPen.SetDashStyle(DashStyleDash);
	path3->Widen(&greenPen);
	//���·��
	graphics.FillPath(&SolidBrush(Color::Red), path3);

	//�Ի��ʽ������ű任 
	Pen pentmp(Color::Blue);
	pentmp.ScaleTransform(3.0f, 20.0f);
	path4->Widen(&pentmp);
	//��ͼƽ������
	graphics.TranslateTransform(rect.Width,0);
	graphics.DrawPath(&bluePen, path4);

	delete path2;
	delete path3;
	delete path4;
}

void Path_WidenDemo_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen bluePen(Color::Blue,1);
	Pen greenPen(Color::Green, 20);
	GraphicsPath path;
	//���һ��ֱ��
	path.AddLine(10,20,100,20);
	GraphicsPath *path2=path.Clone();

	PathData pathData;
	PathData pathData2;

	path.GetPathData(&pathData);
	int num1=path.GetPointCount();

	//����·���Ķ������Ϣ
	CString msg;
	for(int i=0;i<num1;i++)
	{
		CString s;
		s.Format("��%d������ֱ�Ϊ��X=%.2f\tY=%.2f\n",
			i,pathData.Points[i].X,pathData.Points[i].Y);
		msg+=s;
	}
	//����·��
	graphics.DrawPath(&Pen(Color::Blue), &path);

	//ʹ����ɫ�����ؿ�·������
	path2->Widen(&greenPen);
	path2->GetPathData(&pathData2);
	int num2=path2->GetPointCount();

	//��ͼƽ�����ƣ������ؿ��·��
	RectF rect; path.GetBounds(&rect);
	graphics.TranslateTransform(rect.Width*2,0);
	graphics.DrawPath(&bluePen, path2);
	graphics.ResetTransform();
	//�����ؿ��·���Ķ������Ϣ
	CString msg2;
	for(i=0;i<num2;i++)
	{
		CString s;
		s.Format("�ؿ���·����%d������ֱ�Ϊ��X=%.2f\tY=%.2f\n",
			i,pathData2.Points[i].X,pathData2.Points[i].Y);
		msg2+=s;
	}

	//���·���ؿ�ǰ��Ķ��������λ����Ϣ
	FontFamily  fontFamily(L"����");
	Font  font(&fontFamily, 12, FontStyleRegular, UnitPixel);
	graphics.TranslateTransform(0,120);
	MyDrawString(graphics, msg,font,SolidBrush(Color::Black), PointF(0,0));	
	graphics.TranslateTransform(0,font.GetHeight(&graphics)*(num1+1));
	MyDrawString(graphics, msg2,font,SolidBrush(Color::Black), PointF(0,0));	

}

void Region_FromPath_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//�趨�ı��������
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	FontFamily   fontFamily(L"����");
	//����·������
	GraphicsPath path;

	//��������׷���ı�
	path.AddString(L"��������",4,&fontFamily,
		(int)FontStyleRegular,100.0f, Point(0, 0), &StringFormat() );

	Pen pen(Color::Red);
	//����·��
	graphics.DrawPath(&pen, &path);
	graphics.TranslateTransform(0,80);
	//��·���й�������
	Region region(&path);
	//�������	
	graphics.FillRegion(&SolidBrush(Color::Red),&region);
}

void Region_Calculate_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	FontFamily  fontFamily(L"����");
	Font   font(&fontFamily, 16, FontStyleRegular, UnitPixel);

	SolidBrush solidBrush2(Color::Red);
	SolidBrush solidBrush(Color::Green);
	Pen pen(Color::Cyan);

	//�������εĶ˵�����
	Point points[]=
	{
		Point(75, 0), 
		Point(100, 50), 
		Point(150, 50), 
		Point(112, 75),
		Point(150, 150), 
		Point(75, 120), 
		Point(10, 150), 
		Point(37, 75), 
		Point(0, 50), 
		Point(50, 50),
		Point(75, 0)
	};

	//����·�����������
	GraphicsPath path;
	path.AddLines(points, sizeof(points)/sizeof(Point));

	//��С·��
	Matrix matrix;
	matrix.Scale(0.5f,0.5f);
	path.Transform(&matrix);

	//��ȡ·����ռ�ľ�������
	RectF tmp; path.GetBounds(&tmp);

	//��������2
	RectF rect(0,10,tmp.Width,50); 
	//�����ı���Ϣ�������
	RectF textout(0,tmp.Height,tmp.Width,font.GetHeight(&graphics)*2);

	//�����ı������ʽ��ˮƽ���С���ֱ����
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentFar);

	//���·�� 
	graphics.FillPath(&solidBrush2,&path);

	graphics.TranslateTransform(tmp.Width+10,0);
	//������ 
	graphics.FillRectangle(&solidBrush,rect);

	//��·���д�������
	Region region(&path); 

	//�󽻼�
	region.Intersect(rect);
	graphics.TranslateTransform(tmp.Width+10,0);
	//��佻��
	graphics.FillRegion(&solidBrush2, &region);
	MyDrawString(graphics, "����",font,SolidBrush(Color::Black),textout,format);	
	//����·����ռ�ľ�������
	graphics.DrawRectangle(&pen,tmp.X,tmp.Y,tmp.Width,tmp.Height);

	//�󲢼�
	Region region2(&path); 
	region2.Union(rect);
	graphics.TranslateTransform(tmp.Width+10,0);
	graphics.FillRegion(&solidBrush2, &region2);
	MyDrawString(graphics, "����",font,solidBrush,textout,format);	
	//����·����ռ�ľ�������
	graphics.DrawRectangle(&pen,tmp.X,tmp.Y,tmp.Width,tmp.Height);

	//�����������������
	graphics.TranslateTransform(-(tmp.Width+10)*3,tmp.Height+textout.Height);

	//���첢��
	Region region3(&path); 
	region3.Xor(rect);
	//����첢��
	graphics.FillRegion(&solidBrush2, &region3);
	MyDrawString(graphics, "�첢��",font,SolidBrush(Color::Black),textout,format);	
	//����·����ռ�ľ�������
	graphics.DrawRectangle(&pen,tmp.X,tmp.Y,tmp.Width,tmp.Height);

	//�󲹼�
	Region region4(&path); 
	region4.Complement(rect);
	graphics.TranslateTransform(tmp.Width+10,0);
	//��䲹��
	graphics.FillRegion(&solidBrush2, &region4);
	MyDrawString(graphics, "����",font,SolidBrush(Color::Black),textout,format);	
	//����·����ռ�ľ�������
	graphics.DrawRectangle(&pen,tmp.X,tmp.Y,tmp.Width,tmp.Height);

	//���ų⼯
	Region region5(&path); 
	region5.Exclude(rect);
	graphics.TranslateTransform(tmp.Width+10,0);
	//���ų⼯
	graphics.FillRegion(&solidBrush2, &region5);
	MyDrawString(graphics, "�ų⼯",font,SolidBrush(Color::Black),textout,format);	
	graphics.DrawRectangle(&pen,tmp.X,tmp.Y,tmp.Width,tmp.Height);
}

void Region_GetRects_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush solidBrush(Color::Red);
	Pen pen(Color::Black);
	GraphicsPath path;
	Matrix matrix;

	//��·���д�������
	path.AddEllipse(10, 0, 80, 120);
	Region pathRegion(&path);    
	//�������
	graphics.FillRegion(&solidBrush, &pathRegion);

	//��ȡ·���ľ�����ɼ���Ϣ����ʹ�ñ任��
	int count = pathRegion.GetRegionScansCount(&matrix);
	RectF *rects = new RectF[count];
	pathRegion.GetRegionScans(&matrix, rects, &count);
	//����ƽ�����ƣ��Ի��ƾ��μ������еľ���
	graphics.TranslateTransform(90,0); 
	for(int i=0; i<count; i++)
		graphics.DrawRectangle(&pen, rects[i]);	

	//ʵʩ�任
	matrix.Scale(1.0f,0.75f);
	matrix.Shear(0.2f,0.3f);
	//��ȡ·���ľ�����ɼ���Ϣ��ʹ�ñ任��
	count = pathRegion.GetRegionScansCount(&matrix);
	delete rects;
	rects = new RectF[count];
	pathRegion.GetRegionScans(&matrix, rects, &count);
	//����ƽ�����ƣ��Ի��Ʊ任��ľ��μ�
	graphics.TranslateTransform(90,0); 
	for(i=0; i<count; i++)
		graphics.DrawRectangle(&pen, rects[i]);	

	delete rects;
}

void Transform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush mySolidBrush1(Color::Blue);
	SolidBrush mySolidBrush2(_MakeA_RGB(155,Color::Chocolate));
	GraphicsPath myGraphicsPath;
	Rect myRect(60, 60, 60, 60);
	//��·������Ӿ���
	myGraphicsPath.AddRectangle(myRect);
	//���·��
	graphics.FillPath(&mySolidBrush1, &myGraphicsPath);

	// ��������任
	Matrix myPathMatrix;
	//ˮƽ����������������ֱ���򱣳ֲ���
	myPathMatrix.Scale(2, 1);
	myPathMatrix.Rotate(30.0f);
	//��·��ʵ������任
	myGraphicsPath.Transform(&myPathMatrix);

	//���任���·��
	graphics.FillPath(&mySolidBrush2, &myGraphicsPath);
}

void TranslateTransform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"nemo.bmp");
	//����ͼƬ����ʾ����
	Rect rect(0,0,110,70);
	for(int i=0;i<10;i++)
	{
		//��ʾͼƬ
		graphics.DrawImage(&image,rect);
		//��ͼƽ�����ƣ�ÿ����ˮƽ��������110������
		graphics.TranslateTransform(110,0);
	}
}

void RotateTransform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"nemo.bmp");

	//��ȡ��ǰ���ڵ����ĵ�
	Rect rect(0,0,MyClient.Width,MyClient.Height);
	PointF center(rect.Width/2,rect.Height/2);

	float offsetX=0;
	float offsetY=0;
	offsetX=center.X-image.GetWidth()/2;
	offsetY=center.Y-image.GetHeight()/2;
	//����ͼƬ��ʾ����:��ͼƬ�����ĵ��봰�ڵ����ĵ�һ��
	RectF picRect(offsetX,offsetY,image.GetWidth(),image.GetHeight());
	PointF Pcenter(picRect.X+picRect.Width/2,
		picRect.Y+picRect.Height/2);

	//��ͼƬ��������תһ��
	for(int i=0;i<361;i+=10)
	{
		// ��ͼƽ����ͼƬ�����ĵ���ת
		graphics.TranslateTransform(Pcenter.X, Pcenter.Y);
		graphics.RotateTransform(i);
		//�ָ���ͼƽ����ˮƽ�ʹ�ֱ�����ƽ��
		graphics.TranslateTransform(-Pcenter.X, -Pcenter.Y);
		//����ͼƬ����ʱ
		graphics.DrawImage(&image,picRect);	
		::Sleep(100);
		//���û�ͼƽ������б任
		graphics.ResetTransform();
	}
}

void DrawWatch_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Rect clientrect(0,0,
		MyClient.Width,MyClient.Height);

	//����·���ĸߺͿ�
	float WIDTH=clientrect.Width/2;
	float HEIGHT =clientrect.Height/2;

	//�����ı�������
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	FontFamily  fontFamily(L"Times New Roman");
	Font   font(&fontFamily, 14, FontStyleBold, UnitPixel);

	//����ͼƽ�������ԭ���Ƶ���������
	graphics.TranslateTransform(WIDTH /2,HEIGHT/2);
	//�����Ǳ���
	graphics.FillEllipse(&SolidBrush(Color::Black),
		HEIGHT/-2,HEIGHT/-2,HEIGHT, HEIGHT);
	//����ı�
	MyDrawString(graphics, "����/Сʱ",font,SolidBrush(Color::Green),
		PointF(-26,HEIGHT/-4-font.GetHeight(&graphics)));

	//���ƿ̶ȱ��
	graphics.RotateTransform(225);
	for(int x = 0; x<55;x++)
	{
		graphics.FillRectangle(&SolidBrush(Color::Green),
			Rect(-2, -(HEIGHT/2-2), 3, 15));
		graphics.RotateTransform(5);
	}

	//���û�ͼƽ�������任
	graphics.ResetTransform();

	graphics.TranslateTransform(WIDTH /2,HEIGHT/2);
	graphics.RotateTransform(225);
	int sp = 0;
	CString tmp;
	//���ƿ̶�ֵ(������)
	for(x = 0; x<7;x++)
	{
		tmp.Format("%d",sp);

		//���ƺ�ɫ�̶�
		graphics.FillRectangle(&SolidBrush(Color::Red),Rect(-3,(HEIGHT/2 -2)* -1,6,25));
		//������ֵ
		MyDrawString(graphics, tmp,font,SolidBrush(Color::Green), PointF(tmp.GetLength()*(-6),
			(HEIGHT/-2) + 25));
		//��ת45��
		graphics.RotateTransform(45);
		sp += 20;
	}

	//���û�ͼƽ�������任
	graphics.ResetTransform();
	graphics.TranslateTransform(WIDTH /2,HEIGHT/2);

	//����ָ����30����/�������
	float angle= 30*2.25f+ 225;
	graphics.RotateTransform((float)angle);

	Pen pen(Color::Blue,14);
	//������ñ
	pen.SetEndCap(LineCapArrowAnchor);
	pen.SetStartCap(LineCapRoundAnchor);
	//��ָ��
	graphics.DrawLine(&pen, PointF(0,0), PointF(0,(-1)*(HEIGHT/2.75F)));

	graphics.ResetTransform();
	graphics.TranslateTransform(WIDTH /2,HEIGHT/2);
	//�������ĵ�
	graphics.FillEllipse(&SolidBrush(Color::Black),-6,-9,14,14);
	graphics.FillEllipse(&SolidBrush(Color::Red),-7,-7,14,14);

	//�����ٶȼ��ޱ��
	pen.SetWidth(4);
	pen.SetColor(Color::Black);
	pen.SetEndCap(LineCapRound);
	pen.SetStartCap(LineCapFlat);
	graphics.DrawLine(&pen, PointF(HEIGHT/15.75F,HEIGHT/3.95F),
		PointF(HEIGHT/10.75F,HEIGHT/5.2F));
	pen.SetColor(Color::Red);
	graphics.DrawLine(&pen, PointF(HEIGHT/15.75F,HEIGHT/3.95F),
		PointF(HEIGHT/15.75F,HEIGHT/4.6F));
}

void ScaleTransform_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Rect clientrect(0,0,
		MyClient.Width,MyClient.Height);
	//��ȡ��ǰ���ڵ����ĵ�
	float width=clientrect.Width/2;
	float height=clientrect.Height/2;
	PointF center(width,height);

	//���þ��γ�ʼ��СΪ30*30
	float offsetX=center.X-15;
	float offsetY=center.Y-15;

	//������ε���������:�þ��ε����ĵ��봰�ڵ����ĵ�һ��
	RectF rotateRect(offsetX,offsetY,30,30);
	PointF Pcenter(rotateRect.X+rotateRect.Width/2,
		rotateRect.Y+rotateRect.Height/2);

	//���ó�ʼ���ű���
	int scale=1;
	//�Ծ���rotateRect��ת360�Ȳ����ϷŴ����
	for(int i=0;i<360;i+=60)
	{
		// ��ͼƽ����ͼƬ�����ĵ���ת
		graphics.TranslateTransform(Pcenter.X, Pcenter.Y);
		//��ˮƽ�ʹ�ֱ������ͬʱ�������
		graphics.ScaleTransform(scale,scale);
		graphics.RotateTransform(i);
		//�ָ���ͼƽ����ˮƽ�ʹ�ֱ�����ƽ��
		graphics.TranslateTransform(-Pcenter.X, -Pcenter.Y);
		//���ƾ��β���ʱ
		graphics.DrawRectangle(&Pen(Color::Black),
			rotateRect.X,rotateRect.Y,rotateRect.Width,rotateRect.Height);
		::Sleep(100);
		//���û�ͼƽ������б任
		graphics.ResetTransform();
		scale++;
	}
}

void RectScale_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Rect clientrect(0,0,
		MyClient.Width,MyClient.Height);
	//��ȡ��ǰ���ڵ����ĵ�
	float width=clientrect.Width/2;
	float height=clientrect.Height/2;
	PointF center(width,height);

	//���þ��γ�ʼ��СΪ30*30
	float offsetX=center.X-15;
	float offsetY=center.Y-15;

	//������ε���������:�þ��ε����ĵ��봰�ڵ����ĵ�һ��
	RectF rotateRect(offsetX,offsetY,30,30);
	PointF Pcenter(rotateRect.X+rotateRect.Width/2,
		rotateRect.Y+rotateRect.Height/2);

	//���ó�ʼ���ű���
	int scale=0;
	//�Ծ���rotateRect��ת360�Ȳ����ϷŴ����
	for(int i=0;i<361;i+=60)
	{
		// ��ͼƽ����ͼƬ�����ĵ���ת
		graphics.TranslateTransform(Pcenter.X, Pcenter.Y);
		//��ˮƽ�ʹ�ֱ������ͬʱ���Ӿ��εĿ�Ⱥ͸߶�
		rotateRect.Inflate(scale*15,scale*15);
		graphics.RotateTransform(i);
		//�ָ���ͼƽ����ˮƽ�ʹ�ֱ�����ƽ��
		graphics.TranslateTransform(-Pcenter.X, -Pcenter.Y);
		//����ͼƬ����ʱ
		graphics.DrawRectangle(&Pen(Color::Black),
			rotateRect.X,rotateRect.Y,rotateRect.Width,rotateRect.Height);
		::Sleep(100);
		//���öԾ��δ�С�����б任
		graphics.ResetTransform();
		rotateRect.Inflate(-scale*15,-scale*15);
		scale++;
	}

}

void FontRotate_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	FontFamily  fontFamily(L"����");
	Font        myFont(&fontFamily, 20, FontStyleBold, UnitPixel);
	SolidBrush redBrush(Color::Red);

	//�����ı��������
	RectF layoutRect(myFont.GetHeight(&graphics),myFont.GetHeight(&graphics),
		MyClient.Width/2,MyClient.Height/2);

	StringFormat format;
	//�����ı������ʽ
	format.SetAlignment(StringAlignmentNear);
	format.SetLineAlignment(StringAlignmentCenter);
	//���ı������������óɴ��ڵ�����
	graphics.TranslateTransform(layoutRect.Width,layoutRect.Height);

	//����תʱÿ��30������ı�
	for(int i=0;i<360;i+=30)
	{
		//��ת��ͼƽ��
		graphics.RotateTransform(i);
		MyDrawString(graphics, " ��ת����",myFont, redBrush,
			layoutRect, format);
		//�ָ���������ת
		graphics.RotateTransform(-i);
	}

}

void MirrorText_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	SolidBrush redBrush(Color::Red);

	//�������壬���ھ����ı����
	FontFamily  fontFamily(L"���Ŀ���");
	Font        myFont(&fontFamily,
		48, FontStyleRegular, UnitPixel);
	//����Ӣ�����壬������ʾ�ı����������
	FontFamily  fontFamily2(L"Courier New");
	Font        myFont2(&fontFamily2, 16, FontStyleRegular, UnitPixel);

	//�����ı��������
	RectF layoutRect(myFont.GetHeight(&graphics),myFont.GetHeight(&graphics),
		MyClient.Width/2,MyClient.Height/2);

	StringFormat format;

	//�����ı����ʱ��ȷλ��
	//�о࣭���в��֡�(��Ƶ�λ)
	float ascent =fontFamily.GetLineSpacing(FontStyleRegular)- 
		fontFamily.GetCellDescent(FontStyleRegular);
	//�о࣭���в��֡�(��Ƶ�λ)
	float ascent2 =fontFamily.GetLineSpacing(FontStyleRegular)-
		fontFamily.GetCellAscent(FontStyleRegular);

	//���ϡ��²��������Ƶ�λת�������ص�λ
	float ascentPixel = 	myFont.GetSize()*
		ascent /(fontFamily.GetEmHeight(FontStyleRegular));
	float ascentPixel2 = 	myFont.GetSize()* 
		ascent2 /(fontFamily.GetEmHeight(FontStyleRegular));

	//��ͼƽ������
	graphics.TranslateTransform(0,MyClient.Height/4);
	//��������������ı�
	MyDrawString(graphics, "�������",myFont,redBrush,
		PointF(0,-myFont.GetHeight(&graphics)+ascentPixel2), format);

	//��ͼƽ�����ƣ���ʾ��ǰ�ı��������
	graphics.TranslateTransform(200,0);
	CString msg;
	for(int i=0;i<3;i++)
	{
		msg.Format("Line %d...........",i);
		MyDrawString(graphics, msg,myFont2,redBrush, 
			PointF(0,myFont2.GetHeight(&graphics)*i),format);
	}

	//�ָ��Ի�ͼƽ�������
	graphics.TranslateTransform(-200,0);

	//��ͼƽ���ڴ�ֱ������
	graphics.ScaleTransform(1,-1);
	//��������ı�
	MyDrawString(graphics, "�������",myFont,SolidBrush(Color::Gray), 
		PointF(0,-ascentPixel), format);
	//��ͼƽ���ٴ����ƣ���ʾ��ǰ�ı��������
	graphics.TranslateTransform(200,0);
	for(i=0;i<3;i++)
	{
		msg.Format("Line %d...........",i);
		MyDrawString(graphics, msg,myFont2, SolidBrush(Color::Gray),
			PointF(0,myFont2.GetHeight(&graphics)*i), format);
	}

	//�����ڻ�ͼƽ���Ͻ��е����б任����ʾˮƽ�����ı����
	graphics.ResetTransform ( ) ; 
	//��ͼƽ������
	graphics.TranslateTransform(MyClient.Width/2,
		MyClient.Height/2+myFont.GetHeight(&graphics)*2);
	//��������������ı�
	MyDrawString(graphics, "�������",myFont, redBrush,
		PointF(0,0), format);
	//��ͼƽ����ˮƽ������
	graphics.ScaleTransform(-1,1);
	//���ˮƽ�����ı�
	MyDrawString(graphics, "�������",myFont, SolidBrush(Color::Gray),
		PointF(0,0), format);
}


void Matrix_ListElements_Click_1()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush redBrush(Color::Red);
	FontFamily  fontFamily(L"���Ŀ���");
	Font  myFont(&fontFamily,20,
		FontStyleRegular, UnitPixel);		

	//����ƽ�Ʊ任	
	graphics.TranslateTransform(10,10);
	graphics.TranslateTransform(20,10); 
	Matrix m;;
	graphics.GetTransform(&m);
	//��ȡ�Ѿ�ʵʩ�ڻ�ͼƽ�������任
	CString msg;

	float x[6]; m.GetElements(x);
	//��������ÿһ��Ԫ��
	for(int i=0; i<6; i++)
	{			
		msg.Format("��%d������Ԫ��Ϊ%.2f",i,x[i]);
		MyDrawString(graphics, msg,myFont, redBrush,
			PointF(0, myFont.GetHeight(&graphics)*(i+1)));
	}
}

void MatrixPos_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue,4);
	Pen pen2(Color::Gray);

	FontFamily  fontFamily(L"����");
	Font  myFont(&fontFamily,
		20, FontStyleRegular, UnitPixel);

	//��ȡ��ǰ���ڵĴ�С
	Rect rect(0,0,
		MyClient.Width,MyClient.Height);

	//���ö�����Բ�ľ���
	Rect r(-40, -65,80, 130);
	Matrix matrix;
	graphics.TranslateTransform(rect.Width/2, rect.Height/2); 
	//ʹ��Ĭ�ϵ���ת˳��(MatrixOrderPrepend)
	graphics.RotateTransform(20);   
	//��ȡ�Ի�ͼƽ���Ѿ����е�����任
	graphics.GetTransform(&matrix);
	//������Բ
	graphics.DrawEllipse(&pen, r);

	//ʹ��MatrixOrderAppend��ת˳��
	graphics.ResetTransform();
	graphics.TranslateTransform(rect.Width/2, rect.Height/2); 
	graphics.RotateTransform(20,MatrixOrderAppend);   
	//ʹ�ú�ɫ���ʻ�����һ����Բ
	graphics.DrawEllipse(&Pen(Color::Red,1), r);
	Matrix matrix2;
	graphics.GetTransform(&matrix2);

	//��������任���Դ������ĵ�Ϊԭ�����������
	graphics.ResetTransform();
	graphics.DrawLine(&pen2, 0, rect.Height/2, 
		rect.Width, rect.Height/2);
	graphics.DrawLine(&pen2, rect.Width/2, 
		0, rect.Width/2, rect.Height);  

	CString msg;
	//��ȡ����Ԫ��ֵ
	float x[6]; matrix.GetElements(x);
	//�������Ԫ��ֵ
	int i=0;
	for (i=0; i<6; i++)
	{
		msg.Format("%8.2f",x[i]);
		//���������
		if(i==1||i==3||i==5)
		{
			//��ֱ����������һ��
			graphics.TranslateTransform(0,myFont.GetHeight(&graphics));
			MyDrawString (graphics, msg, myFont, SolidBrush(Color::Black), PointF(0,0));
		}
	}
}

void Martrix_Invert_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen myPen(Color::Blue,4);
	Matrix matrix(1.0f, 0.0f, 0.0f, 1.0f, 30.0f, 20.0f);
	//�������Ƿ���棿
	if(!matrix.IsInvertible())
	{
		AfxMessageBox("�þ���Ϊ��������Σ��޷���ʾ");
		return;
	}
	graphics.SetTransform(&matrix);
	for(int i=0;i<200;i++) 
	{
		//���������
		matrix.Invert();
		//�Ի�ͼƽ���������任
		graphics.SetTransform(&matrix);
		graphics.DrawRectangle(&myPen, 35, 25, 200, 100);  
	}
}

void Matrix_Multiply_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"Arial");
	Font    myFont(&fontFamily,
		16, FontStyleRegular, UnitPixel);
	//����ͼƬ
	Bitmap image(L"jieba.bmp");

	//����
	Matrix matrix1(0.80f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f); 
	//λ��
	Matrix matrix2(1.0f, 0.0f, 0.0f, 1.0f, 20.0f, 10.0f);  
	//�����������·�תͼƬ��X����Y��Ե�
	Matrix matrix3(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	//��һ��׷�ӱ任
	matrix1.Multiply(&matrix2, MatrixOrderAppend);
	//�ڶ���׷�ӱ任
	matrix1.Multiply(&matrix3,MatrixOrderAppend);
	//���и��ϱ任
	graphics.SetTransform(&matrix1);

	//����ͼƬ
	graphics.DrawImage(&image, 0, 0);  
	//��ȡ�Ѿ������ڻ�ͼƽ���ϵ�����任
	Matrix matrix;
	graphics.GetTransform(&matrix);
	graphics.ResetTransform();
	//����λ���ϲ鿴�任������Ϣ
	graphics.TranslateTransform(image.GetHeight(),0);

	//��ȡ����Ԫ��ֵ
	float x[6]; matrix.GetElements(x);
	//���ÿһ������Ԫ�ص�ֵ
	CString msg;
	int i=0;
	for(i=0; i<6; i++)
	{
		msg.Format("%6.2f",x[i]);
		//���������
		if(i==1||i==3||i==5)
		{
			//��ֱ����������һ��
			graphics.TranslateTransform(0,myFont.GetHeight(&graphics));
			MyDrawString(graphics, msg,myFont,SolidBrush(Color::Black), 
				PointF(0,0));
		}
	}
}

void Matrix_TransformPoints_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush redBrush(Color::Red);
	SolidBrush blueBrush(Color::Blue);
	Pen pen1(Color::Blue,2);
	Pen pen2(Color::Red,1);

	//���幹�����ߵĵ�����
	Point points[] =
	{
		Point(50, 100), 
		Point(100, 50),
		Point(150, 125),
		Point(200, 100),
		Point(250, 125),
	};

	//��������(δʹ�ñ任ʱ)
	graphics.DrawCurve(&pen1, points, 5);
	//�������߶������Ϣ
	for(int i=0;i<5;i++)	
	{
		graphics.FillEllipse(&blueBrush,
			points[i].X-5,points[i].Y-5,10,10);
	}

	//����һ������ֱ��������������Ϊ0.5�ľ���
	Matrix matrix(1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f);
	//��points�����е�ÿһ����Ա���о�������
	matrix.TransformPoints(points);

	//��������(ʹ�ñ任��)	
	graphics.DrawCurve(&pen2, points,5);

	//�ٴλ������߶������Ϣ
	for(i=0;i<5;i++)	
	{
		graphics.FillEllipse(&redBrush,
			points[i].X-5,points[i].Y-5,10,10);
	}
}

void Matrix_TransformPoints2_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//��������ϵ��
	FontFamily   fontFamily(L"����");

	SolidBrush redBrush(Color::Red);
	//�����ı��������
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	//����·������
	GraphicsPath path;
	//��������׷���ı��������СΪ60
	path.AddString(L"������Ч",4 ,&fontFamily,(int)FontStyleRegular, 
		60, Point(0, 0), &StringFormat());

	//��ȡ·���ĵ���Ϣ
	//��ȡ·���ĵ�������Ϣ
	PathData pathdata;
	path.GetPathData(&pathdata);

	//���ı���ˮƽ��������С���ڴ�ֱ����������
	Matrix matrix(0.50f, 0.0f, 0.0f, 3.5f, 0.0f,0.0f);	

	//��points�����е�ÿһ����Ա���о�������
	matrix.TransformPoints(pathdata.Points, pathdata.Count);
	//���ݼ����ĵ����¹���·��
	GraphicsPath newpath(pathdata.Points,pathdata.Types,pathdata.Count);
	//���·��
	graphics.FillPath(&redBrush,&newpath);

	//�ڶ�����Ч
	Matrix matrix2(0.6f, 0.5f, 0.20f, 1.5f, 160.0f, -40.0f);
	PathData pathdata2;
	path.GetPathData(&pathdata2);
	//�����еĵ���м���
	matrix2.TransformPoints(pathdata2.Points, pathdata2.Count);
	//���ݼ����ĵ����¹���·��
	GraphicsPath newpath2(pathdata2.Points,pathdata2.Types,pathdata2.Count);
	graphics.FillPath(&redBrush,&newpath2);
}

void Matrix_TransformVectors_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue, 7);
	pen.SetEndCap(LineCapArrowAnchor);
	SolidBrush brush(Color::Blue);

	// ����һ�����һ������
	PointF point[]={PointF(100, 50)};
	PointF vector[]={PointF(100, 50)};

	// ���Ƶ�point
	graphics.FillEllipse(&brush, RectF(point[0].X-5, point[0].Y-5, 10, 10));
	//����(10,10)��vector��ʾ��λ����������
	graphics.DrawLine(&pen, PointF(10, 10), vector[0]);

	// ����任����
	Matrix matrix(0.8f, 0.6f, -0.6f, 0.8f, 100.0f, 0.0f);
	//�Ե�point��λ����Ϣ���б任
	matrix.TransformPoints(point);
	//�Ե�vector��λ����Ϣ���ж�ά�����任
	matrix.TransformVectors(vector);

	// ���Ʊ任��ĵ�
	pen.SetColor(Color::Red);
	brush.SetColor(Color::Red);
	graphics.FillEllipse(&brush, RectF(point[0].X - 5, point[0].Y - 5, 10, 10));
	//����(10,10)��任���vector��ʾ��λ����������
	graphics.DrawLine(&pen, PointF(10, 10), vector[0]); 
}

void Matrix_RotateAt_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Pen pen(Color::Blue,4);
	Pen pen2(Color::Gray);

	//��ȡ��ǰ��������
	RectF rect(0,0,MyClient.Width,MyClient.Height);;
	//���첢ƽ�ƾ��󵽴������ĵ�
	Matrix matrix;
	matrix.Translate(rect.Width/2, rect.Height/2);  

	//����ͼƽ��������תһ��
	for(int i=0;i<360;i+=30)
	{
		//��ת��������ڴ������ĵ�
		matrix.RotateAt(i, PointF(rect.Width/2, 
			rect.Height/2), MatrixOrderAppend);
		//����ת��ľ��������ڻ�ͼƽ��
		graphics.SetTransform(&matrix);
		//������Բ
		graphics.DrawEllipse(&pen, -80, -30, 160, 60);
		//���������ڻ�ͼƽ�������еı任
		graphics.ResetTransform();
	}

	//�Դ������ĵ�Ϊԭ�����������
	graphics.DrawLine(&pen2, PointF(0, rect.Height/2),
		PointF(rect.Width, rect.Height/2));
	graphics.DrawLine(&pen2, PointF(rect.Width/2, 0), 
		PointF(rect.Width/2, rect.Height));
}

void Matrix_Shear_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"jieba.bmp");
	//����ͼƬ����ʾ����
	Rect rect(0,0,100,150);
	//����Դͼ
	graphics.DrawImage(&image,rect);

	Matrix matrix;
	//����ˮƽͶ������
	matrix.Shear(0.8f,0.0f);
	//�Ի�ͼƽ��ʹ��Ͷ��任
	graphics.SetTransform(&matrix);
	graphics.TranslateTransform(100,0);
	//����Ͷ��任���ͼƬ
	graphics.DrawImage(&image,rect);

	graphics.ResetTransform();
	Matrix matrix2;
	//���ô�ֱͶ������
	matrix2.Shear(0.0f,0.8f);
	//�Ի�ͼƽ��ʹ��Ͷ��任
	graphics.SetTransform(&matrix2);
	graphics.TranslateTransform(200,0);
	//����Ͷ��任���ͼƬ
	graphics.DrawImage(&image,rect);
}

void Matrix_TextoutShear_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"���Ŀ���");
	Font        myFont(&fontFamily, 20, FontStyleRegular, UnitPixel);

	Font myfont(L"Times New Roman", 100);	
	Matrix mymat;
	//Ͷ��
	mymat.Shear( -1.4f, 0.0f ) ;
	//����
	mymat.Scale( 1, 0.5f ) ;
	//ƽ��
	mymat.Translate ( 236, 170 ) ; 
	//�Ի�ͼƽ��ʵʩ����任����
	graphics.SetTransform(&mymat);

	SolidBrush mybrush(Color::Gray);
	SolidBrush redbrush(Color::Red);
	//������Ӱ
	MyDrawString(graphics, "Hello",myfont,mybrush, PointF(0, 50));
	graphics.ResetTransform ( ) ;
	//����ǰ��
	MyDrawString(graphics, "Hello",myfont,redbrush, PointF(0, 50));
	CString msg;
	//��ȡ����Ԫ��ֵ
	float x[6]; mymat.GetElements(x);
	//���ÿһ������Ԫ�ص�ֵ
	int i=0;
	for(; i<6; i++)
	{
		msg.Format("{0,%6.2f}",x[i]);
		//���������
		if(i==1||i==3||i==5)
		{
			MyDrawString(graphics, msg,myFont,SolidBrush(Color::Black), 
				PointF(0,0));
			//��ֱ����������һ��
			graphics.TranslateTransform(0,myFont.GetHeight(&graphics));
		}
	}
}

void Matrix_ChangeFontHeight_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//��������ϵ��
	FontFamily   fontFamily(L"����");
	//����·������
	GraphicsPath path;
	SolidBrush redBrush(Color::Red);

	//�����ı��������
	graphics.SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	//��������׷���ı��������СΪ80
	path.AddString(L"��С����",4,&fontFamily,(int)FontStyleRegular, 
		80, Point(0, 0), &StringFormat());
	//��ȡ·����ռ�ľ�������
	RectF bound; path.GetBounds(&bound);
	//��ȡ·����������ĵ�
	float halfH=bound.Height/2;
	float halfW=bound.Width/2;

	//��·��ʵʩ�任������·����������ĵ�
	Matrix pathMartrix(1,0,0,1,-halfW,-halfH);
	path.Transform(&pathMartrix);

	//��ȡ·���ĵ���Ϣ
	//��ȡ·���ĵ�������Ϣ
	PathData pathdata;
	path.GetPathData(&pathdata);

	//���ζ�·���Ķ�����Yֵ��������
	for(int i=0;i<pathdata.Count;i++)
	{
		//���ݸõ��·�����ľ���ռ����·�����ȵı�������Yֵ
		pathdata.Points[i].Y*=2*(bound.Width-abs(pathdata.Points[i].X))/bound.Width;
	}

	//���ݸ��ĺ��·����������¹���·��
	GraphicsPath newpath(pathdata.Points,pathdata.Types,pathdata.Count);
	//����ͼƽ���ԭ���Ƶ���������
	graphics.TranslateTransform(MyClient.Width/2,MyClient.Height/2-40);
	//���·��
	graphics.FillPath(&redBrush,&newpath);
}

void ColorMatrix_Start_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap image(L"ColorInput.bmp");
	int width = image.GetWidth();
	int  height = image.GetHeight();
	ImageAttributes  imageAttributes;

	//����ɫ�ʱ任����
	ColorMatrix colorMatrix=
	{
		2.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//����Դͼ
	graphics.DrawImage(&image, 0, 0);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, width, height),
		0, 0,
		width, height,UnitPixel,
		&imageAttributes);
}

void TranslateColor_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap  image(L"ColorBar.bmp");
	ImageAttributes  imageAttributes;
	int  width = image.GetWidth();
	int  height = image.GetHeight();

	//����ɫ�ʱ任����
	ColorMatrix colorMatrix=
	{
		1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.75f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(&colorMatrix, 
		ColorMatrixFlagsDefault,ColorAdjustTypeBitmap);

	//����Դͼ
	graphics.DrawImage(&image, 0, 0);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(&image, Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,&imageAttributes);
}

void ScaleColor_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap          image(L"ColorBar.bmp");
	ImageAttributes imageAttributes;
	int             width = image.GetWidth();
	int             height = image.GetHeight();

	//����ɫ�ʱ任����1
	ColorMatrix colorMatrix=
	{
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����2
	ColorMatrix colorMatrix2=
	{
		0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 500.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����1
	imageAttributes.SetColorMatrix(
		&colorMatrix, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//����Դͼ
	graphics.DrawImage(&image, 0, 0);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, width, height),
		0, 0,
		width, height,UnitPixel,
		&imageAttributes);

	//����Ѿ���ȡ��ɫ�ʱ任
	imageAttributes.ClearColorMatrix(ColorAdjustTypeBitmap);
	//���¼�����һ�任����Matrix2
	imageAttributes.SetColorMatrix(
		&colorMatrix2, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//��ʾʹ��Matrix2��ɫ�ʵ������
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, width, height),
		0, 0,
		width, height,UnitPixel,
		&imageAttributes);
}

void RotateColor_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap    image(L"Colorinput.bmp");
	int   width = image.GetWidth();
	int   height = image.GetHeight();
	float   degrees = 90;
	//�ӽǶȵ�����
	double           r = degrees * PI/ 180.0f;  
	ImageAttributes  imageAttributes;
	//����Դͼ
	graphics.DrawImage(&image, 0, 0);

	//��ɫ������ɫ��ת
	ColorMatrix colorMatrix=
	{
		(float)cos(r),  (float)sin(r), 0.0f, 0.0f, 0.0f,
		-(float)sin(r), (float)cos(r), 0.0f, 0.0f, 0.0f,
		0.0f,    0.0f,   1.0f, 0.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 0.0f, 1.0f
	};

	//ʹ��ɫ�ʱ任�������ͼƬ(R->B)
	graphics.TranslateTransform(width+10,0);
	//����R->Bɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	graphics.DrawImage(
		&image, 
		Rect(0, 10, width, height),  
		0, 0,width,height,      
		UnitPixel,
		&imageAttributes);

	//����Ѿ���ȡ��ɫ�ʱ任
	imageAttributes.ClearColorMatrix(ColorAdjustTypeBitmap);

	//���¼�����һ�任����Matrix2
	//��ɫ���ź�ɫ��ת
	ColorMatrix colorMatrix2=
	{
		1,  0, 0.0f, 0.0f, 0.0f,
		0, (float)cos(r), (float)sin(r), 0.0f, 0.0f,
		0.0f, -(float)sin(r), (float)cos(r), 0.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 0.0f, 1.0f
	};

	imageAttributes.SetColorMatrix(
		&colorMatrix2, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//�ڵڶ������
	graphics.ResetTransform();
	graphics.TranslateTransform(0,height+10);
	graphics.DrawImage(&image, 
		Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,
		&imageAttributes);

	//����Ѿ���ȡ��ɫ�ʱ任
	imageAttributes.ClearColorMatrix(ColorAdjustTypeBitmap);
	//��ɫ���ź�ɫ��
	ColorMatrix colorMatrix3=
	{
		(float)cos(r),  0, -(float)sin(r), 0.0f, 0.0f,
		0, 1, 0.0f, 0.0f, 0.0f,
		(float)sin(r), 0, (float)cos(r), 0.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,    0.0f,   0.0f, 0.0f, 1.0f
	};

	//���¼�����һ�任����Matrix3
	imageAttributes.SetColorMatrix(
		&colorMatrix3, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, width, height),
		0, 0,
		width, height,UnitPixel,
		&imageAttributes);
}

void ColorShear_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap  image(L"Colorinput.bmp");
	ImageAttributes  imageAttributes;
	int   width = image.GetWidth();
	int   height = image.GetHeight();

	//����ɫ�ʱ任����
	ColorMatrix colorMatrix=
	{
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//����Դͼ
	graphics.DrawImage(&image, 0, 0);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(&image, Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,&imageAttributes);

}

void ColorRemap_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//������ɫ������ͼƬ
	Bitmap            image(L"Nemo_Blue.bmp");
	ImageAttributes  imageAttributes;

	int   width = image.GetWidth();
	int   height = image.GetHeight();
	//����ɫ�滻�ɰ�ɫ,�Դﵽ�ٳ���Ч��
	ColorMap   colorMap;
	colorMap.oldColor = Color(255, 0, 0, 255); 
	colorMap.newColor = Color(255, 255,255,255);
	//����ɫ��ת����
	ColorMap remapTable[1];  remapTable[0]=colorMap;

	//����ͼƬ��ɫ����Ϣ
	imageAttributes.SetRemapTable(1, remapTable, ColorAdjustTypeBitmap);
	//����ԭʼͼ��
	graphics.DrawImage(&image, 0, 0, width, height);
	//�����Ѿ��ٳ�����ɫ����ͼ��
	graphics.DrawImage(&image, 
		Rect(width+10, 0, width, height),  //Ŀ������
		0, 0,        // Դͼ���Ͻ�����
		width,       // Դͼ��
		height,      // Դͼ��
		UnitPixel,
		//ͼƬ��ɫ����Ϣ
		&imageAttributes);
}

void SetRGBOutputChannel_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap  image(L"jieba.bmp");
	//����Դͼ
	graphics.DrawImage(&image, 0, 0);

	int  width = image.GetWidth();
	int height = image.GetHeight();
	ImageAttributes  imageAttributes;

	//���ú�ɫͨ��
	ColorMatrix colorMatrix=
	{
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(&image, Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,&imageAttributes);

	//����Ѿ���ȡ��ɫ�ʱ任
	imageAttributes.ClearColorMatrix(ColorAdjustTypeBitmap);
	//������ɫͨ��
	ColorMatrix colorMatrix2=
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix2, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.ResetTransform();
	graphics.TranslateTransform(0,height+10);
	graphics.DrawImage(&image, Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,&imageAttributes);

	//����Ѿ���ȡ��ɫ�ʱ任
	imageAttributes.ClearColorMatrix(ColorAdjustTypeBitmap);

	//������ɫͨ��
	ColorMatrix colorMatrix3=
	{
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//����ɫ�ʱ任����
	imageAttributes.SetColorMatrix(
		&colorMatrix3, 
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	//ʹ��ɫ�ʱ任�������ͼƬ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(&image, Rect(0, 0, width, height),
		0, 0,width, height,UnitPixel,&imageAttributes);
}

void Metafile_Click()
{
	//	Note:  To record a metafile, you must construct a Graphics
	//object based on a Metafile object. The recording of the metafile
	//ends when that Graphics object is deleted or goes out of scope.

	//�½�һ��ͼԪ�ļ�
	HDC hdc =GetGraphics().GetHDC();
	Metafile metaFile1(L"ͼԪ�ļ�ʾ��.emf", hdc);
	{
		//ʹ��Metafile����ĵ�ַ��Ϊ��ͼƽ��
		Graphics graphics(&metaFile1);

		//����һ���ɺ쵽���Ľ���ɫ��ˢ
		LinearGradientBrush RtoBBrush(
			Point(0, 10),
			Point(200, 10),
			Color::Red,   
			Color::Blue);

		//����һ���������ƵĽ���ɫ��ˢ
		LinearGradientBrush BtoYBrush(
			Point(0, 10),
			Point(200, 10),
			Color::Blue,   
			Color::Yellow);
		Pen bluePen(Color::Blue);

		// ���µĲ���������Ļ�ϻ���һ����ͼ��
		Rect ellipseRect(0, 0, 200, 200);
		Rect left(0, 50, 100, 100);
		graphics.DrawArc(&bluePen,left,180.0f,180.0f);
		Rect right(100, 50, 100, 100);
		graphics.FillPie(&RtoBBrush, ellipseRect,0.0f,180.0f);
		graphics.FillPie(&BtoYBrush, ellipseRect,180.0f,180.0f);
		graphics.FillPie(&RtoBBrush, left,180.0f,180.0f);
		graphics.FillPie(&BtoYBrush, right,0.0f,180.0f);

		//�ı���� 
		SolidBrush solidBrush(Color::Black);
		FontFamily fontFamily(L"����");
		Font font(&fontFamily, 27,
			FontStyleRegular, UnitPixel);
		MyDrawString(graphics, "ͼԪ�ļ�ʾ��", font, solidBrush,
			PointF(20.0f, 80.0f));
		//���ˣ�GDI+���е�ֻ����Ӳ���д��ͼƬ��Ϣ�Ĳ���
	}

	//������Ļ�ͼ��Ϣ���лط�
	Graphics playbackGraphics(hdc);
	playbackGraphics.Clear(Color::White);
	//�򿪲���ʾͼԪ�ļ�
	Metafile metaFile2(L"ͼԪ�ļ�ʾ��.emf");
	playbackGraphics.DrawImage(&metaFile2, Point(0,0));
	//�ͷ�HDC
	playbackGraphics.ReleaseHDC(hdc);
}

void CroppingAndScaling_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap image(L"nemo.bmp");
	int width = image.GetWidth();
	int height = image.GetHeight();

	// Ŀ����ʾ������Դͼ��С�Ļ����ϷŴ�1.4��
	RectF destinationRect(
		width+10, 0.0f, 1.4f* width, 1.4f* height);
	//����Դͼ
	graphics.DrawImage(&image, 0, 0);

	//��Ŀ�����������λͼ
	graphics.DrawImage(
		&image,
		destinationRect,
		0.f, 0.f,    // ԭͼ���Ͻ�
		0.65f*width,      // ����ʾԭͼ��ȵ�65%����
		0.65f*height,      // ����ʾԭͼ�߶ȵ�65%����
		UnitPixel);
}

void UsingInterpolationMode_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"eagle.bmp");
	int width = image.GetWidth();
	int height = image.GetHeight();

	//����Դͼ
	graphics.DrawImage(
		&image,
		Rect(0, 0, width, height),  //Ŀ������ 
		0, 0,        //Դͼ���Ͻ�����
		width,       //Դͼ���
		height,      //Դͼ��
		UnitPixel);

	//��ͼƽ������
	graphics.TranslateTransform( width+10,0);
	//���ٽ���ֵ��(������)
	graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
	graphics.DrawImage(
		&image,
		RectF(0.0f, 0.0f, 0.6f*width, 0.6f*height),  //Ŀ������
		0, 0,        //Դͼ���Ͻ�����
		width,       //Դͼ���
		height,      //Դͼ��
		UnitPixel);

	//��ͼƽ������
	graphics.TranslateTransform( 0.6f*width+10,0);
	// ������˫���Բ�ֵ��
	graphics.SetInterpolationMode(InterpolationModeHighQualityBilinear);
	graphics.DrawImage(
		&image,
		RectF(0, 0, 0.6f * width, 0.6f * height),  //Ŀ������
		0, 0,        //Դͼ���Ͻ�����
		width,       //Դͼ���
		height,      //Դͼ��
		UnitPixel);

	//��ͼƽ������
	graphics.TranslateTransform(width*0.6f+10, 0.f);
	// ������˫���β�ֵ��
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	graphics.DrawImage(
		&image,
		RectF(0, 0, 0.6f * width, 0.6f * height),  //Ŀ������
		0, 0,        //Դͼ���Ͻ�����
		width,       //Դͼ���
		height,      //Դͼ��
		UnitPixel);
}

void RotateFlip_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	//����ͼƬ	
	Bitmap photo(L"nemo2.bmp");

	//�õ�ͼƬ�ߴ�
	int iWidth = photo.GetWidth();
	int iHeight = photo.GetHeight();
	//����ԭʼͼƬ
	graphics.DrawImage(&photo, 10+photo.GetWidth()+2,
		10, photo.GetWidth(), photo.GetHeight());
	//ˮƽ��תͼƬ 
	photo.RotateFlip(RotateNoneFlipX);  
	//��ת���ͼƬ
	graphics.DrawImage(&photo, 10, 10, photo.GetWidth(), photo.GetHeight()); 	
}

void ImageSkewing_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼ�ε�Ŀ����ʾ����
	Point destination[]=
	{
		Point(200, 20),   //ԭʼͼ�����Ͻ�ӳ��������
		Point(110, 100), //ԭʼͼ�����Ͻ�ӳ��������
		Point(250, 30)  //ԭʼͼ�����½�ӳ��������
	};
	Bitmap image(L"Stripes.bmp");
	// ����ԭʼͼ��
	graphics.DrawImage(&image, 0, 0);

	// ���ƻ���ƽ���ı���ӳ����ͼ��
	graphics.TranslateTransform(image.GetWidth(),0);
	graphics.DrawImage(&image, destination, 3);	

}


void Cubeimage_Click()
{
	int WIDTH=200;
	int LEFT=200;
	int TOP=200;

	Graphics &graphics=GetGraphics();
	//ʹ����ɫ������ɫ����
	graphics.Clear(Color::Blue);

	//���ò�ֵģʽ��������˫���β�ֵ��
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	//�ֱ�װ�������������������ͼƬ
	Bitmap face(L"rose.bmp");
	Bitmap top(L"flower.bmp");
	Bitmap right(L"yujinxiang.bmp");

	//���¶������������������ͼƬ����
	Point destinationFace[] =
	{
		Point(LEFT,TOP), 
		Point(LEFT+WIDTH, TOP),
		Point(LEFT, TOP+WIDTH)
	};  
	//��������ͼ��
	graphics.DrawImage(&face,destinationFace,3); 

	//���¶������������ڶ�����ͼƬ����	
	PointF destinationTop[]=
	{
		PointF(LEFT+WIDTH/2, TOP-WIDTH/2),
		PointF(LEFT+WIDTH/2+WIDTH, TOP-WIDTH/2), 
		PointF(LEFT, TOP)
	};  
	//����������ͼ��		
	graphics.DrawImage(&top, destinationTop, 3); 

	//���¶��������������Ҳ��ͼƬ����				
	Point destinationRight[]=
	{
		Point(LEFT+WIDTH, TOP),
		Point(LEFT+WIDTH/2+WIDTH, TOP-WIDTH/2), 
		Point(LEFT+WIDTH,TOP+WIDTH)
	};
	//�����Ҳ���ͼ��						
	graphics.DrawImage(&right, destinationRight, 3);
}

void ThumbnailImage_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//���ò�ֵģʽ��������˫���β�ֵ��
	graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);

	//�������鿴����ͼ��ͼƬ
	Bitmap image(L"flower.bmp");
	//��ȡ��ǰ���ڴ�С
	Rect client(0,0,
		MyClient.Width,MyClient.Height);

	float width=image.GetWidth();
	float height=image.GetHeight();

	//��ȡָ����С������ͼ
	Image *pThumbnail = image.GetThumbnailImage(40,40,  NULL, NULL);

	//������ͼ��Ϊ��ˢ
	TextureBrush picBrush(pThumbnail);
	//��䴰��
	graphics.FillEllipse(&picBrush,client);
}

void Clone_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap image(L"head.bmp");
	int Height=image.GetHeight();
	int Width=image.GetWidth();

	//���彫ͼƬ�зֳ��ĸ����ֵ�����
	RectF block[4]=
	{
		RectF(0,0,Width/2,Height/2),
		RectF(Width/2,0,Width/2,Height/2),
		RectF(0,Height/2,Width/2,Height/2),
		RectF(Width/2,Height/2,Width/2,Height/2)
	};

	//�ֱ��¡ͼƬ���ĸ�����	
	Bitmap *s[4];
	s[0]=image.Clone(block[0],PixelFormatDontCare);
	s[1]=image.Clone(block[1],PixelFormatDontCare);
	s[2]=image.Clone(block[2],PixelFormatDontCare);
	s[3]=image.Clone(block[3],PixelFormatDontCare);
	//����ͼƬ���ĸ����֣������ֻ���ʱ����Ϊ1��
	graphics.DrawImage(s[0],0,0);

	//��ʱ���Դﵽ�ֿ���ʾ��Ч��
	::Sleep(1000);
	graphics.DrawImage(s[1],Width/2,0);
	::Sleep(1000);
	graphics.DrawImage(s[3],Width/2,Height/2);
	::Sleep(1000);
	graphics.DrawImage(s[2],0,Height/2);
	delete s[0];
	delete s[1];
	delete s[2];
	delete s[3];
}

void Picturescale_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"photo.bmp");

	//����ͼƬ����ʾ����
	Rect rect(0,0,image.GetWidth(),image.GetHeight());
	graphics.DrawImage(&image,rect);

	//�ֲ���С�������СΪ80*80
	graphics.TranslateTransform(image.GetWidth()+10,0);
	Rect smallrect(0,0,80,80);
	//�ֲ���С
	graphics.DrawImage(&image,smallrect,80,10,106,112,UnitPixel);

	graphics.TranslateTransform(0,100);
	//�ֲ��Ŵ�������СΪ80*80
	Rect largerect(0,0,80,80);
	//���ƷŴ��ľֲ�ͼ��
	graphics.DrawImage(&image,largerect,56,101,35,40,UnitPixel);
}

void ImageAttributesSetNoOp_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap image(L"ColorTable.bmp");
	int width=image.GetWidth();
	//���Ʊ�׼ͼƬ  
	graphics.DrawImage(&image,0,0);

	graphics.TranslateTransform(image.GetWidth()+10,0);
	ImageAttributes imAtt;

	//����һ����ɫת������ɫ�ı任����   


	ColorMatrix brushMatrix=
	{
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	//����ɫ��У��
	imAtt.SetColorMatrix(
		&brushMatrix, 
		ColorMatrixFlagsDefault, 
		ColorAdjustTypeBitmap);

	//ʹ��ɫ��У������ͼƬ
	graphics.DrawImage(
		&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ��λ��
		0, 0, image.GetWidth(), image.GetHeight(),        //Դλ��
		UnitPixel,
		&imAtt);

	//��ʱ�ر�ɫ��У��
	imAtt.SetNoOp(ColorAdjustTypeBitmap);

	//��ʹ��ɫ��У������ͼƬ��ɫ->��ɫ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ��λ��
		0, 0, image.GetWidth(), image.GetHeight(),          //Դλ��
		UnitPixel,
		&imAtt);

	//������ɫ��У���Ĺر�
	imAtt.ClearNoOp(ColorAdjustTypeBitmap);

	//ʹ��ɫ��У������ͼƬ����ɫ->��ɫ
	graphics.TranslateTransform(width+10,0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ��λ��
		0, 0, image.GetWidth(), image.GetHeight(),          //Դλ��
		UnitPixel,
		&imAtt);
}


void CreateMetaFile()
{
	Graphics &metagraph=GetGraphics();

	//�½�һ��ͼԪ�ļ�
	HDC hdc =metagraph.GetHDC();
	Metafile metaFile1(CWideCharString("ddd.emf"), hdc);
	//ʹ��Metafile����ĵ�ַ��Ϊ��ͼƽ��
	Graphics *graphics=Graphics::FromImage(&metaFile1);
	graphics->ScaleTransform(0.8f,0.8f);

	//����ˮƽ�������������Բ�����
	graphics->SetSmoothingMode(SmoothingModeHighQuality);
	//��ɫ��Բ
	graphics->DrawEllipse(&Pen(Color.Red,10), Rect(0, 0, 75, 95));
	graphics->FillEllipse(&SolidBrush(Color::Red), Rect(0, 0, 75, 95));

	//��ɫ��Բ
	graphics->DrawEllipse(&Pen(Color::Green,10), Rect(40, 0, 75, 95));
	graphics->FillEllipse(&SolidBrush(Color::Green), Rect(40, 0, 75, 95));

	//��ɫ��Բ
	graphics->DrawEllipse(&Pen(Color.Blue,10), Rect(80, 0, 75, 95));
	graphics->FillEllipse(&SolidBrush(Color::Blue), Rect(80, 0, 75, 95));

	// ׷������ɫ�ʵ��ı�
	FontFamily fontFamily(CWideCharString("Arial"));
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);

	//��ɫ����
	MyDrawString(*graphics, "GDI+",font, SolidBrush(Color::Red), PointF(-80.0f, 0.0f));
	//��ɫ����
	MyDrawString(*graphics, "GDI+",font, SolidBrush(Color::Green), PointF(-80.0f, font.GetHeight(graphics)));
	//��ɫ����
	MyDrawString(*graphics, "GDI+",font, SolidBrush(Color::Blue), PointF(-80.0f, font.GetHeight(graphics)*2));
	//�ͷ�������Դ��
	//graphics->Dispose();
	//metaFile1.Dispose();
	metagraph.ReleaseHDC(hdc);
	//metagraph.Dispose();
	delete graphics;
}

void SetColorMatrices_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼԪ�ļ�	
	Metafile image(L"ddd.emf");
	Unit  unit=UnitPixel;
	//��ȡͼƬ����
	RectF rect; image.GetBounds(&rect, &unit);

	//��ʹ���κ�ɫ��У�����ͼƬ
	graphics.DrawImage(&image, 0.0f, 0.0f, rect.Width, rect.Height);
	ImageAttributes  imAtt;

	//����һ��ʹ��ɫ��������1.5�ľ���
	ColorMatrix defaultColorMatrix=
	{ 
		1.5f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  0.0f,  1.0f
	};

	//����һ��ʹ��ɫ��������1.5�ľ���
	ColorMatrix defaultGrayMatrix=
	{  
		1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  1.5f,  0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  0.0f,  1.0f
	};

	//���ʵĲ�ɫɫ����Ϣ��У��������ɫ��������1.5�ľ���
	ColorMatrix penColorMatrix= 
	{  
		1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.5f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  0.0f,  1.0f
	};

	//���ʵĻҶ�ɫ�������з�������1.5�ľ���
	ColorMatrix penGrayMatrix=
	{
		1.5f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.0f,  1.5f,  0.0f,  0.0f,  0.0f,
		0.0f,  0.0f,  1.5f,  0.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.0f,  0.0f,  0.0f,  0.0f,  1.0f
	};

	// ����Ĭ�ϵĲ�ɫ���Ҷ�У������.
	//ColorAdjustTypeDefault:�޸����е�ɫ����Ϣ
	imAtt.SetColorMatrices(
		&defaultColorMatrix,
		&defaultGrayMatrix, 
		ColorMatrixFlagsAltGray,
		ColorAdjustTypeDefault);
	//ʹ��У���������ͼԪ�ļ���У�����е�ɫ��
	graphics.TranslateTransform(image.GetWidth()+10,0);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, (int)rect.Width,(int)rect.Height),  
		rect.X, rect.Y,               
		rect.Width,                   
		rect.Height,                   
		UnitPixel,
		&imAtt);

	//���û��ʵĲ�ɫ���Ҷ�ɫ��У������
	//ColorAdjustTypePen����������ɫ��
	imAtt.SetColorMatrices(
		&penColorMatrix,
		&penGrayMatrix, 
		ColorMatrixFlagsAltGray,
		ColorAdjustTypePen); 
	//�ڵڶ��л���
	graphics.ResetTransform();
	graphics.TranslateTransform(0,image.GetHeight());
	//ʹ��������Ļ��ʻ���ͼƬ 
	graphics.DrawImage(
		&image, 
		Rect(0, 0, (int)rect.Width,(int)rect.Height),  
		rect.X, rect.Y,               
		rect.Width,                   
		rect.Height,                   
		UnitPixel,
		&imAtt);

	graphics.TranslateTransform(image.GetWidth()+10,0);
	//����ڻ����ϵ����б任
	imAtt.ClearColorMatrix(ColorAdjustTypePen);
	graphics.DrawImage(
		&image, 
		Rect(0, 0, (int)rect.Width,(int)rect.Height),  
		rect.X, rect.Y,               
		rect.Width,                   
		rect.Height,                   
		UnitPixel,
		&imAtt); 
}

void SetOutputChannelColorProfile_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap image(L"car.bmp");
	ImageAttributes imAtt;
	int width = image.GetWidth();
	int height = image.GetHeight();
	Rect rect(0, 0, width, height);
	//����ԭʼͼƬ
	graphics.DrawImage(&image, rect);

	graphics.TranslateTransform(width,0);
	//����ɫ�������ļ�
	imAtt.SetOutputChannelColorProfile(
		CWideCharString("kodak_dc.ICM"), ColorAdjustTypeBitmap);

	//ʹ��ɫ�������ļ����ͼƬ
	graphics.DrawImage(
		&image,
		rect,  
		0, 0, width, height,          
		UnitPixel,
		&imAtt);
}

void Gammaadjust_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ԭʼͼƬ
	Bitmap image(L"warrior.bmp");
	int width = image.GetWidth();
	int height = image.GetHeight();

	// ����������Ϣ
	Font myFont(L"����", 12);
	//������ʾ��Ϣ����ʾ����
	PointF origin(width+10, height+20);
	SolidBrush blackBrush(Color::Black);

	ImageAttributes imAtt;   
	CString msg;
	//��0-3���ε������ͼƬʱ��ʹ�õ�Gammaֵ
	for(float i=0.0f;i<3.0f;i+=0.1f)
	{	
		//����ԭʼͼƬ
		graphics.DrawImage(&image,0,0);

		//����Gammaֵ
		imAtt.SetGamma(i,ColorAdjustTypeBitmap);
		//ʹ���޸ĺ�Gammaֵ����ͼƬ���
		graphics.DrawImage(
			&image,
			Rect(width+10, 0, width, height),  //Ŀ������
			0, 0, width, height,           //Դ����
			UnitPixel,
			&imAtt);
		msg.Format("�����޸�Gammaֵ��Gamma=%.2f",i);
		//��ʾ��ǰ��Gammaֵ��Ϣ
		MyDrawString(graphics, msg,myFont,blackBrush,origin);
		//��ʱһ���Ա�ۿ�Ч��
		::Sleep(100);
		graphics.Clear(Color::White);
		imAtt.ClearGamma();
	}
}

void SetOutputChannel_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ͼƬ
	Bitmap image(L"jieba.bmp");
	//ͼƬ�ĸ߶�
	int width = image.GetWidth();
	int height = image.GetHeight();

	//����ԭʼͼƬ
	graphics.DrawImage(&image, RectF(0, 0, width, height));
	ImageAttributes imAtt;
	//����ɫ�����ͨ��cyan
	imAtt.SetOutputChannel(ColorChannelFlagsC,
		ColorAdjustTypeBitmap);
	//���ƣ�����ͼƬ
	graphics.TranslateTransform(width, 0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, width, height),  
		0, 0, width, height,           
		UnitPixel,
		&imAtt);

	//����ɫ�����ͨ��:magenta 
	imAtt.SetOutputChannel(ColorChannelFlagsM, 
		ColorAdjustTypeBitmap);
	//���ƣ�����ͼƬ
	graphics.TranslateTransform(width, 0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, width, height),
		0, 0, width, height,           
		UnitPixel,
		&imAtt);

	//����ɫ�����ͨ��:yellow
	imAtt.SetOutputChannel(ColorChannelFlagsY, 
		ColorAdjustTypeBitmap);
	//���ƣ�����ͼƬ
	graphics.TranslateTransform(width, 0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, width, height),
		0, 0, width, height,           
		UnitPixel,
		&imAtt);

	//����ɫ�����ͨ��:black
	imAtt.SetOutputChannel(ColorChannelFlagsK, 
		ColorAdjustTypeBitmap);
	//���ƣ�����ͼƬ
	graphics.TranslateTransform(width, 0);
	graphics.DrawImage(
		&image,
		Rect(0, 0, width, height),
		0, 0, width, height,            
		UnitPixel,
		&imAtt); 

}

void Colorkey_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//װ��ǰ�󱳾�ͼƬ
	Bitmap forground(L"grid.bmp");
	Bitmap background(L"snike.bmp");

	int width=background.GetWidth();
	int height=background.GetHeight();
	Rect rect(0,0,width,height);

	//����ɫ���óɹؼ�ɫ
	ImageAttributes imAtt;
	imAtt.SetColorKey(
		Color::Red,
		Color::Red,
		ColorAdjustTypeBitmap);

	//���Ʊ���
	graphics.DrawImage(&background,0,0); 
	//����ǰ��
	graphics.DrawImage(
		&forground, 
		rect,
		0, 0, forground.GetWidth(), forground.GetHeight(),
		UnitPixel,
		&imAtt);

	graphics.TranslateTransform(width+20,0);
	graphics.DrawImage(&background,0,0); 
	//����Ѿ�Ӧ�õĹؼ�ɫ��Ϣ
	imAtt.ClearColorKey(ColorAdjustTypeBitmap);   
	///����ɫ���óɹؼ�ɫ
	imAtt.SetColorKey(
		Color::Blue,
		Color::Blue,
		ColorAdjustTypeBitmap);
	graphics.DrawImage(&forground, 
		rect,
		0, 0, forground.GetWidth(), forground.GetHeight(),        
		UnitPixel,
		&imAtt);
	graphics.TranslateTransform(width+20,0);

	//����Դͼ
	graphics.DrawImage(&background,0,0); 
}

void Setthreshold_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap image(L"box-2.bmp");
	int Width=image.GetWidth();
	int Height=image.GetHeight();
	//����ԭʼͼƬ
	graphics.DrawImage(&image, 10, 10, Width, Height);

	//����ֵ��0��1��������
	ImageAttributes imAtt;
	for(float i=0.0f;i<1.0f;i+=0.1f)
	{
		//�������ͼƬʱʹ�õ���ֵ
		imAtt.SetThreshold(i, ColorAdjustTypeBitmap);
		//�����Ѿ�ʹ������ֵ��ͼƬ
		graphics.DrawImage(&image,
			Rect(10+Width, 10, Width, Height),  
			0, 0, Width, Height, 
			UnitPixel,
			&imAtt);
		//��ʱ
		::Sleep(1000);
	}
}

void AdjustedPalette_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.7f,0.7f);

	//����ͼƬ
	Bitmap image(L"lord-256.bmp");
	//����ͼƬ
	Bitmap image2(L"lord-256.bmp");
	//��ȡͼƬʹ�õĵ�ɫ����Ϣ
	int size=image.GetPaletteSize();
	ColorPalette *palette= (ColorPalette *)new BYTE[size];
	image.GetPalette(palette, size);

	//��ȡ��ɫ����������ɫ������
	int count=palette->Count;
	if(count<1)
	{
		AfxMessageBox("ͼƬ�޵�ɫ����Ϣ����");
		return;
	}	

	//���ĵ�ɫ���е�ÿһ��ɫ����Ϣ		
	for(int i=0;i<count;i++)
	{
		Color u(palette->Entries[i]);
		int r=u.GetR()/2;
		int g=u.GetG()/2;
		int b=u.GetB()/2;

		if(r<1)
			r=0;
		if(g<1)
			g=0;
		if(b<1)
			b=0;
		palette->Entries[i]=u.MakeARGB(255, r,g,b);
	}

	//����ͼ����µ�ɫ��
	image.SetPalette(palette);
	//����ԭͼ
	graphics.DrawImage(&image2,0,0);
	//�����޸ĺ��ͼƬ
	graphics.DrawImage(&image,image.GetWidth()+10,0);
	delete palette;
}

void SetWrapMode_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//����ͼƬ
	Bitmap image(L"yueru.bmp");
	ImageAttributes imAtt;

	//����ͼƬ���з�ʽΪWrapModeClamp��ͼƬ������ƽ��
	imAtt.SetWrapMode(WrapModeClamp,Color::Red);

	//��С��ʾԴͼ
	graphics.DrawImage(&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ������
		0, 0, 2*image.GetWidth(), 2*image.GetHeight(),      //ԴͼƬ����
		UnitPixel,
		&imAtt);

	graphics.TranslateTransform(image.GetWidth()+10,0);
	//����ͼƬ���з�ʽΪWrapModeTileFlipXY��ͼƬ��ˮƽ�ʹ�ֱ������ͬʱ��ת
	imAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.DrawImage(&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ������
		0, 0, 2*image.GetWidth(), 2*image.GetHeight(),       //ԴͼƬ����
		UnitPixel,
		&imAtt);

	graphics.TranslateTransform(image.GetWidth()+10,0);
	//����ͼƬ���з�ʽΪWrapModeTileFlipX��ͼƬ��ˮƽ�Ϸ�ת
	imAtt.SetWrapMode(WrapModeTileFlipX);
	graphics.DrawImage(&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ������
		0, 0, 2*image.GetWidth(), 2*image.GetHeight(),       //ԴͼƬ����
		UnitPixel,
		&imAtt);

	graphics.TranslateTransform(image.GetWidth()+10,0);
	//����ͼƬ���з�ʽΪWrapModeTileFlipY��ͼƬ�ڴ�ֱ�Ϸ�ת
	imAtt.SetWrapMode(WrapModeTileFlipY);
	graphics.DrawImage(&image,
		Rect(0, 0, image.GetWidth(), image.GetHeight()),  //Ŀ������
		0, 0, 2*image.GetWidth(), 2*image.GetHeight(),       //ԴͼƬ����
		UnitPixel,
		&imAtt);
}

void ListAllImageEncoders_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"���Ŀ���");
	Font        myFont(&fontFamily, 20, FontStyleRegular, UnitPixel);

	//��ȡ��������Ϣ
	UINT num, size;
	GetImageEncodersSize(&num, &size);
	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo*)new BYTE[size];
	GetImageEncoders(num, size, pImageCodecInfo);

	//���������Ϣ
	CString msg;
	for(UINT j = 0; j <num; ++j)
	{ 
		CString s;
		s.Format("����������:%s\t�ļ���ʽ��չ��:%s\t\n", 
			CString(pImageCodecInfo[j].CodecName),
			CString(pImageCodecInfo[j].FilenameExtension));
		msg+=s;
	}
	MyDrawString(graphics, msg,myFont,brush, PointF(0,0));
	delete pImageCodecInfo;
}

//��������
CString MyStringFromGUID2(const GUID &rguid)
{
	WCHAR strGuid[39];
	StringFromGUID2(rguid, strGuid, 39);
	return CString(strGuid);
}

void ListImageEncoder_Detail_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//��ȡ��������Ϣ
	UINT num, size;
	GetImageEncodersSize(&num, &size);
	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo*) new BYTE[size];
	GetImageEncoders(num, size, pImageCodecInfo);
	//����ָ����ʽ�ļ��ı�������Ϣ
	CString msg;
	//��ѯ���еı�������Ϣ
	for(UINT j = 0; j <num; j++)
	{
		CString s;
		s.Format("��ʼ������%d��ͼ�α�����Ϣ\n\n",j); msg+=s;
		s.Format("�����ʶ: %s\n",MyStringFromGUID2(pImageCodecInfo[j].Clsid));  msg+=s;
		s.Format("�ļ���ʽ��ʶ: %s\n", MyStringFromGUID2(pImageCodecInfo[j].FormatID)); msg+=s;
		s.Format("����������: %s\n", CString(pImageCodecInfo[j].CodecName)); msg+=s;
		s.Format("����������Ķ�̬���ӿ���: %s\n",CString(pImageCodecInfo[j].DllName)); msg+=s;
		s.Format("��������: %s\n", CString(pImageCodecInfo[j].FormatDescription)); msg+=s;
		s.Format("��������Ӧ���ļ���չ��: %s\n",CString(pImageCodecInfo[j].FilenameExtension)); msg+=s;
		s.Format("��������MIME��������: %s\n",CString(pImageCodecInfo[j].MimeType)); msg+=s;
		s.Format("ImageCodecFlagsö�ٵı�Ǽ�: %d\n",pImageCodecInfo[j].Flags); msg+=s;
		s.Format("�������汾: %d\n",pImageCodecInfo[j].Version); msg+=s;

		int sigCount = pImageCodecInfo[j].SigCount;
		s.Format("���������Ӧ�ı�����ǩ���������С:%d\n", sigCount); msg+=s;
		s.Format("��%d��ͼ�α�����Ϣ�������\n\n",j); msg+=s;
		AfxMessageBox(msg);
		msg.Empty();
	}
	delete pImageCodecInfo;

	//������������ϸ��Ϣд���ļ�
	//StreamWriter sw= StreamWriter(@"listinfo.txt",false,System.Text.Encoding.Unicode);
	//sw.Write(msg);
	//sw.Close();
	//AfxMessageBox("������������򿪵�ǰĿ¼�µ�listinfo.txt�鿴��������Ϣ");
}

void ListImageDecoder_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"���Ŀ���");
	Font        myFont(&fontFamily, 20, FontStyleRegular, UnitPixel);

	//��ȡ��������Ϣ
	UINT num, size;
	GetImageDecodersSize(&num, &size);
	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo*) new BYTE[size];
	GetImageDecoders(num, size, pImageCodecInfo);

	//���ÿһ������������ϸ��Ϣ
	CString msg;
	for(UINT j = 0; j <num; j++)
	{
		CString s;
		s.Format("����������:%s\t�ļ���ʽ��չ��:%s\t\n", 
			CString(pImageCodecInfo[j].CodecName),CString(pImageCodecInfo[j].FilenameExtension));
		msg+=s;
	}
	delete pImageCodecInfo;
	//��ʾ��Ϣ
	MyDrawString(graphics, msg,myFont,brush, PointF(0,0));
}

GUID GetEncoderClsid(CString format)
{
	GUID picGUID;
	//��ȡ��������Ϣ
	UINT num=0, size=0;
	GetImageEncodersSize(&num, &size);
	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo*) new BYTE[size];
	GetImageEncoders(num, size, pImageCodecInfo);
	//����ָ����ʽ�ļ��ı�������Ϣ
	CWideCharString formatW(format);
	for(UINT i = 0; i <num; i++)
	{	//MimeType�����뷽ʽ�ľ�������
		if(formatW == CWideCharString(pImageCodecInfo[i].MimeType))
		{
			picGUID= pImageCodecInfo[i].Clsid;
			break;
		}
	}
	delete pImageCodecInfo;
	return picGUID;
}

void GetEncoderParameter_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"����");
	Font        myFont(&fontFamily, 16, FontStyleRegular, UnitPixel);

	CString msg;
	// Ϊ�˲�ѯ��λͼ����ΪJPEG��ʽ��ͼƬ���½�һ��λͼ
	Bitmap bitmap(1,1);

	//��ȡJPEG��ʽ��ͼ��������ı�ʶ
	GUID encoderClsid;
	encoderClsid=GetEncoderClsid(L"image/jpeg");

	// ��ȡת����JPG����Ҫ�ľ��������Ϣ
	UINT size=bitmap.GetEncoderParameterListSize(&encoderClsid);
	EncoderParameters *pEncoderParameters= (EncoderParameters *)new BYTE[size];
	bitmap.GetEncoderParameterList(&encoderClsid, size, pEncoderParameters);
	// �鿴pEncoderParameters�����ж��ٸ�EncoderParameter��
	int count=pEncoderParameters->Count;
	msg.Format("�ڱ��������������%d��EncoderParameter��\nÿ�������ϸ��ϢΪ��\n", count);
											
	EncoderParameter *pEncoderParameter=pEncoderParameters->Parameter;
	/*�ֱ�鿴EncoderParameters�����е�
	ÿһ��EncoderParameter����ĳ�Ա����
	GUID��NumberOfValues��Type*/
	for(int i=0;i<count;i++)
	{
		CString s;
		//��GUIDֵת�����ִ� 
		s.Format("�������õĵ�%d����������(GUID):%s\n", i, MyStringFromGUID2(pEncoderParameter[i].Guid));
		msg+=s;
		//�鿴��ÿһ�����������£��������õĲ�����Ϣ
		s.Format("\t�ڸò������������£�����Խ��е����õĲ����ֱ�����\n");
		msg+=s;
		s.Format("\t\t��������=%d\n", pEncoderParameter[i].NumberOfValues);
		msg+=s;
		s.Format("\t\t��������=%d\n", pEncoderParameter[i].Type);
		msg+=s;
	}
	//�����������б���Ϣ
	MyDrawString(graphics, msg,myFont,brush, PointF(0,0));
	delete pEncoderParameters;
}

HRESULT EncoderParameterCategoryFromGUID(GUID guid, WCHAR* category, UINT maxChars);
CString _EncoderParameterCategoryFromGUID(GUID guid)
{
   CONST MAX_CATEGORY_LENGTH = 50;
   WCHAR strParameterCategory[MAX_CATEGORY_LENGTH] = L"";
   if (Ok==EncoderParameterCategoryFromGUID(guid, strParameterCategory, MAX_CATEGORY_LENGTH))
	   return CString(strParameterCategory);
   return _T("ʧ��");
}

CString ShowAllEncoderParameters(CString format)
{
	CString outmsg;		
	
	//��λͼΪ�����鿴pImageCodecInfo����ϸ��Ϣ	
	Bitmap bitmap(L"head.bmp");

	GUID encoderClsid=GetEncoderClsid(format);
	UINT size=bitmap.GetEncoderParameterListSize(&encoderClsid);
	if (0==size)
	{
		return _T("����");
	}
	EncoderParameters *encodersarameters= (EncoderParameters *)new BYTE[size];
	bitmap.GetEncoderParameterList(&encoderClsid, size, encodersarameters);

	// ��ȡ��������Ĳ����б�
	//��ȡEncoderParameter��������
	int count=encodersarameters->Count;
	outmsg.Format("��EncoderParameters�У���%d�� EncoderParameter����\n", 
		count);
	EncoderParameter *pEncoderParameter=encodersarameters->Parameter;

	// �鿴ÿһ��EncoderParameter������Ϣ
	for(int k = 0; k <count;++k)
	{
		//��ԭGUID��Ϣ
		CString strParameterCategory=_EncoderParameterCategoryFromGUID(
			pEncoderParameter[k].Guid);
		CString s;
		s.Format("\t��������: %s.\n", strParameterCategory); outmsg+=s;
		s.Format("\t�ò���������ֵһ���� %d��\n",
			pEncoderParameter[k].NumberOfValues); outmsg+=s;
		s.Format("\t��������%d.\n", pEncoderParameter[k].Type); outmsg+=s;
	} 
	delete encodersarameters;
	//��������Ϣ����outmsg
	return outmsg;
}

void GetAllEncoderParameter_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//���������Ϣʱʹ�õ����塢��ˢ
	SolidBrush brush(Color::Blue);
	FontFamily  fontFamily(L"����");
	Font  myFont(&fontFamily, 16, FontStyleRegular,UnitPixel);

	//�������б���ϸ��Ϣ���浽msg֮��
	CString msg=ShowAllEncoderParameters(L"image/jpeg");
	//��ʾ�����б���Ϣ
	MyDrawString(graphics, msg, myFont, SolidBrush(Color::Black), PointF(0,0));
}

void menuItem17_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap image(L"snike.bmp");
	RectF rect(0,0,image.GetWidth()/2,image.GetHeight()/2);
	graphics.DrawImage(&image,rect);

	//��BMP����ΪPNG�ļ�,��ʹ�ñ������
	GUID pngGuid = GetEncoderClsid("image/png");
	MyImageSave(image, L"snike.png", &pngGuid, NULL);

	//ʹ�õڶ��ַ�������encoder����
	MyImageSave(image,L"snike2.png", &pngGuid);
		
	//�ֱ�����ַ��������ͼ��
	Bitmap image_png1(L"snike.png");
	Bitmap image_png2(L"snike2.png");

	//����PNG��ʽ��ͼƬ
	graphics.TranslateTransform(rect.Width,0);
	graphics.DrawImage(&image_png1,rect);
	graphics.TranslateTransform(rect.Width,0);
	graphics.DrawImage(&image_png2,rect);
}

void SaveBmp2tif_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	Bitmap myBitmap(L"jieba.bmp");

	// ��ȡTIFF��ʽ�ļ��ı�����Ϣ
	GUID tiffGuid = GetEncoderClsid("image/tiff");

	EncoderParameters params;	//�����Ѿ�������һ�� EncoderParameter
	params.Count=1;
	// ʹ��LZWѹ����ʽ��ͼͼ��Ϊ TIFF�ļ�
	params.Parameter[0].Guid= EncoderCompression;
	params.Parameter[0].NumberOfValues=1;
	params.Parameter[0].Type=EncoderParameterValueTypeLong;
	params.Parameter[0].Value=new long[1];

	((long*)params.Parameter[0].Value)[0] = (long)EncoderValueCompressionLZW;

	MyImageSave(myBitmap,L"jieba.tif", &tiffGuid, &params);

	delete params.Parameter[0].Value;
}

void SaveBMP2JPG_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//��BMP�ļ�
	Bitmap myBitmap(L"car.bmp");
	//��ȡ��ʾͼƬ����Ҫ����
	Rect imgrect(0,0, myBitmap.GetWidth(),myBitmap.GetHeight());

	graphics.DrawImage(&myBitmap, imgrect);

	//��ȡJPEG��ʽ�ı��뷽ʽ
	GUID jpegGuid= GetEncoderClsid("image/jpeg");

	//�ֱ�����JPEG�ļ���ͼƬ����
	//�����������Ϊ Quality,
	EncoderParameters params;	//�����Ѿ�������һ�� EncoderParameter
	params.Count=1;
	params.Parameter[0].Guid= EncoderQuality;
	params.Parameter[0].NumberOfValues=1;
	params.Parameter[0].Type=EncoderParameterValueTypeLong;
	params.Parameter[0].Value=new long[1];

	//����JPEGͼƬ����Ϊ25��
	((long*)params.Parameter[0].Value)[0] = 25L;
	MyImageSave(myBitmap,L"car025.jpg", &jpegGuid, &params);

	//����JPEGͼƬ����Ϊ50��
	((long*)params.Parameter[0].Value)[0] = 50L;
	MyImageSave(myBitmap,L"car050.jpg", &jpegGuid, &params);

	//����JPEGͼƬ����Ϊ75��
	((long*)params.Parameter[0].Value)[0] = 75L;
	MyImageSave(myBitmap,L"car075.jpg", &jpegGuid, &params);

	delete params.Parameter[0].Value;

	//�ֱ���ʾ��ͬͼƬ������JPEG�ļ�
	Bitmap image01(L"car025.jpg");
	//��ͼƽ������
	graphics.TranslateTransform(imgrect.Width+10,0);
	graphics.DrawImage(&image01,imgrect);

	Bitmap image02(L"car050.jpg");
	//���û�ͼƽ�棬����
	graphics.ResetTransform();

	graphics.TranslateTransform(0,imgrect.Height+10);
	graphics.DrawImage(&image02,imgrect);

	Bitmap image05(L"car075.jpg");
	graphics.TranslateTransform(imgrect.Width+10,0);
	graphics.DrawImage(&image02,imgrect);
}

void TransformingJPEG_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	
	//��JPEG�ļ�
	Bitmap myBitmap(L"car.jpg");
	//��ȡ��ʾͼƬ����Ҫ����
	Rect imgrect(0,0, myBitmap.GetWidth(), myBitmap.GetHeight());
	//����ԭͼ
	graphics.DrawImage(&myBitmap,imgrect);

	//��ȡJPEG��ʽ�ı��뷽ʽ
	GUID jpegGuid= GetEncoderClsid("image/jpeg");

	//�ֱ�����JPEG�ļ���λ�ñ任��Ϣ
	//�����������Ϊ Transformation
	EncoderParameters params;	//�����Ѿ�������һ�� EncoderParameter
	params.Count=1;
	params.Parameter[0].Guid= EncoderTransformation;
	params.Parameter[0].NumberOfValues=1;
	params.Parameter[0].Type=EncoderParameterValueTypeLong;
	params.Parameter[0].Value=new long[1];

	((long*)params.Parameter[0].Value)[0] = (long)EncoderValueTransformRotate270;

	// ��ͼƬ��ת90�Ⱥ󱣴�
	MyImageSave(myBitmap,L"car0_rotate.jpg", &jpegGuid, &params);

	delete params.Parameter[0].Value;

	//������ת���ͼƬ
	graphics.TranslateTransform(imgrect.Width,0);
	Bitmap myBitmap2(L"car0_rotate.jpg");
	//��ȡ��ʾͼƬ����Ҫ����
	Rect imgrect2(0,0, myBitmap2.GetWidth(), myBitmap2.GetHeight());
	graphics.DrawImage(&myBitmap2, imgrect2);
}
void MultipleFrameImage_Click()
{
	//װ�����Ų�ͬ��ʽ��ͼƬ
	Bitmap multi(L"dog.bmp");
	Bitmap page2(L"dog.gif");
	Bitmap page3(L"cute.jpg");
	Bitmap page4(L"cat.png");
	
	//��ȡtiffͼ���ʽ�ı�����Ϣ
	GUID tiffGuid = GetEncoderClsid("image/tiff");
	
	EncoderParameters params;	//�����Ѿ�������һ�� EncoderParameter
	params.Count=1;
	//�������ͣ�SaveFlag
	params.Parameter[0].Guid= EncoderSaveFlag;
	params.Parameter[0].NumberOfValues=1;
	params.Parameter[0].Type=EncoderParameterValueTypeLong;
	params.Parameter[0].Value=new long[1];

	((long*)params.Parameter[0].Value)[0] = (long)EncoderValueMultiFrame;
	
	//�����һ��ͼƬ
	MyImageSave(multi,L"Multiframe.tiff", &tiffGuid, &params);
	
	//����ڶ���ͼƬ
	((long*)params.Parameter[0].Value)[0] = (long)EncoderValueFrameDimensionPage;
	multi.SaveAdd(&page2, &params);
	
	//���������ͼƬ
	multi.SaveAdd(&page3, &params);
	
	//���������ͼƬ
	multi.SaveAdd(&page4, &params);

	// �ر�TIFF�ļ�
	((long*)params.Parameter[0].Value)[0] = (long)EncoderValueFlush;
	multi.SaveAdd(&params);

	delete params.Parameter[0].Value;

	AfxMessageBox("������������򿪵�ǰĿ¼�µ�Multiframe.tiff�鿴ͼƬ��ӽ��");
}

void GetImageFromMultyFrame_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	//�������зֳ��ĸ����֣�������ʾ�ķ�֡ͼƬ
	Rect ClientRect(0,0,
		MyClient.Width,MyClient.Height);
	Rect r1(0,0,
		ClientRect.Width/2,ClientRect.Height/2);
	Rect r2(ClientRect.Width/2,0,
		ClientRect.Width/2,ClientRect.Height/2);
	Rect r3(0,
		ClientRect.Height/2,ClientRect.Width/2,ClientRect.Height/2);
	Rect r4(ClientRect.Width/2,
		ClientRect.Height/2,ClientRect.Width/2,ClientRect.Height/2);

	//��TIF�ļ�
	Bitmap  multi(L"Multiframe.tiff");

	//FrameDimension.Page:��֡ͼƬ
	GUID pageGuid = FrameDimensionPage;

	GUID pngGuid = GetEncoderClsid("image/png");

	//��ʾ�������һ֡ͼƬ
	multi.SelectActiveFrame(&pageGuid, 0);
	graphics.DrawImage(&multi, r1);
	MyImageSave(multi,L"Page0.png", &pngGuid);

	//��ʾ������ڶ�֡ͼƬ
	multi.SelectActiveFrame(&pageGuid, 1);
	graphics.DrawImage(&multi,r2);
	MyImageSave(multi,L"Page1.png",&pngGuid);

	////��ʾ���������֡ͼƬ
	multi.SelectActiveFrame(&pageGuid, 2);
	graphics.DrawImage(&multi, r3);
	MyImageSave(multi,L"Page2.png",&pngGuid);

	////��ʾ���������֡ͼƬ
	multi.SelectActiveFrame(&pageGuid, 3);
	graphics.DrawImage(&multi, r4);
	MyImageSave(multi,L"Page3.png",&pngGuid);
}

void QueryImage_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);

	SolidBrush brush(Color::Black);
	FontFamily  fontFamily(L"����");
	Font        myFont(&fontFamily, 16, FontStyleRegular, UnitPixel);

	Bitmap image(L"car.jpg");
	//��ȡͼ���������
	UINT size, count=0;
	image.GetPropertySize(&size, &count);
	PropertyItem *propItem= (PropertyItem *)new BYTE[size];
	image.GetAllPropertyItems(size, count, propItem);

	// ͼ���й��ж����������ɹ���ѯ
	if(count == 0)
	{
		AfxMessageBox("���������ɹ���ѯ");
		return;
	}

	CString tmp;
	for(UINT j = 0; j < count; ++j)
	{
		CString s;
		s.Format("�� %d ���ɹ�����ѯ���������ı��ֵΪ��16���ƣ���%x\n",
			j,propItem[j].id); tmp+=s;
		s.Format("�� %d ����������Ӧ�����������ϢΪ��\n",j); tmp+=s;

		//��ȡ��������ϸ������Ϣ
		s.Format("\t������ĳ���Ϊ%d\n\t��������Ϊ%d\n",
			propItem[j].length, propItem[j].type); tmp+=s;
	}

	delete propItem;

	//���ͼ���������Ϣ
	MyDrawString(graphics, tmp, myFont, brush, PointF(0,0));
}

void SetProp_Click()
{
	//װ��ͼƬ�Թ��޸�
	Bitmap image(L"car.jpg");

	// ����ͼƬ������ΪJasmine
	BYTE newWriterValue[] = {(BYTE)'J', (BYTE)'a', (BYTE)'s', (BYTE)'m', (BYTE)'i', (BYTE)'e', 0};

	//��ȡͼ���������
	UINT size, count=0;
	image.GetPropertySize(&size, &count);
	PropertyItem *pp= (PropertyItem *)new BYTE[size];
	image.GetAllPropertyItems(size, count, pp);

	//0x13b���ñ��ֵ��ӦͼƬ����
	pp[0].id=0x13b;
	//����ֵ����
	pp[0].length=strlen((const char*)newWriterValue);
	//2������ֵ����������Ϊ�ַ���
	pp[0].type=2;
	pp[0].value=newWriterValue;

	//����ͼƬ����
	image.SetPropertyItem(pp+0);
	GUID jpegGuid= GetEncoderClsid("image/jpeg");
	MyImageSave(image,L"newwriter.jpg", &jpegGuid);

	delete pp;

	//���¼����޸ĺ��ͼƬ
	Bitmap image2(L"newwriter.jpg");
	//�鿴ͼƬ��������Ϣ
	size = image2.GetPropertyItemSize(0x13b);
	pp= (PropertyItem *)new BYTE[size];
	image2.GetPropertyItem(0x13b, size, pp);
	CString msg;
	msg.Format("ͼƬ�������Ѿ�����Ϊ\n\n%s",CString((BYTE*)pp->value));
	AfxMessageBox(msg);

	delete pp;
}

void OnCanvas_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.7f,0.7f);

	Bitmap image(L"box-2.bmp");

	int Width = image.GetWidth();
	int Height = image.GetHeight();
	Color color;
	graphics.DrawImage(&image,
		Rect(0, 0, Width, Height));
	
	//�������������
	for(int i=0;i<Width-5;i++)
	{
		for( int j=0; j<Height-5;j++)
		{
			int a=rand_Next(1000)%5;
			
			image.GetPixel(i+a, j+a, &color);
			//���õ��RGBֵ���óɸ������֮�ڵ���һ��
			image.SetPixel(i, j, color);
		}
		//��̬�����˾�Ч��ͼ
		graphics.DrawImage(&image,
			Rect(Width, 0, Width, Height));
	}
}

void OnWood_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.7f,0.7f);

	Bitmap image(L"box-2.bmp");

	int Width = image.GetWidth();
	int Height = image.GetHeight();
	Color colorTemp,color2;
	Color color;
	//����ԭͼ
	graphics.DrawImage(&image, Rect(0, 0, Width, Height));
	int tmp;
	for(int i=0;i<Width;i++)
	{
		for( int j=0; j<Height;j++)
		{
			image.GetPixel(i, j, &color);
			//���ݸõ�RGB��ƽ��ֵ��ȷ�ϸõ�ġ�������
			int avg;
			avg=(color.GetRed()+color.GetGreen()+color.GetBlue())/3;
			if(avg>=128)
				tmp=255;
			else
				tmp=0;
			colorTemp = Color(255,tmp,tmp,tmp);
			//��������RGBֵ��д��λͼ
			image.SetPixel(i, j, colorTemp);
		}
		//��̬�����˾�Ч��ͼ
		graphics.DrawImage(&image, Rect(Width, 0, Width, Height));
	}

}
//��������A��B֮��ľ��Ծ���
float fDistance(Point A,Point B)
{
	double i=((A.X-B.X)*(A.X-B.X))+((A.Y-B.Y)*(A.Y-B.Y));
	return (float)sqrt(i);
}

void Flashligt_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	
	Bitmap image(L"sports.bmp");
	int Width = image.GetWidth();
	int Height = image.GetHeight();
	int A=Width/2;
	int B=Height/2;
	//Center:ͼƬ���ĵ㣬������ֵ����ǿ�����ķ���ƫ��
	Point Center= Point(A,B);
	//R��ǿ��������İ뾶���������Ρ�
	int R=100;
	Color colorTemp,color2;
	Color color;
	graphics.DrawImage(&image, Rect(0, 0, Width, Height));
	//���η���ÿ������
	for(int x=0;x<Width;x++)
	{
		for( int y=0; y<Height;y++)
		{
			Point tmp= Point(x,y);
			//�������λ�ڡ����Ρ�֮��
			if(fDistance(tmp,Center)<R)
			{
				image.GetPixel(x, y, &color);
				int r,g,b;
				//���ݸõ����ǿ�����ĵ�ľ��룬�ֱ���RGBֵ����
				//220:�������ӳ�������ֵԽ�󣬹�����Խǿ
				float tmp_r=220.0f*(1.0f-fDistance(tmp,Center)/R);
				
				r=color.GetRed()+(int)tmp_r;
				r=max(0,min(r,255));
				
				g=color.GetGreen()+(int)tmp_r;
				g=max(0,min(g,255));

				b=color.GetBlue()+(int)tmp_r;
				b=max(0,min(b,255));
		
				colorTemp = Color(255,(int)r,(int)g,(int)b);
				//�������������ֵ��д��λͼ
				image.SetPixel(x, y, colorTemp);
			}
		}
		//��̬�����˾�Ч��ͼ
		graphics.DrawImage(&image, Rect(Width, 0, Width, Height));
	}
}

void BlurAndSharpen_Click()
{
	Graphics &graphics=GetGraphics();
	graphics.Clear(Color::White);
	graphics.ScaleTransform(0.8f,0.8f);

	Bitmap image(L"snike.bmp");

	int Width = image.GetWidth();
	int Height = image.GetHeight();
	//image2:�����񻯴���
	Bitmap *image2=image.Clone(0,0,Width,Height,PixelFormatDontCare);

	Color colorTemp;
	Color color[3][3];
	//����ԭͼ
	graphics.DrawImage(&image, Rect(0, 0, Width, Height));

	for(int i=1;i<Width-2;i++)
	{
		for( int j=1; j<Height-2;j++)
		{
			//������Χ9�����RGBֵ
			image.GetPixel(i-1, j-1, &color[0][0]);
			image.GetPixel(i-1, j, &color[0][1]);
			image.GetPixel(i-1, j+1, &color[0][2]);

			image.GetPixel(i, j-1, &color[1][0]);
			image.GetPixel(i, j, &color[1][1]);
			image.GetPixel(i, j+1, &color[1][2]);

			image.GetPixel(i+1, j-1, &color[2][0]);
			image.GetPixel(i+1, j, &color[2][1]);
			image.GetPixel(i+1, j+1, &color[2][2]);

			int rSum=0;
			int gSum=0;
			int bSum=0;
			//�ֱ������Χ9�����R��G��B֮��
			for(int n=0;n<3;n++)
				for(int nn=0;nn<3;nn++)
				{
					rSum+=color[n][nn].GetR();	
					gSum+=color[n][nn].GetG();	
					bSum+=color[n][nn].GetB();	
				}
			//��RGB��ƽ��ֵ��Ϊ��ǰ���RGBֵ
			colorTemp = Color(255,(int)(rSum/9),(int)(gSum/9),(int)(bSum/9));
			//��������RGBֵ��д��λͼ
			image.SetPixel(i, j,colorTemp);
		}
		//���ƾ���ƽ�������Ч��ͼ
		graphics.DrawImage(&image, Rect(Width, 0, Width, Height));
	}

	//�����񻯴���
	Color colorLeft,colornow;
	//����dep����ϵ������ֵԽ����Ч��Խ����
	float dep=0.550f;
	for(i=1;i<Width-1; i++)
	{
		for( int j=1;j<Height-1; j++)
		{
			image2->GetPixel(i, j, &colornow);	
			image2->GetPixel(i-1, j-1, &colorLeft);	

			float r=colornow.GetR()+(colornow.GetR()
				-colorLeft.GetR()*dep);
			r=min(255,max(0,r));

			float g=colornow.GetG()+(colornow.GetG() -colorLeft.GetG()*dep);
			g=min(255,max(0,g));
			float b=colornow.GetB()+(colornow.GetB()-colorLeft.GetB()*dep);
			b=min(255,max(0,b));

			colorTemp = Color(255,(int)r,(int)g,(int)b);

			//��������RGBֵ��д��λͼ
			image2->SetPixel(i, j, colorTemp);
		}

		graphics.DrawImage(image2, Rect(Width*2, 0, Width, Height));
	}
	delete image2;
}


void ShowAllEncoderParameters(ImageCodecInfo*, CString &msg);
HRESULT EncoderParameterCategoryFromGUID(GUID guid, WCHAR* category, UINT maxChars);
HRESULT ValueTypeFromULONG(ULONG index, WCHAR* strValueType, UINT maxChars);

void ShowAllEncoder()
{
   UINT  num;        // Number of image encoders
   UINT  size;       // Size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo;

   // How many encoders are there?
   // How big (in bytes) is the array of all ImageCodecInfo obects?
   GetImageEncodersSize(&num, &size);

   // Create a buffer large enough to hold the array of ImageCodecInfo
   // objects that will be returned by GetImageEncoders.
   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));

   // GetImageEncoders creates an array of ImageCodecInfo objects
   // and copies that array into a previously allocated buffer. 
   // The third argument, imageCodecInfos, is a pointer to that buffer. 
   GetImageEncoders(num, size, pImageCodecInfo);
	
   // For each ImageCodecInfo object in the array, show all parameters.
   for(UINT j = 0; j < num; ++j)
   {
		CString msg;
		ShowAllEncoderParameters(&(pImageCodecInfo[j]), msg);
		AfxMessageBox(msg);
   }

   free(pImageCodecInfo);
}


VOID ShowAllEncoderParameters(ImageCodecInfo* pImageCodecInfo, CString &msg)
{
   CONST MAX_CATEGORY_LENGTH = 50;
   CONST MAX_VALUE_TYPE_LENGTH = 50;
   WCHAR strParameterCategory[MAX_CATEGORY_LENGTH] = L"";
   WCHAR strValueType[MAX_VALUE_TYPE_LENGTH] = L"";

	CString s(pImageCodecInfo->MimeType);
	s+="\n";
	msg+=s;

   // Create a Bitmap (inherited from Image) object so that we can call
   // GetParameterListSize and GetParameterList.
   Bitmap bitmap(1, 1);

   // How big (in bytes) is the encoder's parameter list?
   UINT listSize = 0; 
   listSize = bitmap.GetEncoderParameterListSize(&pImageCodecInfo->Clsid);
   s.Format("  The parameter list requires %d bytes.\n", listSize);
	msg+=s;

   if(listSize == 0)
      return;

   // Allocate a buffer large enough to hold the parameter list.
   EncoderParameters* pEncoderParameters = NULL;
   pEncoderParameters = (EncoderParameters*)malloc(listSize);

   if(pEncoderParameters == NULL)
      return;

   // Get the parameter list for the encoder.
   bitmap.GetEncoderParameterList(
      &pImageCodecInfo->Clsid, listSize, pEncoderParameters);

   // pEncoderParameters points to an EncoderParameters object, which
   // has a Count member and an array of EncoderParameter objects.
   // How many EncoderParameter objects are in the array?
   s.Format("  There are %d EncoderParameter objects in the array.\n", 
      pEncoderParameters->Count);
	msg+=s;

   // For each EncoderParameter object in the array, list the
   // parameter category, data type, and number of values.
   for(UINT k = 0; k < pEncoderParameters->Count; ++k)
   {
      EncoderParameterCategoryFromGUID(
         pEncoderParameters->Parameter[k].Guid, strParameterCategory, MAX_CATEGORY_LENGTH);

      ValueTypeFromULONG(
         pEncoderParameters->Parameter[k].Type, strValueType, MAX_VALUE_TYPE_LENGTH);

      s.Format("    Parameter[%d]\n", k); msg+=s;
      s.Format("      The category is %s.\n", CString(strParameterCategory)); msg+=s;
      s.Format("      The data type is %s.\n", strValueType); msg+=s;

      s.Format("      The number of values is %d.\n",
      pEncoderParameters->Parameter[k].NumberOfValues); msg+=s;
   } // for

   free(pEncoderParameters);
} // ShowAllEncoderParameters


HRESULT MyStringCchCopy(LPWSTR pszDest, size_t cchDest, LPCWSTR pszSrc)
{
	return wcsncpy(pszDest, pszSrc, cchDest)? Ok: E_FAIL;
}

HRESULT EncoderParameterCategoryFromGUID(GUID guid, WCHAR* category, UINT maxChars)
{
   HRESULT hr = E_FAIL;

   if(guid == EncoderCompression)
      hr = MyStringCchCopy(category, maxChars, L"Compression");
   else if(guid == EncoderColorDepth)
      hr = MyStringCchCopy(category, maxChars, L"ColorDepth");
   else if(guid == EncoderScanMethod)
      hr = MyStringCchCopy(category, maxChars, L"ScanMethod");
   else if(guid == EncoderVersion)
      hr = MyStringCchCopy(category, maxChars, L"Version");
   else if(guid == EncoderRenderMethod)
      hr = MyStringCchCopy(category, maxChars, L"RenderMethod");
   else if(guid == EncoderQuality)
      hr = MyStringCchCopy(category, maxChars, L"Quality");
   else if(guid == EncoderTransformation)
      hr = MyStringCchCopy(category, maxChars, L"Transformation");
   else if(guid == EncoderLuminanceTable)
      hr = MyStringCchCopy(category, maxChars, L"LuminanceTable");
   else if(guid == EncoderChrominanceTable)
      hr = MyStringCchCopy(category, maxChars, L"ChrominanceTable");
   else if(guid == EncoderSaveFlag)
      hr = MyStringCchCopy(category, maxChars, L"SaveFlag");
   else
      hr = MyStringCchCopy(category, maxChars, L"Unknown category");

   return hr;
} // EncoderParameterCategoryFromGUID


HRESULT ValueTypeFromULONG(ULONG index, WCHAR* strValueType, UINT maxChars)
{
   HRESULT hr = E_FAIL;

   WCHAR* valueTypes[] = {
      L"Nothing",                  // 0
      L"ValueTypeByte",            // 1
      L"ValueTypeASCII",           // 2
      L"ValueTypeShort",           // 3
      L"ValueTypeLong",            // 4
      L"ValueTypeRational",        // 5
      L"ValueTypeLongRange",       // 6
      L"ValueTypeUndefined",       // 7
      L"ValueTypeRationalRange"};  // 8

   hr = MyStringCchCopy(strValueType, maxChars, valueTypes[index]);
   return hr;

} // ValueTypeFromULONG

