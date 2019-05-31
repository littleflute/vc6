//Download by http://www.NewXing.com
// WalkLtDemoDoc.h : interface of the CWalkLtDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALKLTDEMODOC_H__CE421EAF_8EEE_4CA1_AAD2_EF91F6471DC4__INCLUDED_)
#define AFX_WALKLTDEMODOC_H__CE421EAF_8EEE_4CA1_AAD2_EF91F6471DC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWalkLtDemoDoc : public CDocument
{
protected: // create from serialization only
	CWalkLtDemoDoc();
	DECLARE_DYNCREATE(CWalkLtDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWalkLtDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWalkLtDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWalkLtDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WALKLTDEMODOC_H__CE421EAF_8EEE_4CA1_AAD2_EF91F6471DC4__INCLUDED_)
