#pragma once
#include "Printer.h"
class DefaultPrinter :
    public Printer
{
	void DrawWhiteCell(CPaintDC& dc, CRect rect) override;
	void DrawBlackCell(CPaintDC& dc, CRect rect) override;
	void DrawWhiteChecker(CPaintDC& dc, CRect rect) override;
	void DrawWhiteKingChecker(CPaintDC& dc, CRect rect) override;
	void DrawBlackChecker(CPaintDC& dc, CRect rect) override;
	void DrawBlackKingChecker(CPaintDC& dc, CRect rect) override;
};

