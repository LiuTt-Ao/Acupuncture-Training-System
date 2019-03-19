#pragma once
/******************/
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "ChartClass\ChartAxisLabel.h"
#include "ChartClass\ChartLegend.h"
/*******************/


// CPanelDlg dialog

class CPanelDlg : public CDialogBar
{
	DECLARE_DYNAMIC(CPanelDlg)

public:
	CPanelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPanelDlg();

//	CChartCtrl* m_HSChartCtrl;
//	CChartLineSerie* m_pLineSerie;
//	double time;

// Dialog Data
	enum { IDD = IDD_PANELDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT OnInitDialog(UINT wParam, LONG lParam);
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStart();
//	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHandler);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
