//Download by http://www.NewXing.com
// DrawObj.h: interface for the CDrawObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWOBJ_H__1F9C3913_D28E_4925_BCAE_75347FAC48C6__INCLUDED_)
#define AFX_DRAWOBJ_H__1F9C3913_D28E_4925_BCAE_75347FAC48C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawView;
class CDrawDoc;

class CDrawObj : public CObject  
{
protected:
	DECLARE_SERIAL(CDrawObj);
	CDrawObj();

// Constructors
public:
	CDrawObj(const CRect& position);

// Attributes
	CRect m_position;
	CDrawDoc* m_pDocument;

	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	CRect GetHandleRect(int nHandleID, CDrawView* pView);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void SetLineColor(COLORREF color);
	virtual void SetFillColor(COLORREF color);

// Operations
	virtual void Draw(CDC* pDC);
	enum TrackerState { normal, selected, active };
	virtual void DrawTracker(CDC* pDC, TrackerState state);
	virtual void MoveTo(const CRect& positon, CDrawView* pView = NULL);
	virtual int HitTest(CPoint point, CDrawView* pView, BOOL bSelected);
	virtual BOOL Intersects(const CRect& rect);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual void OnOpen(CDrawView* pView);
	virtual void OnEditProperties();
	virtual CDrawObj* Clone(CDrawDoc* pDoc = NULL);
	virtual void Remove();
	void Invalidate();

// Implementation
public:
	virtual ~CDrawObj();
	virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
	void AssertValid();
#endif

	// implementation data
protected:
	BOOL m_bPen;
	LOGPEN m_logpen;
	BOOL m_bBrush;
	LOGBRUSH m_logbrush;
};

// special 'list' class for this application (requires afxtempl.h)
typedef CTypedPtrList<CObList, CDrawObj*> CDrawObjList;

////////////////////////////////////////////////////////////////////////
// specialized draw objects

class CDrawRect : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawRect);
	CDrawRect();

public:
	CDrawRect(const CRect& position);
	void DrawCircle(CDC* pDC,CRect rect);

// Implementation
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
	//virtual void DrawCircle(CDC* pDC,CRect rect);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);

protected:
	enum Shape { rectangle, roundRectangle, ellipse, XDS_line, circle };
	Shape m_nShape;
	CPoint m_roundness; // for roundRect corners

	friend class CRectTool;
};
class CDrawItem;    // COleClientItem derived class

class CDrawOleObj : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawOleObj);
	CDrawOleObj();

public:
	CDrawOleObj(const CRect& position);

// Implementation
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void OnOpen(CDrawView* pView);
	virtual void MoveTo(const CRect& positon, CDrawView* pView = NULL);
	virtual void OnEditProperties();
	virtual void Remove();
	virtual ~CDrawOleObj();

	static BOOL c_bShowItems;

	CDrawItem* m_pClientItem;
	CSize m_extent; // current extent is tracked separate from scaled position
};

#endif // !defined(AFX_DRAWOBJ_H__1F9C3913_D28E_4925_BCAE_75347FAC48C6__INCLUDED_)
