//Download by http://www.NewXing.com
// DrawObj.cpp: implementation of the CDrawObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawCli.h"
#include "DrawObj.h"

#include "drawdoc.h"
#include "drawvw.h"
#include "cntritem.h"
#include "rectdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDrawObj, CObject, 0)

CDrawObj::CDrawObj()
{
}

CDrawObj::~CDrawObj()
{
}

CDrawObj::CDrawObj(const CRect& position)
{
	m_XDRecPosition = position;
	m_pDocument = NULL;

	m_bPen = TRUE;
	m_logpen.lopnStyle = PS_INSIDEFRAME;
	m_logpen.lopnWidth.x = 2;
	m_logpen.lopnWidth.y = 2;
	m_logpen.lopnColor = RGB(0, 0, 0);

	m_bBrush = TRUE;
	m_logbrush.lbStyle = BS_SOLID;
	m_logbrush.lbColor = RGB(192, 192, 192);
	m_logbrush.lbHatch = HS_HORIZONTAL;
}

void CDrawObj::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_XDRecPosition;
		ar << (WORD)m_bPen;
		ar.Write(&m_logpen, sizeof(LOGPEN));
		ar << (WORD)m_bBrush;
		ar.Write(&m_logbrush, sizeof(LOGBRUSH));
	}
	else
	{
		// get the document back pointer from the archive
		m_pDocument = (CDrawDoc*)ar.m_pDocument;
		ASSERT_VALID(m_pDocument);
		ASSERT_KINDOF(CDrawDoc, m_pDocument);

		WORD wTemp;
		ar >> m_XDRecPosition;
		ar >> wTemp; m_bPen = (BOOL)wTemp;
		ar.Read(&m_logpen,sizeof(LOGPEN));
		ar >> wTemp; m_bBrush = (BOOL)wTemp;
		ar.Read(&m_logbrush, sizeof(LOGBRUSH));
	}
}

void CDrawObj::Remove()
{
	delete this;
}

void CDrawObj::Draw(CDC*)
{
}

void CDrawObj::DrawTracker(CDC* pDC, TrackerState state)
{
	ASSERT_VALID(this);

	switch (state)
	{
	case normal:
		break;

	case selected:
	case active:
		{
			int nHandleCount = GetHandleCount();
			for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
			{
				CPoint handle = GetHandle(nHandle);
				pDC->PatBlt(handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);
			}
		}
		break;
	}
}

// position is in logical
void CDrawObj::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);
	CRect & m_position = this->m_XDRecPosition;
 
	if (position == m_position)
		return;

	if (pView == NULL)
	{
		Invalidate();
		m_position = position;
		Invalidate();
	}
	else
	{
		pView->InvalObj(this);
		m_position = position;
		pView->InvalObj(this);
	}
	m_pDocument->SetModifiedFlag();
}

// Note: if bSelected, hit-codes start at one for the top-left
// and increment clockwise, 0 means no hit.
// If !bSelected, 0 = no hit, 1 = hit (anywhere)

// point is in logical coordinates
int CDrawObj::HitTest(CPoint point, CDrawView* pView, BOOL bSelected)
{
	ASSERT_VALID(this);
	ASSERT(pView != NULL);
	CRect &m_position= m_XDRecPosition;

	if (bSelected)
	{
		int nHandleCount = GetHandleCount();
		for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
		{
			// GetHandleRect returns in logical coords
			CRect rc = GetHandleRect(nHandle,pView);
			if (point.x >= rc.left && point.x < rc.right &&
				point.y <= rc.top && point.y > rc.bottom)
				return nHandle;
		}
	}
	else
	{
		if (point.x >= m_position.left && point.x < m_position.right &&
			point.y <= m_position.top && point.y > m_position.bottom)
			return 1;
	}
	return 0;
}

// rect must be in logical coordinates
BOOL CDrawObj::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);
	CRect &m_position= m_XDRecPosition;

	CRect fixed = m_position;
	fixed.NormalizeRect();
	CRect rectT = rect;
	rectT.NormalizeRect();
	return !(rectT & fixed).IsRectEmpty();
}

int CDrawObj::GetHandleCount()
{
	ASSERT_VALID(this);
	return 8;
}

// returns logical coords of center of handle
CPoint CDrawObj::GetHandle(int nHandle)
{
	ASSERT_VALID(this);
	int x, y, xCenter, yCenter;

	CRect &m_position= m_XDRecPosition;

	// this gets the center regardless of left/right and top/bottom ordering
	xCenter = m_position.left + m_position.Width() / 2;
	yCenter = m_position.top + m_position.Height() / 2;

	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
		x = m_position.left;
		y = m_position.top;
		break;

	case 2:
		x = xCenter;
		y = m_position.top;
		break;

	case 3:
		x = m_position.right;
		y = m_position.top;
		break;

	case 4:
		x = m_position.right;
		y = yCenter;
		break;

	case 5:
		x = m_position.right;
		y = m_position.bottom;
		break;

	case 6:
		x = xCenter;
		y = m_position.bottom;
		break;

	case 7:
		x = m_position.left;
		y = m_position.bottom;
		break;

	case 8:
		x = m_position.left;
		y = yCenter;
		break;
	}

	return CPoint(x, y);
}

// return rectange of handle in logical coords
CRect CDrawObj::GetHandleRect(int nHandleID, CDrawView* pView)
{
	ASSERT_VALID(this);
	ASSERT(pView != NULL);

	CRect rect;
	// get the center of the handle in logical coords
	CPoint point = GetHandle(nHandleID);
	// convert to client/device coords
	pView->DocToClient(point);
	// return CRect of handle in device coords
	rect.SetRect(point.x-3, point.y-3, point.x+3, point.y+3);
	pView->ClientToDoc(rect);

	return rect;
}

HCURSOR CDrawObj::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	LPCTSTR id;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
	case 5:
		id = IDC_SIZENWSE;
		break;

	case 2:
	case 6:
		id = IDC_SIZENS;
		break;

	case 3:
	case 7:
		id = IDC_SIZENESW;
		break;

	case 4:
	case 8:
		id = IDC_SIZEWE;
		break;
	}

	return AfxGetApp()->LoadStandardCursor(id);
}

// point must be in logical
void CDrawObj::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);

	CRect position = this->m_XDRecPosition;
	switch (nHandle)
	{
	default:
		ASSERT(FALSE);

	case 1:
		position.left = point.x;
		position.top = point.y;
		break;

	case 2:
		position.top = point.y;
		break;

	case 3:
		position.right = point.x;
		position.top = point.y;
		break;

	case 4:
		position.right = point.x;
		break;

	case 5:
		position.right = point.x;
		position.bottom = point.y;
		break;

	case 6:
		position.bottom = point.y;
		break;

	case 7:
		position.left = point.x;
		position.bottom = point.y;
		break;

	case 8:
		position.left = point.x;
		break;
	}

	MoveTo(position, pView);
}

void CDrawObj::Invalidate()
{
	ASSERT_VALID(this);
	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
}

CDrawObj* CDrawObj::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);
 
	CDrawObj* pClone = new CDrawObj(this->m_XDRecPosition);

	pClone->m_bPen = m_bPen;
	pClone->m_logpen = m_logpen;
	pClone->m_bBrush = m_bBrush;
	pClone->m_logbrush = m_logbrush;
	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	return pClone;

}

void CDrawObj::OnEditProperties()
{
	ASSERT_VALID(this);
   
	CPropertySheet sheet( _T("对象显示属性") );
	CRectDlg dlg;
	dlg.m_bNoFill = !m_bBrush;
	dlg.m_penSize = m_bPen ? m_logpen.lopnWidth.x : 0;
	dlg.m_LineColor = m_logpen.lopnColor;	  
    dlg.m_FillColor = m_logbrush.lbColor;	  

	sheet.AddPage( &dlg );

	if (sheet.DoModal() != IDOK)
		return;


	m_bBrush = !dlg.m_bNoFill;
	m_bPen = dlg.m_penSize > 0;
	m_logbrush.lbColor = dlg.m_FillColor;   
	if (m_bPen)
	{
	    m_logpen.lopnWidth.x = dlg.m_penSize;
		m_logpen.lopnWidth.y = dlg.m_penSize;
		m_logpen.lopnColor = dlg.m_LineColor;   

 	}

	Invalidate();
	m_pDocument->SetModifiedFlag(); 
}

void CDrawObj::OnOpen(CDrawView* /*pView*/ )
{
	OnEditProperties();
}

void CDrawObj::SetLineColor(COLORREF color)
{
	ASSERT_VALID(this);

	m_logpen.lopnColor = color;
	Invalidate();
	m_pDocument->SetModifiedFlag();
}

void CDrawObj::SetFillColor(COLORREF color)
{
	ASSERT_VALID(this);

	m_logbrush.lbColor = color;
	Invalidate();
	m_pDocument->SetModifiedFlag();
}

#ifdef _DEBUG
void CDrawObj::AssertValid()
{
	ASSERT(m_XDRecPosition.left <= m_XDRecPosition.right);
	ASSERT(m_XDRecPosition.bottom <= m_XDRecPosition.top);
}
#endif

////////////////////////////////////////////////////////////////////////////
// CDrawRect

IMPLEMENT_SERIAL(CDrawRect, CDrawObj, 0)

CDrawRect::CDrawRect()
{
}

CDrawRect::CDrawRect(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);

	m_nShape = rectangle;
	m_roundness.x = 16;
	m_roundness.y = 16;
}

void CDrawRect::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << (WORD) m_nShape;
		ar << m_roundness;
	}
	else
	{
		WORD wTemp;
		ar >> wTemp; m_nShape = (Shape)wTemp;
		ar >> m_roundness;
	}
}

/**/
void CDrawRect::DrawCircle(CDC* pDC,CRect rect)
{
	ASSERT_VALID(this);

	int cx,cy;
	if (rect.right < rect.left)
		{
			cx = rect.left;
			rect.left = rect.right;
			rect.right = cx;
		}
	if (rect.bottom < rect.top)
		{
			cy = rect.top;
			rect.top = rect.bottom;
			rect.bottom = cy;
		}
	cx = rect.right - rect.left;
    cy = rect.bottom - rect.top;
	if (cx > cy)
		{
			rect.left += (cx-cy) / 2;
			rect.right = rect.left + cy;
		}
	else
		{
            rect.top += (cy-cx) / 2;
			rect.bottom = rect.top + cx;
		}
	//pDC->TextOut(rect.left,rect.bottom,"123",3);
	pDC->Ellipse(rect);
}
/**/

void CDrawRect::Draw(CDC* pDC)
{
	ASSERT_VALID(this);

	CBrush brush;
	if (!brush.CreateBrushIndirect(&m_logbrush))
		return;
	CPen pen;
	if (!pen.CreatePenIndirect(&m_logpen))
		return;

	CBrush* pOldBrush;
	CPen* pOldPen;

	if (m_bBrush)
		pOldBrush = pDC->SelectObject(&brush);
	else
		pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	if (m_bPen)
		pOldPen = pDC->SelectObject(&pen);
	else
		pOldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);

	CRect rect = m_XDRecPosition;
	switch (m_nShape)
	{
	case rectangle:
		pDC->Rectangle(rect);
		break;

	case roundRectangle:
		pDC->RoundRect(rect, m_roundness);
		break;

	case ellipse:
		pDC->Ellipse(rect);
		break;

	case circle:
		DrawCircle(pDC,rect);
		//pDC->Circle(rect);
		break;

	case XDS_line:
		if (rect.top > rect.bottom)
		{
			rect.top -= m_logpen.lopnWidth.y / 2;
			rect.bottom += (m_logpen.lopnWidth.y + 1) / 2;
		}
		else
		{
			rect.top += (m_logpen.lopnWidth.y + 1) / 2;
			rect.bottom -= m_logpen.lopnWidth.y / 2;
		}

		if (rect.left > rect.right)
		{
			rect.left -= m_logpen.lopnWidth.x / 2;
			rect.right += (m_logpen.lopnWidth.x + 1) / 2;
		}
		else
		{
			rect.left += (m_logpen.lopnWidth.x + 1) / 2;
			rect.right -= m_logpen.lopnWidth.x / 2;
		}

		pDC->MoveTo(rect.TopLeft());
		pDC->LineTo(rect.BottomRight());

		pDC->TextOut(rect.left,rect.top,"test2: left,top");
		pDC->TextOut(rect.right,rect.bottom,"test3: r,b");

		break;
	}

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


int CDrawRect::GetHandleCount()
{
	ASSERT_VALID(this);

	return m_nShape == XDS_line ? 2 :
		CDrawObj::GetHandleCount() + (m_nShape == roundRectangle);
}

// returns center of handle in logical coordinates
CPoint CDrawRect::GetHandle(int nHandle)
{
	ASSERT_VALID(this);

	if (m_nShape == XDS_line && nHandle == 2)
		nHandle = 5;
	else if (m_nShape == roundRectangle && nHandle == 9)
	{
		CRect rect = m_XDRecPosition;
		rect.NormalizeRect();
		CPoint point = rect.BottomRight();
		point.x -= m_roundness.x / 2;
		point.y -= m_roundness.y / 2;
		return point;
	}

	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawRect::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);

	if (m_nShape == XDS_line && nHandle == 2)
		nHandle = 5;
	else if (m_nShape == roundRectangle && nHandle == 9)
		return AfxGetApp()->LoadStandardCursor(IDC_SIZEALL);
	return CDrawObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CDrawRect::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);

	if (m_nShape == XDS_line && nHandle == 2)
		nHandle = 5;
	else if (m_nShape == roundRectangle && nHandle == 9)
	{
		CRect rect = m_XDRecPosition;
		rect.NormalizeRect();
		if (point.x > rect.right - 1)
			point.x = rect.right - 1;
		else if (point.x < rect.left + rect.Width() / 2)
			point.x = rect.left + rect.Width() / 2;
		if (point.y > rect.bottom - 1)
			point.y = rect.bottom - 1;
		else if (point.y < rect.top + rect.Height() / 2)
			point.y = rect.top + rect.Height() / 2;
		m_roundness.x = 2 * (rect.right - point.x);
		m_roundness.y = 2 * (rect.bottom - point.y);
		m_pDocument->SetModifiedFlag();
		if (pView == NULL)
			Invalidate();
		else
			pView->InvalObj(this);
		return;
	}

	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
BOOL CDrawRect::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect rectT = rect;
	rectT.NormalizeRect();

	CRect fixed = m_XDRecPosition;
	fixed.NormalizeRect();
	if ((rectT & fixed).IsRectEmpty())
		return FALSE;

	CRgn rgn;
	switch (m_nShape)
	{
	case rectangle:
		return TRUE;

	case roundRectangle:
		rgn.CreateRoundRectRgn(fixed.left, fixed.top, fixed.right, fixed.bottom,
			m_roundness.x, m_roundness.y);
		break;

	case ellipse:
		rgn.CreateEllipticRgnIndirect(fixed);
		break;

	case XDS_line:
		{
			int x = (m_logpen.lopnWidth.x + 5) / 2;
			int y = (m_logpen.lopnWidth.y + 5) / 2;
			POINT points[4];
			points[0].x = fixed.left;
			points[0].y = fixed.top;
			points[1].x = fixed.left;
			points[1].y = fixed.top;
			points[2].x = fixed.right;
			points[2].y = fixed.bottom;
			points[3].x = fixed.right;
			points[3].y = fixed.bottom;

			if (fixed.left < fixed.right)
			{
				points[0].x -= x;
				points[1].x += x;
				points[2].x += x;
				points[3].x -= x;
			}
			else
			{
				points[0].x += x;
				points[1].x -= x;
				points[2].x -= x;
				points[3].x += x;
			}

			if (fixed.top < fixed.bottom)
			{
				points[0].y -= y;
				points[1].y += y;
				points[2].y += y;
				points[3].y -= y;
			}
			else
			{
				points[0].y += y;
				points[1].y -= y;
				points[2].y -= y;
				points[3].y += y;
			}
			rgn.CreatePolygonRgn(points, 4, ALTERNATE);
		}
		break;
	case circle:
		rgn.CreateEllipticRgnIndirect(fixed);
		break;
	}
	return rgn.RectInRegion(fixed);
}

CDrawObj* CDrawRect::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawRect* pClone = new CDrawRect(m_XDRecPosition);

	pClone->m_bPen = m_bPen;
	pClone->m_logpen = m_logpen;
	pClone->m_bBrush = m_bBrush;
	pClone->m_logbrush = m_logbrush;
	pClone->m_nShape = m_nShape;
	pClone->m_roundness = m_roundness;
	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);

	return pClone;
}
////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CDrawOleObj, CDrawObj, 0)

BOOL CDrawOleObj::c_bShowItems = TRUE;

CDrawOleObj::CDrawOleObj() : m_extent(0,0)
{
	m_pClientItem = NULL;
}

CDrawOleObj::CDrawOleObj(const CRect& position)
	: CDrawObj(position), m_extent(0, 0)
{
	m_pClientItem = NULL;
}

CDrawOleObj::~CDrawOleObj()
{
	if (m_pClientItem != NULL)
	{
		m_pClientItem->Release();
		m_pClientItem = NULL;
	}
}

void CDrawOleObj::Remove()
{
	if (m_pClientItem != NULL)
	{
		m_pClientItem->Delete();
		m_pClientItem = NULL;
	}
	CDrawObj::Remove();
}

void CDrawOleObj::Serialize( CArchive& ar )
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_extent;
		ar << m_pClientItem;
	}
	else
	{
		ar >> m_extent;
		ar >> m_pClientItem;
		m_pClientItem->m_pDrawObj = this;
	}
 }

CDrawObj* CDrawOleObj::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);
 
	AfxGetApp()->BeginWaitCursor();

	CDrawOleObj* pClone = NULL;
	CDrawItem* pItem = NULL;
 
	TRY
	{
		// perform a "deep copy" -- need to copy CDrawOleObj and the CDrawItem
		//  that it points to.
		CDrawOleObj* pClone = new CDrawOleObj(m_XDRecPosition);
		CDrawItem* pItem = new CDrawItem(m_pDocument, pClone);
		if (!pItem->CreateCloneFrom(m_pClientItem))
			AfxThrowMemoryException();

		pClone->m_pClientItem = pItem;
		pClone->m_bPen = m_bPen;
		pClone->m_logpen = m_logpen;
		pClone->m_bBrush = m_bBrush;
		pClone->m_logbrush = m_logbrush;
		ASSERT_VALID(pClone);

		if (pDoc != NULL)
			pDoc->Add(pClone);
	}
	CATCH_ALL(e)
	{
		pItem->Delete();
		pClone->m_pClientItem = NULL;
		pClone->Remove();
		AfxGetApp()->EndWaitCursor();

		THROW_LAST();
	}
	END_CATCH_ALL

	AfxGetApp()->EndWaitCursor();

	return pClone;
}

void CDrawOleObj::Draw(CDC* pDC)
{
	ASSERT_VALID(this);

	CDrawItem* pItem = m_pClientItem;
	if (pItem != NULL)
	{
		// draw the OLE item itself
		pItem->Draw(pDC, m_XDRecPosition);

		// don't draw tracker in print preview or on printer
		if (!pDC->IsPrinting())
		{
			// use a CRectTracker to draw the standard effects
			CRectTracker tracker;
			tracker.m_rect = m_XDRecPosition;
			pDC->LPtoDP(tracker.m_rect);

			if (c_bShowItems)
			{
				// put correct border depending on item type
				if (pItem->GetType() == OT_LINK)
					tracker.m_nStyle |= CRectTracker::dottedLine;
				else
					tracker.m_nStyle |= CRectTracker::solidLine;
			}

			// put hatching over the item if it is currently open
			if (pItem->GetItemState() == COleClientItem::openState ||
				pItem->GetItemState() == COleClientItem::activeUIState)
			{
				tracker.m_nStyle |= CRectTracker::hatchInside;
			}
			tracker.Draw(pDC);
		}
	}
}

void CDrawOleObj::OnOpen(CDrawView* pView)
{
	AfxGetApp()->BeginWaitCursor();
	m_pClientItem->DoVerb(
#ifndef _MAC		
		GetKeyState(VK_CONTROL) < 0 ? OLEIVERB_OPEN : OLEIVERB_PRIMARY,
#else		
		GetKeyState(VK_OPTION) < 0 ? OLEIVERB_OPEN : OLEIVERB_PRIMARY,
#endif		
		pView);
	AfxGetApp()->EndWaitCursor();
}

void CDrawOleObj::OnEditProperties()
{
	// using COlePropertiesDialog directly means no scaling
	COlePropertiesDialog dlg(m_pClientItem, 100, 100, NULL);

	dlg.DoModal();
}

// position is in logical
void CDrawOleObj::MoveTo(const CRect& position, CDrawView* pView)
{
	ASSERT_VALID(this);

	if (position == m_XDRecPosition)
		return;

	// call base class to update position
	CDrawObj::MoveTo(position, pView);

	// update position of in-place editing session on position change
	if (m_pClientItem->IsInPlaceActive())
		m_pClientItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
