// CalibrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v3.h"
#include "CalibrationDlg.h"
#include "afxdialogex.h"


// CCalibrationDlg dialog

IMPLEMENT_DYNAMIC(CCalibrationDlg, CDialogEx)

CCalibrationDlg::CCalibrationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalibrationDlg::IDD, pParent)
{

}

CCalibrationDlg::~CCalibrationDlg()
{
}

void CCalibrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalibrationDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CCalibrationDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCalibrationDlg message handlers


void CCalibrationDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CGlobal::calibrated = TRUE;
//	CDialogEx::OnOK();
}


void CCalibrationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString str=L" ";
	str.Format(L"%lf", CGlobal::force[0]);
	GetDlgItem(IDC_EDIT_FORCE1)->SetWindowTextW(str);

	str.Format(L"%lf", CGlobal::force[1]);
	GetDlgItem(IDC_EDIT_FORCE2)->SetWindowTextW(str);

	str.Format(L"%lf", CGlobal::force[2]);
	GetDlgItem(IDC_EDIT_FORCE3)->SetWindowTextW(str);

	str.Format(L"%lf", CGlobal::force[3]);
	GetDlgItem(IDC_EDIT_FORCE4)->SetWindowTextW(str);

	str.Format(L"%lf", CGlobal::force[4]);
	GetDlgItem(IDC_EDIT_FORCE5)->SetWindowTextW(str);

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CCalibrationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetTimer(1, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
