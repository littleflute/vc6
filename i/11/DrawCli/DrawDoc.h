//Download by http://www.NewXing.com
// DrawDoc.h : interface of the CDrawDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWDOC_H__1D9F1D00_6EE7_4704_9BBD_3ECE7D4638FB__INCLUDED_)
#define AFX_DRAWDOC_H__1D9F1D00_6EE7_4704_9BBD_3ECE7D4638FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
//class CDrawObj;
 
class CDrawDoc : public COleDocument
{
protected: // create from serialization only
	CDrawObjList m_objects;
	CSize m_size;
	int m_nMapMode;
	CDrawDoc();
	DECLARE_DYNCREATE(CDrawDoc)

// Attributes
public:
	COLORREF m_paperColor;

// Operations
public:
	void ComputePageSize();
	void Draw(CDC* pDC,CDrawView* pView);
	const CSize& GetSize() const { return m_size; }
	COLORREF GetPaperColor() const { return m_paperColor; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Remove(CDrawObj* pObj);
	CDrawObj* ObjectAt(const CPoint& point);
	CDrawObjList* GetObjects() { return &m_objects; }
	void Add(CDrawObj* pObj);
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawDoc)
	afx_msg void OnViewPapercolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDOC_H__1D9F1D00_6EE7_4704_9BBD_3ECE7D4638FB__INCLUDED_)
