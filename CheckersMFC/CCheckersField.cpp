// CCheckersField.cpp : implementation file
//

#include "pch.h"
#include "CheckersMFC.h"
#include "CCheckersField.h"

#define CHECKERSFIELD_CLASSNAME L"CheckersField"
#define FIELDNUMBERSPACE 20
// CCheckersField

IMPLEMENT_DYNAMIC(CCheckersField, CWnd)

CCheckersField::CCheckersField()
{
	this->board = new Board();
	this->fieldXSize = this->board->cells.size();
	this->fieldYSize = this->board->cells[0].size();
	this->nSelectedX = -1;
	this->nSelectedY = -1;
	this->RegisterClass();
}

CCheckersField::~CCheckersField()
{
}


BEGIN_MESSAGE_MAP(CCheckersField, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CCheckersField message handlers




BOOL CCheckersField::RegisterClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, CHECKERSFIELD_CLASSNAME, &wndcls))) {
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CHECKERSFIELD_CLASSNAME;
		if (!AfxRegisterClass(&wndcls)) {
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}


void CCheckersField::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	CRect rect;
	GetClientRect(&rect);

	CPen pen;
	HGDIOBJ oldPen;
	int fontWidth = 2;
	pen.CreatePen(PS_SOLID, fontWidth, RGB(0, 0, 0));
	oldPen = dc.SelectObject(pen);
	dc.SetTextColor(RGB(255, 0, 0));
	dc.SetTextAlign(TA_TOP | TA_LEFT);
	dc.SetBkMode(TRANSPARENT);

	/*int fieldXSize = this->board->cells.size();
	int fieldYSize = this->board->cells[0].size();*/

	int hPartSize = (rect.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rect.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;
	this->HighlightSelection(dc);
	for (int i = 0; i < this->fieldXSize; i++) {
		CString st;
		std::string str;

		char xCoord = 'A' + i;
		st = xCoord;
		dc.TextOutW(FIELDNUMBERSPACE + hPartSize / 2 + i * hPartSize - fontWidth, 0, st);
		dc.TextOutW(FIELDNUMBERSPACE + hPartSize / 2 + i * hPartSize - fontWidth, rect.bottom - FIELDNUMBERSPACE + fontWidth, st);

		int yCoord = i + 1;
		str = std::to_string(yCoord);
		st = str.c_str();
		dc.TextOutW(0, FIELDNUMBERSPACE + vPartSize / 2 + i * vPartSize - fontWidth * 3, st);
		dc.TextOutW(rect.right - FIELDNUMBERSPACE + fontWidth * 3, FIELDNUMBERSPACE + vPartSize / 2 + i * vPartSize - fontWidth * 3, st);
	}
	for (int i = 0; i < this->fieldXSize + 1; i++) {
		dc.MoveTo(FIELDNUMBERSPACE + i * hPartSize, FIELDNUMBERSPACE);
		dc.LineTo(FIELDNUMBERSPACE + i * hPartSize, this->fieldYSize * vPartSize + FIELDNUMBERSPACE);
	}
	for (int i = 0; i < this->fieldYSize + 1; i++) {
		dc.MoveTo(FIELDNUMBERSPACE, i * vPartSize + FIELDNUMBERSPACE);
		dc.LineTo(FIELDNUMBERSPACE + (this->fieldXSize)*hPartSize, i * vPartSize + FIELDNUMBERSPACE);
	}

	dc.SelectObject(oldPen);
	pen.DeleteObject();
}

CRect CCheckersField::GetRectFromField(int x, int y) {
	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rectWnd.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;
	rect.left = FIELDNUMBERSPACE + x * hPartSize + 1;
	rect.top = FIELDNUMBERSPACE + y * vPartSize + 1;
	rect.right = FIELDNUMBERSPACE + ((x + 1) * hPartSize) - 1;
	rect.bottom = FIELDNUMBERSPACE + ((y + 1) * vPartSize) - 1;
	// TODO: Добавьте сюда код реализации.
	return rect;
}

void CCheckersField::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//int x, y;
	CPoint p = this->GetFieldPosition(point);
	if ((this->nSelectedX != p.x) || (this->nSelectedY != p.y)) {
		this->nSelectedX = p.x;
		this->nSelectedY = p.y;
		this->Invalidate();
	}
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->m_hWnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;
	TrackMouseEvent(&tme);
	CWnd::OnMouseMove(nFlags, point);
}


void CCheckersField::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	this->nSelectedX = -1;
	this->nSelectedY = -1;
	this->Invalidate();

	CWnd::OnMouseLeave();
}

CPoint CCheckersField::GetFieldPosition(CPoint point) {
	CRect rect;
	GetClientRect(&rect);
	CPoint position;
	int hPartSize = (rect.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rect.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;
	for (int i = 0; i < this->fieldXSize; i++) {
		if ((point.x > FIELDNUMBERSPACE + i * hPartSize) && (point.x < FIELDNUMBERSPACE + (i + 1) * hPartSize))
			position.x = i;
	}
	for (int i = 0; i < this->fieldYSize; i++) {
		if ((point.y > FIELDNUMBERSPACE + i * vPartSize) && (point.y < FIELDNUMBERSPACE + (i + 1) * vPartSize))
			position.y = i;
	}

	return position;
}

void CCheckersField::HighlightSelection(CPaintDC& dc) {
	if ((this->nSelectedX < 0) || (this->nSelectedY < 0)) {
		return;
	}
	CRect rect = this->GetRectFromField(nSelectedX, nSelectedY);
	CBrush brush;
	brush.CreateSolidBrush(RGB(230, 255, 230));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	brush.DeleteObject();
}