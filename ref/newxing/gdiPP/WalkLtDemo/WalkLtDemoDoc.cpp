//Download by http://www.NewXing.com
// WalkLtDemoDoc.cpp : implementation of the CWalkLtDemoDoc class
//

#include "stdafx.h"
#include "WalkLtDemo.h"

#include "WalkLtDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoDoc

IMPLEMENT_DYNCREATE(CWalkLtDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CWalkLtDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CWalkLtDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoDoc construction/destruction

CWalkLtDemoDoc::CWalkLtDemoDoc()
{
	// TODO: add one-time construction code here

}

CWalkLtDemoDoc::~CWalkLtDemoDoc()
{
}

BOOL CWalkLtDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoDoc serialization

void CWalkLtDemoDoc::Serialize(CArchive& ar)
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
// CWalkLtDemoDoc diagnostics

#ifdef _DEBUG
void CWalkLtDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWalkLtDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWalkLtDemoDoc commands
