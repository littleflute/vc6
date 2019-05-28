//Download by http://www.NewXing.com
// DrawTool.h: interface for the CDrawTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWTOOL_H__67B343D6_9A89_4CAD_A4B9_2EEF72C5EF10__INCLUDED_)
#define AFX_DRAWTOOL_H__67B343D6_9A89_4CAD_A4B9_2EEF72C5EF10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "drawobj.h"
class CDrawView;

enum DrawShape {	selection, 	XDDS_line, 	rect,	roundRect,	ellipse,    circle,	poly};

class CDrawTool  
{
// Constructors
public:
	CDrawTool(DrawShape nDrawShape);

// Overridables
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnEditProperties(CDrawView* pView);
	virtual void OnCancel();

// Attributes
	DrawShape m_drawShape;

	static CDrawTool*	FindTool(DrawShape drawShape);
	static CPtrList		c_tools;
	static CPoint		c_down;
	static UINT			c_nDownFlags;
	static CPoint		c_last;
	static DrawShape	c_drawShape;

};

class CSelectTool : public CDrawTool
{
// Constructors
public:
	CSelectTool();

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnEditProperties(CDrawView* pView);
};

class CRectTool : public CDrawTool
{
// Constructors
public:
	CRectTool(DrawShape drawShape);

// Implementation
	virtual void OnLButtonDown(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonDblClk(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnLButtonUp(CDrawView* pView, UINT nFlags, const CPoint& point);
	virtual void OnMouseMove(CDrawView* pView, UINT nFlags, const CPoint& point);
};

#endif // !defined(AFX_DRAWTOOL_H__67B343D6_9A89_4CAD_A4B9_2EEF72C5EF10__INCLUDED_)
