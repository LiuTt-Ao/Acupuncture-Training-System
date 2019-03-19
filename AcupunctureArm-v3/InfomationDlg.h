#pragma once
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "ChartClass\ChartAxisLabel.h"
#include "ChartClass\ChartLegend.h"

// CInfomationDlg dialog

class CInfomationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInfomationDlg)

public:
	CInfomationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInfomationDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_INFORMATION };
	CChartCtrl* m_HSChartCtrl;
	CChartLineSerie* m_pLineSerie1;
	CChartLineSerie* m_pLineSerie2;
	CChartLineSerie* m_pLineSerie3;
	CChartLineSerie* m_pLineSerie4;
	CChartLineSerie* m_pLineSerie5;
	CChartLineSerie* m_pLineSerie6;
	double time;
	CString str[5][3];
	int num = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonExportData();
	afx_msg void OnBnClickedButtonImportData();
	afx_msg void OnPaint();
};
