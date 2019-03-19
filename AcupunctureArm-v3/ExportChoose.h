#pragma once


// CExportChoose dialog

class CExportChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CExportChoose)

public:
	CExportChoose(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExportChoose();

// Dialog Data
	enum { IDD = IDD_DIALOG_EXPORT_CHOOSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
