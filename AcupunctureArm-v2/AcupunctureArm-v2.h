
// AcupunctureArm-v2.h : main header file for the AcupunctureArm-v2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CAcupunctureArmv2App:
// See AcupunctureArm-v2.cpp for the implementation of this class
//

class CAcupunctureArmv2App : public CWinAppEx
{
public:
	CAcupunctureArmv2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAcupunctureArmv2App theApp;
