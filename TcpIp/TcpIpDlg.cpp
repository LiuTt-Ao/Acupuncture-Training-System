
// TcpIpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcpIp.h"
#include "TcpIpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


SOCKET sock;
UINT recv_thd(LPVOID p);
int revNum = 0, sendNum = 0;
void hex_to_str(char *ptr, char *buf);
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTcpIpDlg dialog



CTcpIpDlg::CTcpIpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTcpIpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTcpIpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CTcpIpDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CTcpIpDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CTcpIpDlg message handlers

BOOL CTcpIpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CIPAddressCtrl *ip = (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS);
	ip->SetAddress(192, 168, 16, 254);

	CEdit *port = (CEdit*)GetDlgItem(IDC_PORT);
	port->SetWindowTextW(L"8080");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTcpIpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcpIpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTcpIpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTcpIpDlg::OnBnClickedButtonConnect()
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
			AfxBeginThread(&recv_thd, 0);
			GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowTextW(L"已连接");
		}
	}
}


void CTcpIpDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here
	CString sendData;
	CString num,str;
	((CEdit*)GetDlgItem(IDC_SEND))->GetWindowTextW(sendData);
//	msg = (char*)(LPCTSTR)sendData;
	byte data[] = { 0xFE, 0x04, 0x00, 0x00, 0x00, 0x01, 0x25, 0xC5 };
	char *msg = (char*)data;
//	unsigned char *bits = new unsigned char[];
//	String2HexString(msg, bits);
	if (send(sock, msg, 8, 0) == SOCKET_ERROR)
	{
		MessageBox(L"发送失败!");
	}
	else
	{
		sendNum++;
		num.Format(L"SendNum:%d,RevNum:%d", sendNum,revNum);
		((CEdit*)GetDlgItem(IDC_NUM))->SetWindowTextW(num);
		str.Format(L"%s", msg);
		((CEdit*)GetDlgItem(IDC_RECIVE))->SetWindowTextW(str);
	}
}


UINT recv_thd(LPVOID p)
{
	int res;
	char msg[100], hex_msg[100];
	CString str;
	CString num;
	while (1)
	{
		if ((res = recv(sock, msg, 100, 0)) <= 0)
		{
			AfxMessageBox(L"连接断开！");
			break;
		}
		else
		{
			revNum++;
			msg[res] = '\0';
			hex_to_str(hex_msg, msg);
			num.Format(L"SendNum:%d,RevNum:%d", sendNum, revNum);
			AfxGetApp()->m_pMainWnd->SetDlgItemTextW(IDC_NUM, num);
			str.Format(L"%s", hex_msg);
			AfxGetApp()->m_pMainWnd->SetDlgItemTextW(IDC_RECIVE, str);
		}
		

	}
	closesocket(sock);
	return 0;
}

void hex_to_str(char *ptr, char *buf)//hex格式转化成字符串显示
{
	int i, j, k;

	for (i = 0; i<8; i++) {
		if (0 == (i % 16)) {
			//sprintf(ptr, "%08x", i);
			sprintf(ptr, "", i);
			sprintf(ptr, "%s %02x", ptr, (unsigned char)buf[i]);
		}
		else if (15 == (i % 16)) {
			sprintf(ptr, "%s %02x", ptr, (unsigned char)buf[i]);
			sprintf(ptr, "%s  ", ptr);
			for (j = i - 15; j <= i; j++) {
				sprintf(ptr, "%s%c", ptr, ('!'<buf[j] && buf[j] <= '~') ? buf[j] : '.');
			}
		}
		else {
			sprintf(ptr, "%s %02x", ptr, (unsigned char)buf[i]);
		}
	}
	if (0 != (i % 16)) {
		k = 16 - (i % 16);
		for (j = 0; j<k; j++) {
			sprintf(ptr, "%s   ", ptr);
		}
		sprintf(ptr, "%s  ", ptr);
		k = 16 - k;
		for (j = i - k; j<i; j++) {
			sprintf(ptr, "%s%c", ptr, ('!'<buf[j] && buf[j] <= '~') ? buf[j] : '.');
		}
	}
}