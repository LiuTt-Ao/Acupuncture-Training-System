// UIThread.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v3.h"
#include "UIThread.h"


// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread()
{
}

CUIThread::~CUIThread()
{
}

BOOL CUIThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	m_pMainWnd = &dlg;
//	dlg.DoModal();
	dlg.Create(CInfomationDlg::IDD);
	dlg.ShowWindow(SW_SHOW);
	return TRUE;
}

int CUIThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
END_MESSAGE_MAP()


// CUIThread message handlers

void CUIThread::ShowWindow(BOOL flag)
{
	if (flag)
		dlg.ShowWindow(SW_SHOW);
	else
		dlg.ShowWindow(SW_HIDE);
}
