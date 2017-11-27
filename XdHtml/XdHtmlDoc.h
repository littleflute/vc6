// XdHtmlDoc.h : interface of the CXdHtmlDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XDHTMLDOC_H__BB0CD64A_0B25_4E46_8910_3AD54772AEA0__INCLUDED_)
#define AFX_XDHTMLDOC_H__BB0CD64A_0B25_4E46_8910_3AD54772AEA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXdHtmlDoc : public CDocument
{
protected: // create from serialization only
	CXdHtmlDoc();
	DECLARE_DYNCREATE(CXdHtmlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXdHtmlDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXdHtmlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXdHtmlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDHTMLDOC_H__BB0CD64A_0B25_4E46_8910_3AD54772AEA0__INCLUDED_)
