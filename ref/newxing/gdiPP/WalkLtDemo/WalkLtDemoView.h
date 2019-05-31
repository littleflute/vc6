//Download by http://www.NewXing.com
// WalkLtDemoView.h : interface of the CWalkLtDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALKLTDEMOVIEW_H__6B1DD540_4701_4CCC_867C_143F4DBF0EEE__INCLUDED_)
#define AFX_WALKLTDEMOVIEW_H__6B1DD540_4701_4CCC_867C_143F4DBF0EEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWalkLtDemoView : public CView
{
protected: // create from serialization only
	CWalkLtDemoView();
	DECLARE_DYNCREATE(CWalkLtDemoView)

// Attributes
public:
	CWalkLtDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalkLtDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWalkLtDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWalkLtDemoView)
	afx_msg void OnGdiplusDemo();
	afx_msg void OnGdiplusCode();
	afx_msg void OnUpdateGdiplusCode(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WalkLtDemoView.cpp
inline CWalkLtDemoDoc* CWalkLtDemoView::GetDocument()
   { return (CWalkLtDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALKLTDEMOVIEW_H__6B1DD540_4701_4CCC_867C_143F4DBF0EEE__INCLUDED_)
