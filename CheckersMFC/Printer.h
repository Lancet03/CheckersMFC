#pragma once
class Printer
{
public:
	virtual void DrawWhiteCell(CDC& dc, CRect rect) = 0;
	virtual void DrawBlackCell(CDC& dc, CRect rect) = 0;
	virtual void DrawAvailableToMoveCell(CDC& dc, CRect rect) = 0;

	virtual void DrawWhiteChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawWhiteKingChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawSelectedWhiteChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawSelectedWhiteKingChecker(CDC& dc, CRect rect) = 0;

	virtual void DrawBlackChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawBlackKingChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawSelectedBlackChecker(CDC& dc, CRect rect) = 0;
	virtual void DrawSelectedBlackKingChecker(CDC& dc, CRect rect) = 0;
};

