
// AcupunctureArm.h : main header file for the AcupunctureArm application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAcupunctureArmApp:
// See AcupunctureArm.cpp for the implementation of this class
//

class CAcupunctureArmApp : public CWinAppEx
{
public:
	CAcupunctureArmApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAcupunctureArmApp theApp;
