//Download by http://www.NewXing.com
// WalkLtDemoView.cpp : implementation of the CWalkLtDemoView class
//

#include "stdafx.h"
#include "WalkLtDemo.h"

#include "WalkLtDemoDoc.h"
#include "WalkLtDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView

IMPLEMENT_DYNCREATE(CWalkLtDemoView, CView)

BEGIN_MESSAGE_MAP(CWalkLtDemoView, CView)
	//{{AFX_MSG_MAP(CWalkLtDemoView)
	ON_COMMAND(ID_GDIPLUS_DEMO, OnGdiplusDemo)
	ON_COMMAND(ID_GDIPLUS_CODE, OnGdiplusCode)
	ON_UPDATE_COMMAND_UI(ID_GDIPLUS_CODE, OnUpdateGdiplusCode)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView construction/destruction

CWalkLtDemoView::CWalkLtDemoView()
{
	// TODO: add construction code here

}

CWalkLtDemoView::~CWalkLtDemoView()
{
}

BOOL CWalkLtDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView drawing

typedef GdiPlusColor Color;

int g_index1=0;
int g_index2=0;

BOOL g_OnDraw=0;

void CWalkLtDemoView::OnDraw(CDC* pDC)
{
	CWalkLtDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (g_OnDraw)
		return;

	g_OnDraw=1;

	//绘制一个红色椭圆
	Graphics gc(pDC->m_hDC);
	Pen pen(Color::Red, 2);
	gc.DrawArc(&pen, 10, 10, 300, 200, 0, 360);

	//支持 WalkLtDemo设计实例.cpp 中的函数调用
	//----------- 调用 DoGdiplusDemo ---------
	extern void DoGdiplusDemo(Graphics &gc, CView *pView, int index1, int index2);
	if (g_index1>0 && g_index2>0)
		DoGdiplusDemo(gc, this, g_index1, g_index2);

	g_OnDraw=0;
}

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView printing

BOOL CWalkLtDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWalkLtDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWalkLtDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView diagnostics

#ifdef _DEBUG
void CWalkLtDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CWalkLtDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWalkLtDemoDoc* CWalkLtDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWalkLtDemoDoc)));
	return (CWalkLtDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoView message handlers
#include "GdiplusDemoDlg.h"

void CWalkLtDemoView::OnGdiplusDemo() 
{
	CGdiplusDemoDlg dlg;
	if (IDOK==dlg.DoModal())
	{
		g_index1=dlg.m_index1;
		g_index2=dlg.m_index2;
		Invalidate();
	}
}

#include "MyCodeDlg.h"
void CWalkLtDemoView::OnGdiplusCode() 
{
	//获取函数的源代码
	CString GetGdiplusFunsCode(int index1, int index2);
	CMyCodeDlg dlg;
	dlg.m_str = GetGdiplusFunsCode(g_index1, g_index2);
	dlg.DoModal();
}

void CWalkLtDemoView::OnUpdateGdiplusCode(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_index1>0&&g_index2>0);
}
