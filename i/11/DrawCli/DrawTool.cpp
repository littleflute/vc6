//Download by http://www.NewXing.com
// DrawTool.cpp: implementation of the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawCli.h"
#include "DrawTool.h"
 
#include "drawdoc.h"
#include "drawvw.h"
#include "drawobj.h"
 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDrawTool implementation

CPtrList CDrawTool::c_tools;

static CSelectTool selectTool;
static CRectTool lineTool(line);
static CRectTool rectTool(rect);
static CRectTool roundRectTool(roundRect);
static CRectTool ellipseTool(ellipse);
static CRectTool circleTool(circle);
//static CPolyTool polyTool;

CPoint CDrawTool::c_down;
UINT CDrawTool::c_nDownFlags;
CPoint CDrawTool::c_last;
DrawShape CDrawTool::c_drawShape = selection;

CDrawTool::CDrawTool(DrawShape drawShape)
{
	m_drawShape = drawShape;
	c_tools.AddTail(this);
}

CDrawTool* CDrawTool::FindTool(DrawShape drawShape)
{
	POSITION pos = c_tools.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawTool* pTool = (CDrawTool*)c_tools.GetNext(pos);
		if (pTool->m_drawShape == drawShape)
			return pTool;
	}

	return NULL;
}

void CDrawTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	// deactivate any in-place active item on this view!
	COleClientItem* pActiveItem = pView->GetDocument()->GetInPlaceActiveItem(pView);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
		ASSERT(pView->GetDocument()->GetInPlaceActiveItem(pView) == NULL);
	}

	pView->SetCapture();
	c_nDownFlags = nFlags;
	c_down = point;
	c_last = point;
}

void CDrawTool::OnLButtonDblClk(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& /*point*/)
{
}

void CDrawTool::OnLButtonUp(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& point)
{
	ReleaseCapture();

	if (point == c_down)
		c_drawShape = selection;
}

void CDrawTool::OnMouseMove(CDrawView* /*pView*/, UINT /*nFlags*/, const CPoint& point)
{
	c_last = point;
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
}

void CDrawTool::OnEditProperties(CDrawView* /*pView*/)
{
}

void CDrawTool::OnCancel()
{
	c_drawShape = selection;
}

////////////////////////////////////////////////////////////////////////////
// CResizeTool

enum SelectMode
{
	none,
	netSelect,
	move,
	size
};

SelectMode selectMode = none;
int nDragHandle;

CPoint lastPoint;

CSelectTool::CSelectTool()
	: CDrawTool(selection)
{
}

void CSelectTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	
	CPoint local = point;
	pView->ClientToDoc(local);

	CDrawObj* pObj;
	selectMode = none;

	// Check for resizing (only allowed on single selections)
	if (pView->m_selection.GetCount() == 1)
	{
		pObj = pView->m_selection.GetHead();
		nDragHandle = pObj->HitTest(local, pView, TRUE);
		if (nDragHandle != 0)
			selectMode = size;
	}

	// See if the click was on an object, select and start move if so
	if (selectMode == none)
	{
		pObj = pView->GetDocument()->ObjectAt(local);

		if (pObj != NULL)
		{
			selectMode = move;

			if (!pView->IsSelected(pObj))
				pView->Select(pObj, (nFlags & MK_SHIFT) != 0);

			// Ctrl+Click clones the selection...
#ifndef _MAC			
			if ((nFlags & MK_CONTROL) != 0)
#else
			if ((nFlags & MK_OPTION) != 0)
#endif			
				pView->CloneSelection();
		}
	}
 
	// Click on background, start a net-selection
	if (selectMode == none)
	{
		if ((nFlags & MK_SHIFT) == 0)
			pView->Select(NULL);

		selectMode = netSelect;

		CClientDC dc(pView);
		CRect rect(point.x, point.y, point.x, point.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
	}

	lastPoint = local;
	CDrawTool::OnLButtonDown(pView, nFlags, point);
  
}

void CSelectTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	
	if ((nFlags & MK_SHIFT) != 0)
	{
		// Shift+DblClk deselects object...
		CPoint local = point;
		pView->ClientToDoc(local);
		CDrawObj* pObj = pView->GetDocument()->ObjectAt(local);
		if (pObj != NULL)
			pView->Deselect(pObj);
	}
	else
	{
		// "Normal" DblClk opens properties, or OLE server...
		if (pView->m_selection.GetCount() == 1)
			pView->m_selection.GetHead()->OnOpen(pView);
	}

	CDrawTool::OnLButtonDblClk(pView, nFlags, point);

}

void CSelectTool::OnEditProperties(CDrawView* pView)
{
	if (pView->m_selection.GetCount() == 1)
		pView->m_selection.GetHead()->OnEditProperties();
}

void CSelectTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	
	if (pView->GetCapture() == pView)
	{
		if (selectMode == netSelect)
		{
			CClientDC dc(pView);
			CRect rect(c_down.x, c_down.y, c_last.x, c_last.y);
			rect.NormalizeRect();
			dc.DrawFocusRect(rect);

			pView->SelectWithinRect(rect, TRUE);
		}
		else if (selectMode != none)
		{
			pView->GetDocument()->UpdateAllViews(pView);
		}
	}

	CDrawTool::OnLButtonUp(pView, nFlags, point);
	
}

void CSelectTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	if (pView->GetCapture() != pView)
	{
		if (c_drawShape == selection && pView->m_selection.GetCount() == 1)
		{
			CDrawObj* pObj = pView->m_selection.GetHead();
			CPoint local = point;
			pView->ClientToDoc(local);
			int nHandle = pObj->HitTest(local, pView, TRUE);
			if (nHandle != 0)
			{
				SetCursor(pObj->GetHandleCursor(nHandle));
				return; // bypass CDrawTool
			}
		}
		if (c_drawShape == selection)
			CDrawTool::OnMouseMove(pView, nFlags, point);
		return;
	}

	if (selectMode == netSelect)
	{
		CClientDC dc(pView);
		CRect rect(c_down.x, c_down.y, c_last.x, c_last.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);
		rect.SetRect(c_down.x, c_down.y, point.x, point.y);
		rect.NormalizeRect();
		dc.DrawFocusRect(rect);

		CDrawTool::OnMouseMove(pView, nFlags, point);
		return;
	}

	CPoint local = point;
	pView->ClientToDoc(local);
	CPoint delta = (CPoint)(local - lastPoint);

	POSITION pos = pView->m_selection.GetHeadPosition();
	while (pos != NULL)
	{
		CDrawObj* pObj = pView->m_selection.GetNext(pos);
		CRect position = pObj->m_position;

		if (selectMode == move)
		{
			position += delta;
			pObj->MoveTo(position, pView);
		}
		else if (nDragHandle != 0)
		{
			pObj->MoveHandleTo(nDragHandle, local, pView);
		}
	}

	lastPoint = local;

	if (selectMode == size && c_drawShape == selection)
	{
		c_last = point;
		SetCursor(pView->m_selection.GetHead()->GetHandleCursor(nDragHandle));
		return; // bypass CDrawTool
	}

	c_last = point;

	if (c_drawShape == selection)
		CDrawTool::OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CRectTool (does rectangles, round-rectangles, and ellipses)

CRectTool::CRectTool(DrawShape drawShape)
	: CDrawTool(drawShape)
{
}

void CRectTool::OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	
	CDrawTool::OnLButtonDown(pView, nFlags, point);

	CPoint local = point;
	pView->ClientToDoc(local);

	CDrawRect* pObj = new CDrawRect(CRect(local, CSize(0, 0)));
	switch (m_drawShape)
	{
	default:
		ASSERT(FALSE); // unsuported shape!

	case rect:
		pObj->m_nShape = CDrawRect::rectangle;
		break;

	case roundRect:
		pObj->m_nShape = CDrawRect::roundRectangle;
		break;

	case ellipse:
		pObj->m_nShape = CDrawRect::ellipse;
		break;

	case line:
		pObj->m_nShape = CDrawRect::line;
		break;
	case circle:
		pObj->m_nShape = CDrawRect::circle;
		break;
	}
	pView->GetDocument()->Add(pObj);
	pView->Select(pObj);

	selectMode = size;
	nDragHandle = 1;
	lastPoint = local;

}

void CRectTool::OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	CDrawTool::OnLButtonDblClk(pView, nFlags, point);
}

void CRectTool::OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point)
{  
	if (point == c_down)
	{
		// Don't create empty objects...
		CDrawObj *pObj = pView->m_selection.GetTail();
		pView->GetDocument()->Remove(pObj);
		pObj->Remove();
		selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
	}

	selectTool.OnLButtonUp(pView, nFlags, point);
}

void CRectTool::OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point)
{
	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	selectTool.OnMouseMove(pView, nFlags, point);
}
