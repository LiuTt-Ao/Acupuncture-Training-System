// ExportChoose.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v3.h"
#include "ExportChoose.h"
#include "afxdialogex.h"
#include "Global.h"


// CExportChoose dialog

IMPLEMENT_DYNAMIC(CExportChoose, CDialogEx)

CExportChoose::CExportChoose(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExportChoose::IDD, pParent)
{

}

CExportChoose::~CExportChoose()
{
}

void CExportChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExportChoose, CDialogEx)
	ON_BN_CLICKED(IDOK, &CExportChoose::OnBnClickedOk)
END_MESSAGE_MAP()


// CExportChoose message handlers


void CExportChoose::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CGlobal::export_choose=GetCheckedRadioButton(IDC_ACUPOINT1, IDC_ACUPOINT5);
	CDialogEx::OnOK();
}
