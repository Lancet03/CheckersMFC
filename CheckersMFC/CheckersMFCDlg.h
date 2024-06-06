
// CheckersMFCDlg.h : header file
//

#pragma once
#include "CCheckersField.h"
#include "Board.h"
#include "Player.h"

//class CCheckersField;

// CCheckersMFCDlg dialog
class CCheckersMFCDlg : public CDialogEx
{
// Construction
public:
	CCheckersMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHECKERSMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CCheckersField checkersField;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnBnClickedOpenstartup();
	
	void CreateBoard();
	void CreatePlayer1(CString name, int type);
	void CreatePlayer2(CString name, int type);

	Board* GetBoard() { return this->board; };
	Player* GetCurrentPlayer() { return this->currentPlayer; };
	Player* GetPlayer1() { return this->player1; };
	Player* GetPlayer2() { return this->player2; }
	void SetGameInProgress(bool inProgress);
	void ChangePlayer();
	void Cleanup();
private:
	Board* board;
	Player* player1;
	Player* player2;
	Player* currentPlayer;
	bool bGameInProcess = false;
	
	void UpdateName();
public:
	afx_msg void OnDestroy();
	CButton mStartStopButton;
	CString strPlayerTurn;
};
