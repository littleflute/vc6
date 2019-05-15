//Download by http://www.NewXing.com
// CntrItem.h : interface of the CDrawItem class
//

#if !defined(AFX_CNTRITEM_H__1B01D2CD_13E2_4042_B354_6458D9F1A132__INCLUDED_)
#define AFX_CNTRITEM_H__1B01D2CD_13E2_4042_B354_6458D9F1A132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDrawDoc;
class CDrawView;

class CDrawItem : public COleClientItem
{
	DECLARE_SERIAL(CDrawItem)

// Constructors
public:
	BOOL UpdateExtent();
	CDrawOleObj* m_pDrawObj;
//	CDrawItem(CDrawDoc* pContainer = NULL);
	CDrawItem(CDrawDoc* pContainer = NULL, CDrawOleObj* pDrawObj = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CDrawDoc* GetDocument()
		{ return (CDrawDoc*)COleClientItem::GetDocument(); }
	CDrawView* GetActiveView()
		{ return (CDrawView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CDrawItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__1B01D2CD_13E2_4042_B354_6458D9F1A132__INCLUDED_)
