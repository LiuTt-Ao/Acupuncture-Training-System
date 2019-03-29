
// AcupunctureArm-v3.h : main header file for the AcupunctureArm-v3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "UIThread.h"

// CAcupunctureArmv3App:
// See AcupunctureArm-v3.cpp for the implementation of this class
//

class CAcupunctureArmv3App : public CWinApp
{
public:
	CAcupunctureArmv3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	BOOL InfoDisplay;
	CUIThread* myThread;

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	afx_msg void On32771();
	afx_msg void OnStart();
	afx_msg void OnStartCalibration();
	afx_msg void OnInformationDisplay();
	afx_msg void OnUpdateInformationDisplay(CCmdUI *pCmdUI);
};

extern CAcupunctureArmv3App theApp;
