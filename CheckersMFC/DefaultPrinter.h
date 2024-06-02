#pragma once
#include "Printer.h"
class DefaultPrinter :
    public Printer
{
	void DrawWhiteCell(CDC& dc, CRect rect) override;
	void DrawBlackCell(CDC& dc, CRect rect) override;
	void DrawAvailableToMoveCell(CDC& dc, CRect rect) override;

	void DrawWhiteChecker(CDC& dc, CRect rect) override;
	void DrawWhiteKingChecker(CDC& dc, CRect rect) override;
	virtual void DrawSelectedWhiteChecker(CDC& dc, CRect rect) override;
	virtual void DrawSelectedWhiteKingChecker(CDC& dc, CRect rect) override;

	void DrawBlackChecker(CDC& dc, CRect rect) override;
	void DrawBlackKingChecker(CDC& dc, CRect rect) override;
	virtual void DrawSelectedBlackChecker(CDC& dc, CRect rect) override;
	virtual void DrawSelectedBlackKingChecker(CDC& dc, CRect rect) override;
};

