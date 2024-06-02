#pragma once
class Printer
{
public:
	virtual void DrawWhiteCell(CPaintDC& dc, CRect rect) = 0;
	virtual void DrawBlackCell(CPaintDC& dc, CRect rect) = 0;
	virtual void DrawWhiteChecker(CPaintDC& dc, CRect rect) = 0;
	virtual void DrawWhiteKingChecker(CPaintDC& dc, CRect rect) = 0;
	virtual void DrawBlackChecker(CPaintDC& dc, CRect rect) = 0;
	virtual void DrawBlackKingChecker(CPaintDC& dc, CRect rect) = 0;
};

