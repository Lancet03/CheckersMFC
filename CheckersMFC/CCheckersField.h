#pragma once
#include "Board.h"

// CCheckersField

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
	int fieldXSize;
	int fieldYSize;
	int nSelectedX;
	int nSelectedY;
	BOOL RegisterClass();
	Board* board;
	CRect GetRectFromField(int x, int y);
	CPoint GetFieldPosition(CPoint point);
	void HighlightSelection(CPaintDC& dc);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


