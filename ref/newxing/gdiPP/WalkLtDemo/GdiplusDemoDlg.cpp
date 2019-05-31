//Download by http://www.NewXing.com
// GdiplusDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WalkLtDemo.h"
#include "GdiplusDemoDlg.h"

#include "MyCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGdiplusDemoDlg dialog


CGdiplusDemoDlg::CGdiplusDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGdiplusDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGdiplusDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGdiplusDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGdiplusDemoDlg)
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGdiplusDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGdiplusDemoDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGdiplusDemoDlg message handlers

extern void FillGdiplusFuns(CTreeCtrl &tree);

BOOL CGdiplusDemoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	FillGdiplusFuns(m_ctrlTree);

	return TRUE;
}

void CGdiplusDemoDlg::OnButton1() 
{
	HTREEITEM h=m_ctrlTree.GetSelectedItem();
	if (!h)
	{
		AfxMessageBox("请选择一演示项");
		return;
	}
	int res = m_ctrlTree.GetItemData(h);

	m_index1 = res/0x100;
	m_index2 = res&0x00FF;

	if (m_index1<1 || m_index2<1)
	{
		AfxMessageBox("请选择一可演示项");
		return;
	}

	//获取函数的源代码
	CString GetGdiplusFunsCode(int index1, int index2);
	CMyCodeDlg dlg;
	dlg.m_str = GetGdiplusFunsCode(m_index1, m_index2);
	dlg.m_title=m_ctrlTree.GetItemText(h);
	dlg.DoModal();
}

void CGdiplusDemoDlg::OnOK() 
{
	UpdateData();

	HTREEITEM h=m_ctrlTree.GetSelectedItem();
	if (!h)
	{
		AfxMessageBox("请选择一演示项");
		return;
	}
	int res = m_ctrlTree.GetItemData(h);

	m_index1 = res/0x100;
	m_index2 = res&0x00FF;

	if (m_index1<1 || m_index2<1)
	{
		AfxMessageBox("请选择一可演示项");
		return;
	}

	CDialog::OnOK();
}
