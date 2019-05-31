//Download by http://www.NewXing.com
// MyCodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "walkltdemo.h"
#include "MyCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCodeDlg dialog


CMyCodeDlg::CMyCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCodeDlg)
	m_str = _T("");
	//}}AFX_DATA_INIT
}


void CMyCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCodeDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctrl);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyCodeDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCodeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCodeDlg message handlers

BOOL CMyCodeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ctrl.SetTabStops(16);

	if (!m_title.IsEmpty())
	this->SetWindowText(m_title);

	return TRUE;
}
