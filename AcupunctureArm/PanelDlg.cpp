// PanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm.h"
#include "PanelDlg.h"


// CPanelDlg

IMPLEMENT_DYNCREATE(CPanelDlg, CFormView)

CPanelDlg::CPanelDlg()
	: CFormView(CPanelDlg::IDD)
{

}

CPanelDlg::~CPanelDlg()
{
}

void CPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSCOMM, m_Comm);
}

BEGIN_MESSAGE_MAP(CPanelDlg, CFormView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START, &CPanelDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// CPanelDlg diagnostics

#ifdef _DEBUG
void CPanelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPanelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPanelDlg message handlers


void CPanelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CRect rect;
	GetDlgItem(IDC_PLOT)->GetWindowRect(rect);
	GetDlgItem(IDC_PLOT)->ShowWindow(SW_HIDE);
	ScreenToClient(rect);
	CChartAxis *pAxis = NULL;
	m_HSChartCtrl = new CChartCtrl;
	m_HSChartCtrl->Create(this, rect, 2);
	//初始化坐标
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
//	pAxis->EnableScrollBar(true);
	pAxis->SetPanZoomEnabled(true);
	pAxis->GetLabel()->SetText(_T("时间（s）"));
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);
	pAxis->GetLabel()->SetText(_T("压力（mN）"));
	m_pLineSerie = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie->SetColor(RGB(0, 0, 255));
	time = 0;
	/******设置串口********
	m_Comm.put_CommPort(3);
	m_Comm.put_InputMode(1);
	m_Comm.put_InBufferSize(1024);
	m_Comm.put_Settings(_T("9600,n,8,1"));
	************/
	CString str1 = _T("内关穴归属手厥阴心包经，有抒压,解除疲劳，改善胸痛、心悸、盗汗，舒缓腹胀感，缓解治疗头晕、心痛、晕车等作用\r\n"),
		    str2 = _T("内关穴位于手掌面关节横纹的中央，往上约三指宽的中央凹陷处\r\n"),
			str3 = _T("取此穴道时应要患者采用正坐或仰卧，仰掌的姿势，内关穴位于人体的前臂掌侧，从近手腕之横皱纹的中央，往上约三指宽的中央");
	GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str1+str2+str3);
}


void CPanelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CFormView::OnPaint() for painting messages
}


void CPanelDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_pLineSerie->AddPoint(time, sin(time));
	time = time + 0.1;
	CFormView::OnTimer(nIDEvent);
}


void CPanelDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_START)->GetWindowTextW(str);
	if (str == "开始")
	{
		/*******************************
		if (!m_Comm.get_PortOpen())
		{
			try
			{
				m_Comm.put_PortOpen(true);
			}
			catch (COleDispatchException *e)
			{
				CString strError;
				strError.Format(_T("打开串口失败！\n\nError Number: %d \nError Message: %s"), e->m_wCode, e->m_strDescription);
				MessageBoxW(strError, _T("错误提示"), MB_ICONERROR);
				return;
			}
		}
		else
		{
			MessageBoxW(_T("串口已打开!"));
		}
		m_Comm.put_RThreshold(1);
		m_Comm.put_InputLen(0);
		m_Comm.get_Input();
		/*****************************/

		GetDlgItem(IDC_START)->SetWindowTextW(_T("停止"));
		SetTimer(0, 100, NULL);
	}
	if (str == "停止")
	{
		GetDlgItem(IDC_START)->SetWindowTextW(_T("开始"));
		KillTimer(0);

		/***************
		if (m_Comm.get_PortOpen())
			m_Comm.put_PortOpen(false);
		/**********************/
	}
}

/******************************
BEGIN_EVENTSINK_MAP(CPanelDlg, CFormView)
	ON_EVENT(CPanelDlg, IDC_MSCOMM, 1, CPanelDlg::OnOncommMscomm, VTS_NONE)
END_EVENTSINK_MAP()

void CPanelDlg::OnOncommMscomm()
{
	// TODO: Add your message handler code here
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048];
	CString strtemp,strinput;
	if (m_Comm.get_CommEvent() == 2)
	{
		variant_inp = m_Comm.get_Input();
		safearray_inp = variant_inp;
		len = safearray_inp.GetOneDimSize();
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k<len; k++) //将数组转换为Cstring型变量  
		{
			BYTE bt = *(char*)(rxdata + k); //字符型  
			strtemp.Format(_T("%c"), bt); //将字符送入临时变量strtemp存放  
			strinput += strtemp; //加入接收编辑框对应字符串   
		}
		SetDlgItemText(IDC_DESCRIPTION, strinput);
	}
}
********************************/
