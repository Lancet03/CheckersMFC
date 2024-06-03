#pragma once
#include "Board.h"
#include "Printer.h"
#include "Checker.h"
//#include "CheckersMFCDlg.h"

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

	CCheckersMFCDlg* gameParent;
private:
	int fieldXSize;
	int fieldYSize;
	int nSelectedX;
	int nSelectedY;
	Printer* printer;

	Checker* selectedChecker = nullptr;



	BOOL RegisterClass();
	Board* board;
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
};


