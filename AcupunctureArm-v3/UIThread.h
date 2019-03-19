#pragma once

#include "InfomationDlg.h"

// CUIThread

class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)

public:
	CUIThread();
	CInfomationDlg dlg;
	void ShowWindow(BOOL flag);
protected:
//	CUIThread();           // protected constructor used by dynamic creation
	virtual ~CUIThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


