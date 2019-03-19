// PanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v2.h"
#include "PanelDlg.h"
#include "afxdialogex.h"


UINT plotThread(LPVOID pParam);
CChartCtrl* m_HSChartCtrl;
CChartLineSerie* m_pLineSerie;
// CPanelDlg dialog

IMPLEMENT_DYNAMIC(CPanelDlg, CDialogBar)

CPanelDlg::CPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialogBar()
{

}

CPanelDlg::~CPanelDlg()
{
}

void CPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPanelDlg, CDialogBar)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, &CPanelDlg::OnBnClickedStart)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CPanelDlg message handlers
LRESULT CPanelDlg::OnInitDialog(UINT wParam, LONG lParam)
{

	// TODO: Add extra initialization here
	LRESULT bRet = HandleInitDialog(wParam, lParam);

	if (!UpdateData(FALSE))

	{

		TRACE0("InitCPanelDlg Failed!");

	}

	
	/*********************
	CRect rect;
	GetDlgItem(IDC_PLOT)->GetWindowRect(rect);
	GetDlgItem(IDC_PLOT)->ShowWindow(SW_HIDE);
	ScreenToClient(rect);
	CChartAxis *pAxis = NULL;
	m_HSChartCtrl = new CChartCtrl;
	m_HSChartCtrl->Create(this, rect, 2);
	//��ʼ������
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	//	pAxis->EnableScrollBar(true);
	pAxis->SetPanZoomEnabled(true);
	pAxis->GetLabel()->SetText(_T("ʱ�䣨s��"));
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);
	pAxis->GetLabel()->SetText(_T("ѹ����mN��"));
	m_pLineSerie = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie->SetColor(RGB(0, 0, 255));

	/******************************/
	CString str1 = _T("�ڹ�Ѩ�����������İ���������ѹ,���ƣ�ͣ�������ʹ���ļ¡��������滺���͸У���������ͷ�Ρ���ʹ���γ�������\r\n"),
		str2 = _T("�ڹ�Ѩλ��������ؽں��Ƶ����룬����Լ��ָ������밼�ݴ�\r\n"),
		str3 = _T("ȡ��Ѩ��ʱӦҪ���߲������������ԣ����Ƶ����ƣ��ڹ�Ѩλ�������ǰ���Ʋ࣬�ӽ�����֮�����Ƶ����룬����Լ��ָ�������");
	GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str1 + str2 + str3);

	return TRUE;  // return TRUE unless you set the focus to a control

	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CPanelDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: Add your message handler code here and/or call default
//	m_pLineSerie->AddPoint(time, sin(time));
//	time = time + 0.1;
//	CDialogBar::OnTimer(nIDEvent);
//}


void CPanelDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_START)->GetWindowTextW(str);
	if (str == "��ʼ")
	{
		GetDlgItem(IDC_START)->SetWindowTextW(_T("ֹͣ"));
//		SetTimer(0, 100, NULL);
		HWND hWnd = ::FindWindowEx(AfxGetMainWnd()->m_hWnd,NULL,L"DisplayClass", NULL);
		AfxBeginThread(plotThread, 0);
	}
	if (str == "ֹͣ")
	{
		GetDlgItem(IDC_START)->SetWindowTextW(_T("��ʼ"));
//		KillTimer(0);
	}
}


//void CPanelDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	CDialogBar::OnUpdateCmdUI(pTarget, FALSE);
//}


void CPanelDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
//	m_pLineSerie->AddPoint(time, sin(time));
//	time = time + 0.1;
	CDialogBar::OnTimer(nIDEvent);
}


UINT plotThread(LPVOID pParam)
{	/************************/
	CRect rect;
	HWND hWnd = ::FindWindowEx(AfxGetMainWnd()->m_hWnd, NULL, L"DisplayClass", NULL);
	CPanelDlg* pWnd = (CPanelDlg*)CPanelDlg::FromHandle(hWnd);
	pWnd->GetDlgItem(IDC_PLOT)->GetWindowRect(&rect);
	pWnd->GetDlgItem(IDC_PLOT)->ShowWindow(SW_HIDE);
	pWnd->ScreenToClient(rect);
	CChartAxis *pAxis = NULL;
	m_HSChartCtrl = new CChartCtrl;
	m_HSChartCtrl->Create(pWnd, rect, 2);
	/*******************
	CWnd *pWnd = AfxGetMainWnd();
//	CView *pView = ((CFrameWndEx *)AfxGetMainWnd())->GetActiveView();
	
	HWND hHwnd = pWnd->m_hWnd;
	HWND Hwnd = ::GetDlgItem(hHwnd, IDD_PANELDLG);
	pWnd->GetDlgItem(IDD_PANELDLG)->GetDlgItem(IDC_PLOT)->GetClientRect(&rect);
//	pWnd->ScreenToClient(rect);
	CChartAxis *pAxis = NULL;
	m_HSChartCtrl = new CChartCtrl;
	m_HSChartCtrl->Create(pWnd->GetDlgItem(IDD_PANELDLG), rect, 2);
	/*******************************

	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis->SetPanZoomEnabled(true);
	pAxis->GetLabel()->SetText(_T("ʱ�䣨s��"));
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);
	pAxis->GetLabel()->SetText(_T("ѹ����mN��"));
	m_pLineSerie = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie->SetColor(RGB(0, 0, 255));
	/*****************************
	double time = 0.0;
	while (time < 1000.0)
	{
		m_pLineSerie->AddPoint(time, sin(time));
		time = time + 0.1;
		Sleep(100);
//		pWnd->Invalidate(FALSE);
	}
	/*******************/

	return 0;
}

int CPanelDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
