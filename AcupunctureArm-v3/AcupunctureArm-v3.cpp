
// AcupunctureArm-v3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "AcupunctureArm-v3.h"
#include "MainFrm.h"

#include "AcupunctureArm-v3Doc.h"
#include "AcupunctureArm-v3View.h"
#include "ConnectDlg.h"
#include "CalibrationDlg.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAcupunctureArmv3App

BEGIN_MESSAGE_MAP(CAcupunctureArmv3App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CAcupunctureArmv3App::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
//	ON_COMMAND(ID_32771, &CAcupunctureArmv3App::On32771)
ON_COMMAND(ID_START, &CAcupunctureArmv3App::OnStart)
ON_COMMAND(ID_START_CALIBRATION, &CAcupunctureArmv3App::OnStartCalibration)
ON_COMMAND(ID_INFORMATION_DISPLAY, &CAcupunctureArmv3App::OnInformationDisplay)
ON_UPDATE_COMMAND_UI(ID_INFORMATION_DISPLAY, &CAcupunctureArmv3App::OnUpdateInformationDisplay)
END_MESSAGE_MAP()


// CAcupunctureArmv3App construction

CAcupunctureArmv3App::CAcupunctureArmv3App()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AcupunctureArm-v3.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CAcupunctureArmv3App object

CAcupunctureArmv3App theApp;

// CAcupunctureArmv3App initialization

BOOL CAcupunctureArmv3App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	InfoDisplay = FALSE;


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAcupunctureArmv3Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAcupunctureArmv3View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CAcupunctureArmv3App::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CAcupunctureArmv3App message handlers


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

// App command to run the dialog
void CAcupunctureArmv3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAcupunctureArmv3App message handlers





//void CAcupunctureArmv3App::On32771()
//{
//	// TODO: Add your command handler code here
//}


void CAcupunctureArmv3App::OnStart()
{
	// TODO: Add your command handler code here
	CConnectDlg dlg;
	dlg.DoModal();
}


void CAcupunctureArmv3App::OnStartCalibration()
{
	// TODO: Add your command handler code here
	CCalibrationDlg dlg;
	if (CGlobal::connected)
	{
		dlg.DoModal();
	}
	else
		AfxMessageBox(L"ÍøÂçÎ´Á¬½Ó£¡");
}


void CAcupunctureArmv3App::OnInformationDisplay()
{
	// TODO: Add your command handler code here
	if (!InfoDisplay)
	{ 
		myThread = new CUIThread();
		myThread->CreateThread();
		InfoDisplay = TRUE;
	}
	else
	{
		myThread->ShowWindow(InfoDisplay);
	}

	m_pMainWnd->GetMenu()->GetSubMenu(1)->EnableMenuItem(ID_INFORMATION_DISPLAY, MF_BYCOMMAND | MF_DISABLED);
}


void CAcupunctureArmv3App::OnUpdateInformationDisplay(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here

}
