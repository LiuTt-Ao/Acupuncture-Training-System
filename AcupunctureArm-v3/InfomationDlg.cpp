// InfomationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v3.h"
#include "InfomationDlg.h"
#include "afxdialogex.h"
#include <gdiplus.h>
#include <locale>
#include "ExportChoose.h"


/***********从手掌往上依次为***************
穴位1：阴郄穴
穴位2：关内穴
穴位3：孔最穴
穴位4：尺泽穴（靠外）
穴位5：少海穴（靠内）
*************/

// CInfomationDlg dialog

IMPLEMENT_DYNAMIC(CInfomationDlg, CDialogEx)

CInfomationDlg::CInfomationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfomationDlg::IDD, pParent)
{

}

CInfomationDlg::~CInfomationDlg()
{
}

void CInfomationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfomationDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CInfomationDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CInfomationDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CInfomationDlg::OnBnClickedButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CInfomationDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_DATA, &CInfomationDlg::OnBnClickedButtonExportData)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_DATA, &CInfomationDlg::OnBnClickedButtonImportData)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInfomationDlg message handlers


void CInfomationDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CMenu *pMenu = (CMenu *)AfxGetApp()->m_pMainWnd->GetMenu();
	pMenu->GetSubMenu(1)->EnableMenuItem(ID_INFORMATION_DISPLAY, MF_BYCOMMAND | MF_ENABLED);
	ShowWindow(SW_HIDE);
//	CDialogEx::OnCancel();
}


BOOL CInfomationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
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
	//pAxis->SetPanZoomEnabled(true);
	pAxis->GetLabel()->SetText(_T("时间（s）"));
	pAxis = m_HSChartCtrl->CreateStandardAxis(CChartCtrl::LeftAxis);
	//pAxis->SetAutomatic(true);
	pAxis->GetLabel()->SetText(_T("压力（10mN）"));
	m_pLineSerie1 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie1->SetColor(RGB(0, 0, 255));
	m_pLineSerie1->SetSmooth(true);
	m_pLineSerie2 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie2->SetColor(RGB(200, 200, 0));
	m_pLineSerie2->SetSmooth(true);
	m_pLineSerie3 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie3->SetColor(RGB(0, 255, 0));
	m_pLineSerie3->SetSmooth(true);
	m_pLineSerie4 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie4->SetColor(RGB(0, 255, 255));
	m_pLineSerie4->SetSmooth(true);
	m_pLineSerie5 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie5->SetColor(RGB(255, 0, 255));
	m_pLineSerie5->SetSmooth(true);
	m_pLineSerie6 = m_HSChartCtrl->CreateLineSerie();
	m_pLineSerie6->SetColor(RGB(0, 0, 0));
	m_pLineSerie6->SetSmooth(true);
	time = 0;
	str[0][0] = _T("内关穴归属手少阴心经，有清心安神、沟通心肾、清心滋阴、安神固表的作用\r\n\r\n");
	str[0][1] = _T("阴郄穴位于前臂掌侧，当尺侧腕屈肌腱的桡侧缘，腕横纹上0.5寸\r\n\r\n");
	str[0][2] = _T("取此穴道时应仰掌，于尺侧腕屈肌肌腱桡侧缘，神门上0.5寸，横平尺骨头的下缘（头部）处取穴");
	str[1][0] = _T("内关穴位于手掌面关节横纹的中央，往上约三指宽的中央凹陷处\r\n\r\n");
	str[1][1] = _T("大陵穴位于人体腕掌横纹的中点处，当掌长肌腱与桡侧腕屈肌腱之间\r\n\r\n");
	str[1][2] = _T("取此穴道时应要患者采用正坐或仰卧，仰掌的姿势，内关穴位于人体的前臂掌侧，从近手腕之横皱纹的中央，往上约三指宽的中央");
	str[2][0] = _T("孔最穴归属于手太阴肺经穴，有缓解治疗咳嗽、气喘、咽痛、支气管炎、鼻出血、便血、肘臂痛等作用\r\n\r\n");
	str[2][1] = _T("孔最穴位于人体前臂掌面桡侧，当尺泽穴与太渊穴连线上，腕横纹上7寸\r\n\r\n");
	str[2][2] = _T("取此穴道时伸臂仰掌，于尺泽与太渊连线的中点向上1寸，当桡骨内缘处取穴");
	str[3][0] = _T("尺泽穴归属太阴肺经，有清热和胃，通络止痛，清肺泻火，调理肠腑等作用\r\n\r\n");
	str[3][1] = _T("尺泽穴位于肘横纹中，肱二头肌腱桡侧凹陷处\r\n\r\n");
	str[3][2] = _T("取此穴道时应采用正坐、仰掌并微曲肘的取穴姿势");
	str[4][0] = _T("少海穴归属手少阴心经，有缓解治疗精神分裂症、肋间神经痛、臂麻、手颤、健忘等作用\r\n\r\n");
	str[4][1] = _T("尺泽穴位于肘横纹内侧端与肱骨内上髁连线的中点处\r\n\r\n");
	str[4][2] = _T("取此穴道时应屈肘，在肘横纹尺侧纹头凹陷处取穴");
//	GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str1 + str2 + str3);

//	SetTimer(0, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CInfomationDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	if (CGlobal::force[0] > 20.0)
	{
		GetDlgItem(IDC_ACUPOINT_NAME)->SetWindowTextW(L"阴郄穴");
		GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str[0][0] + str[0][1] + str[0][2]);
	}
		if ((CGlobal::force[0] > 20.0) && (CGlobal::velocity[0] > 50.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::velocity[0] < -50.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::force[0]>30.0) && (CGlobal::velocity[0]<25.0) && (CGlobal::velocity[0]>-25.0) 
			&& (CGlobal::velocity2[0]<25.0) && (CGlobal::velocity2[0]>-25.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
		}
	

	if (CGlobal::force[1] > 20.0)
	{
		GetDlgItem(IDC_ACUPOINT_NAME)->SetWindowTextW(L"内关穴");
		GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str[1][0] + str[1][1] + str[1][2]);
	}
		if ((CGlobal::force[1] > 20.0) && (CGlobal::velocity[1] > 50.0) )
		{
			//(CGlobal::velocity[1] > 50.0) && (CGlobal::acceleration[1] > 250.0)
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::velocity[1] < -50.0))
		{
			//(CGlobal::velocity[1] < -80.0) && (CGlobal::acceleration[1] < -400.0)
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if((CGlobal::force[1]>30.0) && (CGlobal::velocity[1]<25.0) && (CGlobal::velocity[1]>-25.0) 
			&& (CGlobal::velocity2[1]<25.0) && (CGlobal::velocity2[1]>-25.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);					
		}
	

	if (CGlobal::force[2] > 20.0)
	{
		GetDlgItem(IDC_ACUPOINT_NAME)->SetWindowTextW(L"孔最穴");
		GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str[2][0] + str[2][1] + str[2][2]);
	}
		if ((CGlobal::force[2] > 20.0) && (CGlobal::velocity[2] > 50.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::velocity[2] < -50.0) )
		{
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::force[2]>30.0) && (CGlobal::velocity[2]<25.0) && (CGlobal::velocity[2]>-25.0) 
			&& (CGlobal::velocity2[2]<25.0) && (CGlobal::velocity2[2]>-25.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
		}
	

	if (CGlobal::force[3] > 20.0)
	{
		GetDlgItem(IDC_ACUPOINT_NAME)->SetWindowTextW(L"尺泽穴");
		GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str[3][0] + str[3][1] + str[3][2]);
	}
		if ((CGlobal::force[3] > 20.0) && (CGlobal::velocity[3] > 50.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::velocity[3] < -50.0) )
		{
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::force[3]>30.0) && (CGlobal::velocity[3]<25.0) && (CGlobal::velocity[3]>-25.0) 
			&& (CGlobal::velocity2[3]<25.0) && (CGlobal::velocity2[3]>-25.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
		}
	

	if (CGlobal::force[4] > 20.0)
	{
		GetDlgItem(IDC_ACUPOINT_NAME)->SetWindowTextW(L"少海穴");
		GetDlgItem(IDC_DESCRIPTION)->SetWindowTextW(str[4][0] + str[4][1] + str[4][2]);
	}
		if ((CGlobal::force[4] > 20.0) && (CGlobal::velocity[4] > 50.0) )
		{
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::velocity[4] < -50.0) )
		{
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(FALSE);
		}
		if ((CGlobal::force[4]>30.0) && (CGlobal::velocity[4]<25.0) && (CGlobal::velocity[4]>-25.0) 
			&& (CGlobal::velocity2[4]<25.0) && (CGlobal::velocity2[4]>-25.0))
		{
			((CButton *)GetDlgItem(IDC_RADIO_ROTATE))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_RADIO_UP))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_RADIO_DOWN))->SetCheck(FALSE);
		}
	
	/**********Force******************/
	m_pLineSerie1->AddPoint(time, CGlobal::force[0]);
	m_pLineSerie2->AddPoint(time, CGlobal::force[1]);
	m_pLineSerie3->AddPoint(time, CGlobal::force[2]);
	m_pLineSerie4->AddPoint(time, CGlobal::force[3]);
	m_pLineSerie5->AddPoint(time, CGlobal::force[4]);
	/**********************************/
	/**********Velocity******************
	m_pLineSerie1->AddPoint(time, CGlobal::velocity[0]);
	m_pLineSerie2->AddPoint(time, CGlobal::velocity[1]);
	m_pLineSerie3->AddPoint(time, CGlobal::velocity[2]);
	m_pLineSerie4->AddPoint(time, CGlobal::velocity[3]);
	m_pLineSerie5->AddPoint(time, CGlobal::velocity[4]);
	/**********************************/

	/**********Acceleration******************
	m_pLineSerie1->AddPoint(time, CGlobal::acceleration[0]);
	m_pLineSerie2->AddPoint(time, CGlobal::acceleration[1]);
	m_pLineSerie3->AddPoint(time, CGlobal::acceleration[2]);
	m_pLineSerie4->AddPoint(time, CGlobal::acceleration[3]);
	m_pLineSerie5->AddPoint(time, CGlobal::acceleration[4]);
	/**********************************/

	time = time + 0.1;
	CDialogEx::OnTimer(nIDEvent);
}


void CInfomationDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItem(IDC_BUTTON_STOP)->GetWindowTextW(str);
	if (CGlobal::connected)
	{
		if (str == "开始")
		{
			GetDlgItem(IDC_BUTTON_STOP)->SetWindowTextW(_T("停止"));
			SetTimer(0, 200, NULL);
		}
		if (str == "停止")
		{
			GetDlgItem(IDC_BUTTON_STOP)->SetWindowTextW(_T("开始"));
			KillTimer(0);
		}
	}
	else
	{
		MessageBox(L"请先连接网络！");
	}
}


void CInfomationDlg::OnBnClickedButtonExport()
{
	// TODO: Add your control notification handler code here
	CString defaultDir = L"";   //默认打开的文件路径  
	CString fileName = L"ForceCurve.jpg"; //默认打开的文件名  
	CString filter = L"文件 (*.jpg; *.png; *.bmp)|*.jpg;*.png;*.bmp||";   //文件过虑的类型  
	CFileDialog openFileDlg(false, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = L"ForceCurve.jpg";
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if (result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		TChartString imageNmae = filePath.GetString();
		m_HSChartCtrl->SaveAsImage(imageNmae, 0, 32);
	}
}


void CInfomationDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	m_pLineSerie1->ClearSerie();
	m_pLineSerie2->ClearSerie();
	m_pLineSerie3->ClearSerie();
	m_pLineSerie4->ClearSerie();
	m_pLineSerie5->ClearSerie();
	m_pLineSerie6->ClearSerie();
}


void CInfomationDlg::OnBnClickedButtonExportData()
{
	// TODO: Add your control notification handler code here
	CExportChoose dlg;
	CChartLineSerie *m_pLineSerie=NULL;
	if (dlg.DoModal())
	{
		switch (CGlobal::export_choose)
		{
		case 1001:m_pLineSerie = m_pLineSerie1; break;
		case 1002:m_pLineSerie = m_pLineSerie2; break;
		case 1003:m_pLineSerie = m_pLineSerie3; break;
		case 1004:m_pLineSerie = m_pLineSerie4; break;
		case 1005:m_pLineSerie = m_pLineSerie5; break;
		default:m_pLineSerie = NULL; break;
		}
	}
	unsigned int num=m_pLineSerie->GetPointsCount();
	double *pX = new double[num]; double *pY = new double[num];
	CString str1,str2;
	m_pLineSerie->GetAllXYPointValue(pX, pY, num);
	CFileDialog openFileDlg(false, _T("csv"), _T("data.csv"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Excel CSV File(*.csv)|*.csv|All File(*.*)|*.*||"), NULL);
	if (openFileDlg.DoModal() == IDOK)
	{
		setlocale(LC_CTYPE, ("chs"));
		CString filename = openFileDlg.GetPathName();
		CStdioFile file(filename, CFile::modeCreate | CFile::modeWrite);
		str1 = L"时间"; str2 = L"压力值";
		file.WriteString(str1 + L"," + str2 + L"\n");
		for (unsigned int i = 0; i < num; i++)
		{
			str1.Format(_T("%lf"), pX[i]);
			str2.Format(_T("%lf"), pY[i]);
			file.WriteString(str1 + L"," + str2 + L"\n");
		}
		file.Close();
	}
	if (pX!=NULL)
		delete pX;
	if (pY != NULL)
		delete pY;
}


void CInfomationDlg::OnBnClickedButtonImportData()
{
	// TODO: Add your control notification handler code here
	CFileDialog openFileDlg(true, _T("csv"), NULL,  OFN_FILEMUSTEXIST, _T("Excel CSV File(*.csv)|*.csv||"), NULL);
	if (openFileDlg.DoModal() == IDOK)
	{
		setlocale(LC_CTYPE, ("chs"));
		CString filename = openFileDlg.GetPathName();
		CStdioFile file;
		file.Open(filename, CFile::modeRead);
		CString str;
		while (file.ReadString(str))
		{
			str = str.Trim(_T(" "));
			CString substr[2] = { NULL };
			int index = str.Find(_T(","));
			if (index != -1)
			{
				substr[0] = str.Left(index);
				substr[1] = str.Right(str.GetLength() - index - 1);
			}
			if (substr[0] != L"时间" && substr[1] != L"压力值")
				m_pLineSerie6->AddPoint(_ttof(substr[0]), _ttof(substr[1]));
		}
		file.Close();
	}
}


void CInfomationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect prect;
	GetDlgItem(IDC_STATIC_ACUPOINT1)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT1)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(0, 0, 255)));
	GetDlgItem(IDC_STATIC_ACUPOINT2)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT2)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(200, 200, 0)));
	GetDlgItem(IDC_STATIC_ACUPOINT3)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT3)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(0, 255, 0)));
	GetDlgItem(IDC_STATIC_ACUPOINT4)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT4)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(0, 255, 255)));
	GetDlgItem(IDC_STATIC_ACUPOINT5)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT5)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(255, 0, 255)));
	GetDlgItem(IDC_STATIC_ACUPOINT6)->GetClientRect(&prect);
	FillRect(GetDlgItem(IDC_STATIC_ACUPOINT6)->GetDC()->GetSafeHdc(), &prect, CBrush(RGB(0, 0, 0)));
	// Do not call CDialogEx::OnPaint() for painting messages
}
