
// CheckersMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CheckersMFC.h"
#include "CheckersMFCDlg.h"
#include "afxdialogex.h"
#include "CStartupDialog.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "BoardTile.h"
#include "CCheckersField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCheckersMFCDlg dialog

CCheckersMFCDlg::CCheckersMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHECKERSMFC_DIALOG, pParent)
	, strPlayerTurn(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	this->board = nullptr;
	this->player1 = nullptr;
	this->player2 = nullptr;
	this->currentPlayer = nullptr;
}

void CCheckersMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECKERSFIELD, this->checkersField);
	DDX_Control(pDX, IDC_OPENSTARTUP, mStartStopButton);
	DDX_Text(pDX, IDC_CURRENTPLAYER, strPlayerTurn);
}

BEGIN_MESSAGE_MAP(CCheckersMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_BN_CLICKED(IDC_OPENSTARTUP, &CCheckersMFCDlg::OnBnClickedOpenstartup)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCheckersMFCDlg message handlers

BOOL CCheckersMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->checkersField.SetGameParent(this);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CFont font;
	font.CreateFont(
		50,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));                 // lpszFacename

	GetDlgItem(IDC_CURRENTPLAYER)->SetFont(&font);
	
	this->OnBnClickedOpenstartup();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckersMFCDlg::OnPaint()
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
HCURSOR CCheckersMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCheckersMFCDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
}


void CCheckersMFCDlg::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseLeave();
}


void CCheckersMFCDlg::OnBnClickedOpenstartup()
{
	// TODO: Add your control notification handler code here
	

	if (this->bGameInProcess) {
		//this->Cleanup();
		this->SetGameInProgress(false);
		this->Invalidate();
	}
	else {
		CStartupDialog sdlg;
		sdlg.SetDlgParent(this);
		int nRes = sdlg.DoModal();

		if (nRes == IDOK) {
			this->currentPlayer = this->player1;
			this->SetGameInProgress(true);
			this->UpdateName();
			this->Invalidate();
		}
		else if (nRes == IDCANCEL) {
			if (this->board == nullptr) {
				EndDialog(0);
			}

			this->SetGameInProgress(true);
			this->Invalidate();
		}
	}
}


void CCheckersMFCDlg::CreateBoard() {
	this->board = new Board();
	this->checkersField.InitializeField();
}

void CCheckersMFCDlg::CreatePlayer1(CString name, int type) {
	if (type == 0) {
		this->player1 = new HumanPlayer();
	}
	else {
		this->player1 = new ComputerPlayer();
	}
	this->player1->SetupPlayer(name, BoardTile::White);
	this->player1->SetBoard(this->board);

}

void CCheckersMFCDlg::CreatePlayer2(CString name, int type) {
	if (type == 0) {
		this->player2 = new HumanPlayer();
	}
	else {
		this->player2 = new ComputerPlayer();
	}
	this->player2->SetupPlayer(name, BoardTile::Black);
	this->player2->SetBoard(this->board);
}

void CCheckersMFCDlg::SetGameInProgress(bool inProgress) {
	this->bGameInProcess = inProgress;
	this->checkersField.SetGameInProgress(inProgress);
	if (inProgress) {
		this->mStartStopButton.SetWindowTextW(L"Остановить");
	}
	else {
		this->mStartStopButton.SetWindowTextW(L"Запустить");

		//this->Cleanup();
	}
}

void CCheckersMFCDlg::Cleanup() {
	if (this->player1 != nullptr) {
		delete this->player1;
		this->player1 = nullptr;
	}
	if (this->player2 != nullptr) {
		delete this->player2;
		this->player2 = nullptr;
	}
	if (this->board != nullptr) {
		delete this->board;
		this->board = nullptr;
	}
	this->currentPlayer = nullptr;
	this->checkersField.Cleanup();
}


void CCheckersMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// TODO: Add your message handler code here
	this->Cleanup();
}

void CCheckersMFCDlg::UpdateName() {
	CString str;
	str.Format(L"Ход игрока: %s", this->currentPlayer->GetName());
	this->strPlayerTurn = str;
	UpdateData(FALSE);
}

void CCheckersMFCDlg::ChangePlayer() {
	if (this->currentPlayer != this->player1) {
		this->currentPlayer = this->player1;
	}
	else {
		this->currentPlayer = this->player2;
	}

	this->UpdateName();
}