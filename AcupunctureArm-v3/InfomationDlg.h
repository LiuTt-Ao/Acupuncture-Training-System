#pragma once
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "ChartClass\ChartAxisLabel.h"
#include "ChartClass\ChartLegend.h"

// CInfomationDlg dialog
//神经网络算法参数赋值


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

	double n_data[5][2];
	//神经网络输入数组
	double arr_force0[6];
	double arr_force1[6];
	double arr_force2[6];
	double arr_force3[6];
	double arr_force4[6];
	void renew_array();//数组更新函数
	int jb[5];

	static const int  innode = 6;      //输入结点数
	static const int  hidenode = 4;    //隐含结点数
	static const int  outnode = 3;     //输出结点数

	double result0[outnode];
	double result1[outnode];
	double result2[outnode];
	double result3[outnode];
	double result4[outnode];

	double* recognize(double *p);

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
	//afx_msg void OnBnClickedRadioUp();
};
