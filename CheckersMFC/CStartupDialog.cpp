// CStartupDialog.cpp : implementation file
//

#include "pch.h"
#include "CheckersMFC.h"
#include "afxdialogex.h"
#include "CStartupDialog.h"


// CStartupDialog dialog

IMPLEMENT_DYNAMIC(CStartupDialog, CDialogEx)

CStartupDialog::CStartupDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STARTDIALOG, pParent)
	, strPlayerName1(_T(""))
	, strPlayerName2(_T(""))
{

}

CStartupDialog::~CStartupDialog()
{
}

void CStartupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER1, strPlayerName1);
	DDX_Text(pDX, IDC_EDITNAMEPLAYER2, strPlayerName2);

	DDX_Control(pDX, IDC_COMBOTYPEPLAYER1, mTypePlayer1);
	DDX_Control(pDX, IDC_COMBOTYPEPLAYER2, mTypePlayer2);
}


BEGIN_MESSAGE_MAP(CStartupDialog, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CStartupDialog::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBOTYPEPLAYER1, &CStartupDialog::OnCbnSelchangeCombotypeplayer1)
	
	ON_BN_CLICKED(IDC_STARTBUTTON, &CStartupDialog::OnBnClickedStartbutton)
END_MESSAGE_MAP()


// CStartupDialog message handlers


void CStartupDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void CStartupDialog::OnCbnSelchangeCombotypeplayer1()
{
	// TODO: Add your control notification handler code here
}


BOOL CStartupDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	this->mTypePlayer1.SetCurSel(0);
	this->mTypePlayer2.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStartupDialog::OnBnClickedStartbutton()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ((this->strPlayerName1 == L"") || (this->strPlayerName2 == L"")) {
		AfxMessageBox(L"Имя игрока не может быть пустым");
		return;
	}

	this->EndDialog(IDOK);
}

void CStartupDialog::SetDlgParent(CCheckersMFCDlg* p) {
	this->dlgParent = p;
}

void CStartupDialog::CreateBoard() {

}

void CStartupDialog::CreatePlayer1(CString name, int type) {

}

void CStartupDialog::CreatePlayer2(CString name, int type) {

}
