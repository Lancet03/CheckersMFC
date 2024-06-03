#pragma once
#include "afxdialogex.h"
#include "CheckersMFCDlg.h"


// CStartupDialog dialog

class CStartupDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CStartupDialog)

public:
	CStartupDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CStartupDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeCombotypeplayer1();
	virtual BOOL OnInitDialog();
	CString strPlayerName1;
	CString strPlayerName2;
	CComboBox mTypePlayer2;
	CComboBox mTypePlayer1;
	afx_msg void OnBnClickedStartbutton();

	void SetDlgParent(CCheckersMFCDlg* p);
	private:
	CCheckersMFCDlg* dlgParent;
};
