#pragma once
#include "Board.h"
#include "Printer.h"
#include "Checker.h"

// CCheckersField

class CCheckersMFCDlg;
class CCheckersField : public CWnd
{
	DECLARE_DYNAMIC(CCheckersField)

public:
	CCheckersField();
	virtual ~CCheckersField();
	afx_msg void OnPaint();
	
protected:
	DECLARE_MESSAGE_MAP()

	
private:
	int fieldXSize = 0;
	int fieldYSize = 0;
	int nSelectedX;
	int nSelectedY;
	Printer* printer;

	Checker* selectedChecker = nullptr;
	bool bGameInProgress = false;
	CCheckersMFCDlg* gameParent;

	BOOL RegisterClass();
	//Board* board;
	CRect GetRectFromField(int x, int y);
	CPoint GetFieldPosition(CPoint point);
	void HighlightSelection(CDC& dc);
	void DrawChecker(Tile* tile, CDC& dc, CRect rect);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetGameParent(CCheckersMFCDlg* p);
	void SetGameInProgress(bool inProgress);
	bool CheckEndCondition();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


