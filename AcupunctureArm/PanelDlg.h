#pragma once
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "ChartClass\ChartAxisLabel.h"
#include "ChartClass\ChartLegend.h"
#include "mscomm.h"


// CPanelDlg form view

class CPanelDlg : public CFormView
{
	DECLARE_DYNCREATE(CPanelDlg)

protected:
	CPanelDlg();           // protected constructor used by dynamic creation
	virtual ~CPanelDlg();

public:
	enum { IDD = IDD_PANELDLG };

	CChartCtrl* m_HSChartCtrl;
	CChartLineSerie* m_pLineSerie;
	double time;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStart();
	CMscomm m_Comm;
//	DECLARE_EVENTSINK_MAP()
	void OnOncommMscomm();
};


