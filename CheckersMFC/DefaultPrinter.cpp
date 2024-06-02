#include "pch.h"
#include "DefaultPrinter.h"

void DefaultPrinter::DrawWhiteCell(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID,	0, RGB(249, 241, 165));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(249, 241, 165));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawBlackCell(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(19, 161, 14));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(19, 161, 14));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawAvailableToMoveCell(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(19, 255, 14));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(19, 161, 14));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawWhiteChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(242, 242, 242));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawWhiteKingChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(242, 242, 242));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawSelectedWhiteChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(50, 50, 50));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(240, 240, 240));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
	
}

void DefaultPrinter::DrawSelectedWhiteKingChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(240, 240, 240));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}


void DefaultPrinter::DrawBlackChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(23, 23, 23));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(23, 23, 23));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawBlackKingChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(23, 23, 23));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(23, 23, 23));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawSelectedBlackChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(50, 50, 50));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(23, 23, 23));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void DefaultPrinter::DrawSelectedBlackKingChecker(CDC& dc, CRect rect) {
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 30, 30));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Ellipse(rect.left + 4, rect.top + 4, rect.right - 4, rect.bottom - 4);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}