// XdHtmlDoc.cpp : implementation of the CXdHtmlDoc class
//

#include "stdafx.h"
#include "XdHtml.h"

#include "XdHtmlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlDoc

IMPLEMENT_DYNCREATE(CXdHtmlDoc, CDocument)

BEGIN_MESSAGE_MAP(CXdHtmlDoc, CDocument)
	//{{AFX_MSG_MAP(CXdHtmlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlDoc construction/destruction

CXdHtmlDoc::CXdHtmlDoc()
{
	// TODO: add one-time construction code here

}

CXdHtmlDoc::~CXdHtmlDoc()
{
}

BOOL CXdHtmlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXdHtmlDoc serialization

void CXdHtmlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlDoc diagnostics

#ifdef _DEBUG
void CXdHtmlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXdHtmlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXdHtmlDoc commands
