// ConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AcupunctureArm-v3.h"
#include "ConnectDlg.h"
#include "afxdialogex.h"


// CConnectDlg dialog
SOCKET sock;
UINT recv_thd(LPVOID p);
UINT send_thd(LPVOID p);
IMPLEMENT_DYNAMIC(CConnectDlg, CDialogEx)

CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnectDlg::IDD, pParent)
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON1, &CConnectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CConnectDlg::OnBnClickedButtonConnect)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CConnectDlg message handlers


//void CConnectDlg::OnBnClickedButton1()
//{
//	// TODO: Add your control notification handler code here
//}


void CConnectDlg::OnBnClickedButtonConnect()
{
	// TODO: Add your control notification handler code here
	WSADATA wsaData;
	SOCKADDR_IN server_addr;
	WORD wVersion;
	wVersion = MAKEWORD(2, 2);
	WSAStartup(wVersion, &wsaData);

	DWORD ipAddres;
	CString strIP;
	CString port;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->GetAddress(ipAddres);
	((CEdit*)GetDlgItem(IDC_PORT))->GetWindowTextW(port);

	int port_num = _ttoi(port); 
	unsigned char *pIP = (unsigned char*)&ipAddres;
	strIP.Format(L"%u.%u.%u.%u", *(pIP + 3), *(pIP + 2), *(pIP + 1), *pIP);

	USES_CONVERSION;
	server_addr.sin_addr.s_addr = inet_addr(W2A(strIP));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_num);

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		MessageBox(L"Failed to create socket!");
	}
	else
	{
		if (connect(sock, (struct sockaddr *) &server_addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			MessageBox(L"Failed to connect!");
		}
		else
		{
			GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowTextW(L"已连接");
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
			CGlobal::connected = TRUE;
			CMenu *pMenu = (CMenu *)AfxGetApp()->m_pMainWnd->GetMenu();
			pMenu->GetSubMenu(0)->EnableMenuItem(ID_START, MF_BYCOMMAND | MF_DISABLED);
			AfxBeginThread(&recv_thd, 0);
			AfxBeginThread(&send_thd, 0);
			CDialogEx::OnCancel();
		}
	}
}


BOOL CConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CIPAddressCtrl *ip = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	ip->SetAddress(192,168,16,254);

	CEdit *port = (CEdit*)GetDlgItem(IDC_PORT);
	port->SetWindowTextW(L"8080");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


UINT recv_thd(LPVOID p)
{
	int res;
	char msg[100],hex_msg[100],stor_msg[50];
	int js = 0;
	CString dataStr[5];
	double offset[5] = { 0.0 };
	double slide_filter_data[5][5] = { 0.0 };
	double force_data[5][3] = { 0.0 };
	double vel_data[5][2] = { 0.0 };
	while (1)
	{
		if ((res = recv(sock, msg, 100, 0)) <= 0)
		{
			CGlobal::connected = FALSE;
			CMenu *pMenu = (CMenu *)AfxGetApp()->m_pMainWnd->GetMenu();
			pMenu->GetSubMenu(0)->EnableMenuItem(ID_START, MF_BYCOMMAND | MF_ENABLED);
			AfxMessageBox(L"连接断开！");
			break;
		}
		else
		{
			msg[res] = '\0';
			CGlobal::hex_to_str(hex_msg, msg);

			if (js==0 && hex_msg[1]=='f' && hex_msg[2]=='e' && hex_msg[4]=='0' && hex_msg[5]=='4' && hex_msg[7]=='1' && hex_msg[8]=='0')
			{
				for (int i = 0; i < 48; i++)
				{
					stor_msg[i] = hex_msg[i];
				}
				js = 1;
			}

			if (js==1)
			{
				if (stor_msg[44] == hex_msg[44] && stor_msg[46] == hex_msg[46] && stor_msg[47] == hex_msg[47])
				{
					dataStr[0] = ((CString)stor_msg[10]) + ((CString)stor_msg[11]) + ((CString)stor_msg[13]) + ((CString)stor_msg[14]);
					dataStr[1] = ((CString)stor_msg[16]) + ((CString)stor_msg[17]) + ((CString)stor_msg[19]) + ((CString)stor_msg[20]);
					dataStr[2] = ((CString)stor_msg[22]) + ((CString)stor_msg[23]) + ((CString)stor_msg[25]) + ((CString)stor_msg[26]);
					dataStr[3] = ((CString)stor_msg[28]) + ((CString)stor_msg[29]) + ((CString)stor_msg[31]) + ((CString)stor_msg[32]);
					dataStr[4] = ((CString)stor_msg[34]) + ((CString)stor_msg[35]) + ((CString)stor_msg[37]) + ((CString)stor_msg[38]);

					if (CGlobal::calibrated)
					{
						for (int i = 0; i < 5; i++)
						{
							offset[i] = CGlobal::hex_to_dec(dataStr[i]);
						}
					}

					for (int j = 0; j < 5; j++)
					{
						CGlobal::force[j] = (CGlobal::hex_to_dec(dataStr[j]) - offset[j]) * 0.025;
						/***************中值滑动平均滤波*******************/
						slide_filter_data[j][0] = slide_filter_data[j][1];
						slide_filter_data[j][1] = slide_filter_data[j][2];
						slide_filter_data[j][2] = slide_filter_data[j][3];
						slide_filter_data[j][3] = slide_filter_data[j][4];
						slide_filter_data[j][4] = CGlobal::force[j];
						//						CGlobal::force[j] = CGlobal::slide_average_filter(slide_filter_data[j], 5);
						int m = CGlobal::maxIndex(slide_filter_data[j], 5);
						int n = CGlobal::minIndex(slide_filter_data[j], 5);
						CGlobal::force[j] = (slide_filter_data[j][0] + slide_filter_data[j][1] + slide_filter_data[j][2] + slide_filter_data[j][3] + slide_filter_data[j][4] - slide_filter_data[j][m] - slide_filter_data[j][n]) / 3.0;
						/******************************************/
					}

					for (int k = 0; k < 5; k++)
					{
						force_data[k][0] = force_data[k][1];
						force_data[k][1] = force_data[k][2];
						force_data[k][2] = CGlobal::force[k];

						vel_data[k][0] = (force_data[k][1] - force_data[k][0]) / (CGlobal::interval / 1000.0);
						vel_data[k][1] = (force_data[k][2] - force_data[k][1]) / (CGlobal::interval / 1000.0);

						CGlobal::velocity[k] = vel_data[k][0] ;
						CGlobal::velocity2[k] = vel_data[k][1] ;
						CGlobal::acceleration[k] = (vel_data[k][1] - vel_data[k][0]) / (CGlobal::interval / 1000.0);
					}

					CGlobal::calibrated = FALSE;
					js = 0;
				}

				else
				{
					js = 0;
				}
				
			}
	        		
		}

	}
	closesocket(sock);
	return 0;
}

UINT send_thd(LPVOID p)
{
	byte data[] = { 0xFE, 0x04, 0x00, 0x00, 0x00, 0x08, 0xE5, 0xC3 };//端口1-8
//	byte data[] = { 0xFE, 0x04, 0x00, 0x00, 0x00, 0x01, 0x25, 0xC5 };//端口1
//	byte data[] = { 0xFE, 0x04, 0x00, 0x01, 0x00, 0x01, 0x74, 0x05 };//端口2
//	byte data[] = { 0xFE, 0x04, 0x00, 0x02, 0x00, 0x01, 0x84, 0x05 };//端口3
//	byte data[] = { 0xFE, 0x04, 0x00, 0x03, 0x00, 0x01, 0xD5, 0xC5 };//端口4
//	byte data[] = { 0xFE, 0x04, 0x00, 0x04, 0x00, 0x01, 0x64, 0x04 };//端口5
//	byte data[] = { 0xFE, 0x04, 0x00, 0x01, 0x00, 0x05, 0x24, 0x06 };//端口1-5
	char *msg = (char*)data;
	while (1)
	{
		Sleep(CGlobal::interval);
		if (CGlobal::connected == TRUE)
		{
			if (send(sock, msg, 8, 0) == SOCKET_ERROR)
			{
				AfxMessageBox(L"发送失败!");
			}
		}
	}

	return 0;
}

void CConnectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnTimer(nIDEvent);
}
