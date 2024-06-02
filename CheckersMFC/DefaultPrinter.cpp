#include "pch.h"
#include "DefaultPrinter.h"

void DefaultPrinter::DrawWhiteCell(CPaintDC& dc, CRect rect) {
	CBrush brush;
	brush.CreateSolidBrush(RGB(230, 255, 230));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	brush.DeleteObject();
}

void DefaultPrinter::DrawBlackCell(CPaintDC& dc, CRect rect) {
	CBrush brush;
	brush.CreateSolidBrush(RGB(230, 255, 230));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	brush.DeleteObject();
}

void DefaultPrinter::DrawWhiteChecker(CPaintDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
}

void DefaultPrinter::DrawWhiteKingChecker(CPaintDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
}

void DefaultPrinter::DrawBlackChecker(CPaintDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
}

void DefaultPrinter::DrawBlackKingChecker(CPaintDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	HGDIOBJ oldBrush = dc.SelectObject(GetStockObject(HOLLOW_BRUSH));
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
}