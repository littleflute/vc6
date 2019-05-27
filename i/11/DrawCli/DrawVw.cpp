//Download by http://www.NewXing.com
// DrawVw.cpp : implementation of the CDrawView class
//

#include "stdafx.h"
#include <afxpriv.h>
#include "DrawCli.h"

#include "DrawDoc.h"
#include "CntrItem.h"
#include "DrawVw.h"
#include "resource.h"

#include "DrawObj.h"
#include "drawtool.h"
#include "CntrItem.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// private clipboard format (list of Draw objects)
CLIPFORMAT CDrawView::m_cfDraw = (CLIPFORMAT)
#ifdef _MAC
	::RegisterClipboardFormat(_T("DCLI"));
#else
	::RegisterClipboardFormat(_T("MFC Draw Sample"));
#endif
CLIPFORMAT CDrawView::m_cfObjectDescriptor = NULL;

/////////////////////////////////////////////////////////////////////////////
// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawView, CScrollView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CDrawView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_DRAW_SELECT, OnDrawSelect)
	ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, OnUpdateDrawRect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
	ON_COMMAND(ID_DRAW_ELLIPSE, OnDrawEllipse)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_ROUNDRECT, OnDrawRoundrect)
	ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
	ON_COMMAND(ID_OBJECT_MOVEBACK, OnObjectMoveback)
	ON_COMMAND(ID_OBJECT_MOVEFORWARD, OnObjectMoveforward)
	ON_COMMAND(ID_OBJECT_MOVETOBACK, OnObjectMovetoback)
	ON_COMMAND(ID_OBJECT_MOVETOFRONT, OnObjectMovetofront)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVEBACK, OnUpdateObjectMoveback)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVEFORWARD, OnUpdateObjectMoveforward)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVETOBACK, OnUpdateObjectMovetoback)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVETOFRONT, OnUpdateObjectMovetofront)
	ON_COMMAND(ID_OBJECT_FILLCOLOR, OnObjectFillcolor)
	ON_COMMAND(ID_OBJECT_LINECOLOR, OnObjectLinecolor)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_FILLCOLOR, OnUpdateObjectFillcolor)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_LINECOLOR, OnUpdateObjectLinecolor)
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_VIEW_SHOWOBJECTS, OnViewShowobjects)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOWOBJECTS, OnUpdateViewShowobjects)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateEditClear)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView construction/destruction

CDrawView::CDrawView()
{
//	m_pSelection = NULL;

	m_bGrid = TRUE;
	m_gridColor = RGB(0, 0, 128);
	m_bActive = FALSE;
}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView drawing

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDC dc;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(client);
	CRect rect = client;
	DocToClient(rect);

	if (!pDC->IsPrinting())
	{
		// draw to offscreen bitmap for fast looking repaints
		if (dc.CreateCompatibleDC(pDC))
		{
			if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				OnPrepareDC(&dc, NULL);
				pDrawDC = &dc;

				// offset origin more because bitmap is just piece of the whole drawing
				dc.OffsetViewportOrg(-rect.left, -rect.top);
				pOldBitmap = dc.SelectObject(&bitmap);
				dc.SetBrushOrg(rect.left % 8, rect.top % 8);

				// might as well clip to the same rectangle
				dc.IntersectClipRect(client);
			}
		}
	}

	// paint background
	CBrush brush;
	if (!brush.CreateSolidBrush(pDoc->GetPaperColor()))
		return;

	brush.UnrealizeObject();
	pDrawDC->FillRect(client, &brush);

	if (!pDC->IsPrinting() && m_bGrid)
		DrawGrid(pDrawDC);

	pDoc->Draw(pDrawDC, this);

	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
			&dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
}

void CDrawView::OnInitialUpdate()
{
//	CScrollView::OnInitialUpdate();

  	CSize size = GetDocument()->GetSize();
	CClientDC dc(NULL);
	size.cx = MulDiv(size.cx, dc.GetDeviceCaps(LOGPIXELSX), 100);
	size.cy = MulDiv(size.cy, dc.GetDeviceCaps(LOGPIXELSY), 100);
	SetScrollSizes(MM_TEXT, size);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDrawView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CScrollView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CDrawView::IsSelected(const CObject* pDocItem) const
{
/*
	// The implementation below is adequate if your selection consists of
	//  only CDrawItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.
	// TODO: implement this function that tests for a selected OLE client item
	return pDocItem == m_pSelection;
*/
	CDrawObj* pDrawObj = (CDrawObj*)pDocItem;
	if (pDocItem->IsKindOf(RUNTIME_CLASS(CDrawItem)))
		pDrawObj = ((CDrawItem*)pDocItem)->m_pDrawObj;
	return m_selection.Find(pDrawObj) != NULL;

}

void CDrawView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CDrawItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	// First create the C++ object
	CDrawOleObj* pObj = new CDrawOleObj(GetInitialPosition());
	ASSERT_VALID(pObj);
	CDrawItem* pItem = new CDrawItem(GetDocument(), pObj);
	ASSERT_VALID(pItem);
	pObj->m_pClientItem = pItem;

	// Now create the OLE object/item
	TRY
	{
		if (!dlg.CreateItem(pObj->m_pClientItem))
			AfxThrowMemoryException();

		// add the object to the document
		GetDocument()->Add(pObj);

		// try to get initial presentation data
		pItem->UpdateLink();
		pItem->UpdateExtent();

		// if insert new object -- initially show the object
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);
	}
	CATCH_ALL(e)
	{
		// clean up item
		pItem->Delete();
		pObj->m_pClientItem = NULL;
		GetDocument()->Remove(pObj);
		pObj->Remove();

		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH_ALL

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CDrawView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CDrawView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CScrollView::OnSetFocus(pOldWnd);
}

void CDrawView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawView message handlers

void CDrawView::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(ID_POPUP_MENU));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CDrawView::InvalObj(CDrawObj *pObj)
{
	CRect rect = pObj->m_position;
	DocToClient(rect);
	if (m_bActive && IsSelected(pObj))
	{
		rect.left -= 4;
		rect.top -= 5;
		rect.right += 5;
		rect.bottom += 4;
	}
	rect.InflateRect(1, 1); // handles CDrawOleObj objects

	InvalidateRect(rect, FALSE);
}

void CDrawView::ClientToDoc(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

void CDrawView::ClientToDoc(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.bottom <= rect.top);
}

void CDrawView::DocToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}

void CDrawView::DocToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
}
void CDrawView::Remove(CDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
		m_selection.RemoveAt(pos);
}
void CDrawView::Select(CDrawObj* pObj,BOOL bAdd)
{
	if (!bAdd)
	{
		OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
		m_selection.RemoveAll();
	}

	if (pObj == NULL || IsSelected(pObj))
		return;

	m_selection.AddTail(pObj);
	InvalObj(pObj);

}
void CDrawView::CloneSelection()
{
	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->Clone(pObj->m_pDocument);
			// copies object and adds it to the document
	}
}
void CDrawView::Deselect(CDrawObj* pObj)
{
	POSITION pos = m_selection.Find(pObj);
	if (pos != NULL)
	{
		InvalObj(pObj);
		m_selection.RemoveAt(pos);
	}
}

void CDrawView::SelectWithinRect(CRect rect,BOOL bAdd)
{
	if (!bAdd)
		Select(NULL);

	ClientToDoc(rect);

	CDrawObjList* pObList = GetDocument()->GetObjects();
	POSITION posObj = pObList->GetHeadPosition();
	while (posObj != NULL)
	{
		CDrawObj* pObj = pObList->GetNext(posObj);
		if (pObj->Intersects(rect))
			Select(pObj, TRUE);
	}

}

void CDrawView::OnDrawSelect() 
{
	CDrawTool::c_drawShape = selection;
}

void CDrawView::OnDrawRect() 
{
	CDrawTool::c_drawShape = rect;
}

void CDrawView::OnUpdateDrawSelect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == selection);
}

void CDrawView::OnUpdateDrawRect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(CDrawTool::c_drawShape == rect);
}

void CDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonDown(this, nFlags, point);
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonUp(this, nFlags, point);
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnMouseMove(this, nFlags, point);

//  m_wndStatusBar.SetPaneText(1,LPCTSTR("abcdefgh"),TRUE);
}

void CDrawView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (!m_bActive)
		return;
	CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
	if (pTool != NULL)
		pTool->OnLButtonDblClk(this, nFlags, point);
}
void CDrawView::DrawGrid(CDC* pDC)
{
   	CDrawDoc* pDoc = GetDocument();

	COLORREF oldBkColor = pDC->SetBkColor(pDoc->GetPaperColor());

	CRect rect;
	rect.left = -pDoc->GetSize().cx / 2;
	rect.top = -pDoc->GetSize().cy / 2;
	rect.right = rect.left + pDoc->GetSize().cx;
	rect.bottom = rect.top + pDoc->GetSize().cy;

	// Center lines
	CPen penDash;
	penDash.CreatePen(PS_DASH, 1, m_gridColor);
	CPen* pOldPen = pDC->SelectObject(&penDash);

	pDC->TextOut(410,280,"xdtest: v0.0.1");

	pDC->MoveTo(0, rect.top);
	pDC->LineTo(0, rect.bottom);
	pDC->MoveTo(rect.left, 0);
	pDC->LineTo(rect.right, 0);

	// Major unit lines
	CPen penDot;
	penDot.CreatePen(PS_DOT, 1, m_gridColor);
	pDC->SelectObject(&penDot);

	//for (int x = rect.left / 100 * 100; x < rect.right; x += 100)
	for (int x = rect.left / 50 * 50; x < rect.right; x += 50)
	{
		if (x != 0)
		{
			pDC->MoveTo(x, rect.top);
			pDC->LineTo(x, rect.bottom);
		}
	}

	//for (int y = rect.top / 100 * 100; y < rect.bottom; y += 100)
	for (int y = rect.top / 50 * 50; y < rect.bottom; y += 50)
	{
		if (y != 0)
		{
			pDC->MoveTo(rect.left, y);
			pDC->LineTo(rect.right, y);
		}
	}

	// Outlines
	CPen penSolid;
	penSolid.CreatePen(PS_SOLID, 1, m_gridColor);
	pDC->SelectObject(&penSolid);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);

	pDC->SelectObject(pOldPen);
	pDC->SetBkColor(oldBkColor);

}
void CDrawView::SetPageSize(CSize size)
{
   	CClientDC dc(NULL);
	size.cx = MulDiv(size.cx, dc.GetDeviceCaps(LOGPIXELSX), 100);
	size.cy = MulDiv(size.cy, dc.GetDeviceCaps(LOGPIXELSY), 100);
	SetScrollSizes(MM_TEXT, size);
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_WINDOW, NULL);

}


void CDrawView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
 	CScrollView::OnPrepareDC(pDC, pInfo);
	// mapping mode is MM_ANISOTROPIC
	// these extents setup a mode similar to MM_LOENGLISH
	// MM_LOENGLISH is in .01 physical inches
	// these extents provide .01 logical inches
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
		pDC->GetDeviceCaps(LOGPIXELSY));
	pDC->SetWindowExt(100, -100);

	// set the origin of the coordinate system to the center of the page
	CPoint ptOrg;
	ptOrg.x = GetDocument()->GetSize().cx / 2;
	ptOrg.y = GetDocument()->GetSize().cy / 2;

	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(-ptOrg.x,ptOrg.y);
}

CRect CDrawView::GetInitialPosition()
{
	CRect rect(10, 10, 10, 10);
	ClientToDoc(rect);
	return rect;
}

//用来显示所画图形
void CDrawView::OnActivateView(BOOL bActivate,CView* pActiveView,CView* pDeactiveView)
{
	CView::OnActivateView(bActivate, pActiveView, pDeactiveView);

	// invalidate selections when active status changes
	if (m_bActive != bActivate)
	{
		if (bActivate)  // if becoming active update as if active
			m_bActive = bActivate;
		if (!m_selection.IsEmpty())
			OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
		m_bActive = bActivate;
	}
}

void CDrawView::OnDrawCircle() 
{
	CDrawTool::c_drawShape = circle;	
}

void CDrawView::OnDrawEllipse() 
{
	CDrawTool::c_drawShape = ellipse;
}

void CDrawView::OnDrawLine() 
{
	CDrawTool::c_drawShape = XDDS_line;
	
}

void CDrawView::OnDrawRoundrect() 
{
	CDrawTool::c_drawShape = roundRect;
}

void CDrawView::OnEditProperties() 
{
	if (m_selection.GetCount() == 1 && CDrawTool::c_drawShape == selection)
	{
		CDrawTool* pTool = CDrawTool::FindTool(CDrawTool::c_drawShape);
		ASSERT(pTool != NULL);
		pTool->OnEditProperties(this);
	}
}

void CDrawView::OnObjectMoveback() 
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	if (pos != pObjects->GetHeadPosition())
	{
		POSITION posPrev = pos;
		pObjects->GetPrev(posPrev);
		pObjects->RemoveAt(pos);
		pObjects->InsertBefore(posPrev, pObj);
		InvalObj(pObj);
	}
	
}

void CDrawView::OnObjectMoveforward() 
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	if (pos != pObjects->GetTailPosition())
	{
		POSITION posNext = pos;
		pObjects->GetNext(posNext);
		pObjects->RemoveAt(pos);
		pObjects->InsertAfter(posNext, pObj);
		InvalObj(pObj);
	}
	
}

void CDrawView::OnObjectMovetoback() 
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	pObjects->RemoveAt(pos);
	pObjects->AddHead(pObj);
	InvalObj(pObj);
	
}

void CDrawView::OnObjectMovetofront() 
{
	CDrawDoc* pDoc = GetDocument();
	CDrawObj* pObj = m_selection.GetHead();
	CDrawObjList* pObjects = pDoc->GetObjects();
	POSITION pos = pObjects->Find(pObj);
	ASSERT(pos != NULL);
	pObjects->RemoveAt(pos);
	pObjects->AddTail(pObj);
	InvalObj(pObj);
	
}

void CDrawView::OnUpdateObjectMoveback(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnUpdateObjectMoveforward(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnUpdateObjectMovetoback(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnUpdateObjectMovetofront(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnObjectFillcolor() 
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	COLORREF color = dlg.GetColor();

	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->SetFillColor(color);
	}
	
}

void CDrawView::OnObjectLinecolor() 
{
	CColorDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	COLORREF color = dlg.GetColor();

	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		pObj->SetLineColor(color);
	}	
}

void CDrawView::OnUpdateObjectFillcolor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnUpdateObjectLinecolor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_selection.GetCount() == 1);
	
}

void CDrawView::OnViewGrid() 
{
	m_bGrid = !m_bGrid;
	Invalidate(FALSE);
	
}

void CDrawView::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bGrid);
	
}

void CDrawView::OnViewShowobjects() 
{
	CDrawOleObj::c_bShowItems = !CDrawOleObj::c_bShowItems;
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_OLE_ITEMS, NULL);
	
}

void CDrawView::OnUpdateViewShowobjects(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(CDrawOleObj::c_bShowItems);
	
}

void CDrawView::OnEditClear() 
{
	GetDocument()->UpdateAllViews(NULL, HINT_DELETE_SELECTION, &m_selection);
	OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);

	// now remove the selection from the document
	POSITION pos = m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = m_selection.GetNext(pos);
		GetDocument()->Remove(pObj);
		pObj->Remove();
	}
	m_selection.RemoveAll();
	
}

void CDrawView::OnEditCopy() 
{
	ASSERT_VALID(this);
	ASSERT(m_cfDraw != NULL);

	// Create a shared file and associate a CArchive with it
	CSharedFile file;
	CArchive ar(&file, CArchive::store);

	// Serialize selected objects to the archive
	m_selection.Serialize(ar);
	ar.Close();

	COleDataSource* pDataSource = NULL;
	TRY
	{
		pDataSource = new COleDataSource;
		// put on local format instead of or in addation to
		pDataSource->CacheGlobalData(m_cfDraw, file.Detach());

		// if only one item and it is a COleClientItem then also
		// paste in that format
		CDrawObj* pDrawObj = m_selection.GetHead();
		if (m_selection.GetCount() == 1 &&
			pDrawObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
		{
			CDrawOleObj* pDrawOle = (CDrawOleObj*)pDrawObj;
			pDrawOle->m_pClientItem->GetClipboardData(pDataSource, FALSE);
		}
		pDataSource->SetClipboard();
	}
	CATCH_ALL(e)
	{
		delete pDataSource;
		THROW_LAST();
	}
	END_CATCH_ALL
	
}

void CDrawView::OnEditCut() 
{
	OnEditCopy();
	OnEditClear();
	
}

void CDrawView::OnEditPaste() 
{
	COleDataObject dataObject;
	dataObject.AttachClipboard();

	// invalidate current selection since it will be deselected
	OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
	m_selection.RemoveAll();
	if (dataObject.IsDataAvailable(m_cfDraw))
	{
		PasteNative(dataObject);

		// now add all items in m_selection to document
		POSITION pos = m_selection.GetHeadPosition();
		while (pos != NULL)
			GetDocument()->Add(m_selection.GetNext(pos));
	}
	else
		PasteEmbedded(dataObject, GetInitialPosition().TopLeft() );

	GetDocument()->SetModifiedFlag();

	// invalidate new pasted stuff
	GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_SELECTION, &m_selection);
	
}

void CDrawView::OnEditSelectAll() 
{
	CDrawObjList* pObList = GetDocument()->GetObjects();
	POSITION pos = pObList->GetHeadPosition();
	while (pos != NULL)
		Select(pObList->GetNext(pos), TRUE);
	
}
void CDrawView::PasteNative(COleDataObject& dataObject)
{
	// get file refering to clipboard data
	CFile* pFile = dataObject.GetFileData(m_cfDraw);
	if (pFile == NULL)
		return;

	// connect the file to the archive
	CArchive ar(pFile, CArchive::load);
	TRY
	{
		ar.m_pDocument = GetDocument(); // set back-pointer in archive

		// read the selection
		m_selection.Serialize(ar);
	}
	CATCH_ALL(e)
	{
		ar.Close();
		delete pFile;
		THROW_LAST();
	}
	END_CATCH_ALL

	ar.Close();
	delete pFile;
}

void CDrawView::PasteEmbedded(COleDataObject& dataObject, CPoint point)
{
	BeginWaitCursor();

	// paste embedded
	CDrawOleObj* pObj = new CDrawOleObj(GetInitialPosition());
	ASSERT_VALID(pObj);
	CDrawItem* pItem = new CDrawItem(GetDocument(), pObj);
	ASSERT_VALID(pItem);
	pObj->m_pClientItem = pItem;

	TRY
	{
		if (!pItem->CreateFromData(&dataObject) &&
			!pItem->CreateStaticFromData(&dataObject))
		{
			AfxThrowMemoryException();      // any exception will do
		}

		// add the object to the document
		GetDocument()->Add(pObj);
		m_selection.AddTail(pObj);
		ClientToDoc( point );
		pObj->MoveTo( CRect( point, pObj->m_extent ), this );

		// try to get initial presentation data
		pItem->UpdateLink();
		pItem->UpdateExtent();
	}
	CATCH_ALL(e)
	{
		// clean up item
		pItem->Delete();
		pObj->m_pClientItem = NULL;
		GetDocument()->Remove(pObj);
		pObj->Remove();

		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH_ALL

	EndWaitCursor();
}

void CDrawView::OnUpdateEditClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_selection.IsEmpty());
	
}

void CDrawView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_selection.IsEmpty());
	
}

void CDrawView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_selection.IsEmpty());
	
}

void CDrawView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// determine if private or standard OLE formats are on the clipboard
	COleDataObject dataObject;
	BOOL bEnable = dataObject.AttachClipboard() &&
		(dataObject.IsDataAvailable(m_cfDraw) ||
		 COleClientItem::CanCreateFromData(&dataObject));

	// enable command based on availability
	pCmdUI->Enable(bEnable);
}

void CDrawView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetObjects()->GetCount() != 0);
	
}
void CDrawView::OnUpdate(CView* , LPARAM lHint, CObject* pHint)
{

	switch (lHint)
	{
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;

	case HINT_UPDATE_DRAWOBJ:   // a single object has changed
		InvalObj((CDrawObj*)pHint);
		break;

	case HINT_UPDATE_SELECTION: // an entire selection has changed
		{
			CDrawObjList* pList = pHint != NULL ?
				(CDrawObjList*)pHint : &m_selection;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
				InvalObj(pList->GetNext(pos));
		}
		break;

	case HINT_DELETE_SELECTION: // an entire selection has been removed
		if (pHint != &m_selection)
		{
			CDrawObjList* pList = (CDrawObjList*)pHint;
			POSITION pos = pList->GetHeadPosition();
			while (pos != NULL)
			{
				CDrawObj* pObj = pList->GetNext(pos);
				InvalObj(pObj);
				Remove(pObj);   // remove it from this view's selection
			}
		}
		break;

	case HINT_UPDATE_OLE_ITEMS:
		{
			CDrawDoc* pDoc = GetDocument();
			POSITION pos = pDoc->GetObjects()->GetHeadPosition();
			while (pos != NULL)
			{
				CDrawObj* pObj = pDoc->GetObjects()->GetNext(pos);
				if (pObj->IsKindOf(RUNTIME_CLASS(CDrawOleObj)))
					InvalObj(pObj);
			}
		}
		break;

	default:
		ASSERT(FALSE);
		break;
	}

}
