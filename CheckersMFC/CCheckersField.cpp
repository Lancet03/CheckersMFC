// CCheckersField.cpp : implementation file
//

#include "pch.h"
#include "CheckersMFC.h"
#include "CCheckersField.h"
#include "DefaultPrinter.h"
#include "Checker.h"
#include "EmptyCell.h"

#include <typeinfo>
#include <vector>

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

	this->printer = new DefaultPrinter();
	this->RegisterClass();
}

CCheckersField::~CCheckersField()
{
}


BEGIN_MESSAGE_MAP(CCheckersField, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
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

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(&rect, RGB(255, 255, 255));

	CPen pen;
	HGDIOBJ oldPen;
	int fontWidth = 2;
	pen.CreatePen(PS_SOLID, fontWidth, RGB(0, 0, 0));
	oldPen = memDC.SelectObject(pen);
	memDC.SetTextColor(RGB(23, 23, 23));
	memDC.SetTextAlign(TA_TOP | TA_LEFT);
	memDC.SetBkMode(TRANSPARENT);

	int hPartSize = (rect.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rect.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;

	for (int i = 0; i < this->fieldXSize; i++) {
		CString st;
		std::string str;

		char xCoord = 'A' + i;
		st = xCoord;
		memDC.TextOutW(FIELDNUMBERSPACE + hPartSize / 2 + i * hPartSize - fontWidth, 0, st);
		memDC.TextOutW(FIELDNUMBERSPACE + hPartSize / 2 + i * hPartSize - fontWidth, rect.bottom - FIELDNUMBERSPACE + fontWidth, st);

		int yCoord = i + 1;
		str = std::to_string(yCoord);
		st = str.c_str();
		memDC.TextOutW(0, FIELDNUMBERSPACE + vPartSize / 2 + i * vPartSize - fontWidth * 3, st);
		memDC.TextOutW(rect.right - FIELDNUMBERSPACE + fontWidth * 3, FIELDNUMBERSPACE + vPartSize / 2 + i * vPartSize - fontWidth * 3, st);
	}


	std::vector<EmptyCell*> availableToMoveCells = {};
	if (this->selectedChecker != nullptr) {
		availableToMoveCells = this->selectedChecker->GetTilesAvailable();
	}
	for (int row = 0; row < this->fieldYSize; row++) {
		for (int col = 0; col < this->fieldXSize; col++) {
			CRect cellRect = this->GetRectFromField(col, row);

			bool cellPrinted = false;
			for (int i = 0; i < availableToMoveCells.size(); i++) {
				EmptyCell* availableToMoveCell = availableToMoveCells[i];
				if (availableToMoveCell->position.first == col && availableToMoveCell->position.second == row) {
					this->printer->DrawAvailableToMoveCell(memDC, cellRect);
					cellPrinted = true;
					break;
				}
			}

			if (!cellPrinted)
			{
				if ((row + col) % 2 == 0) {
					this->printer->DrawWhiteCell(memDC, cellRect);
				}
				else {
					this->printer->DrawBlackCell(memDC, cellRect);
				}
			}
		}
	}

	this->HighlightSelection(memDC);

	for (int row = 0; row < this->fieldYSize; row++) {
		for (int col = 0; col < this->fieldXSize; col++) {
			CRect cellRect = this->GetRectFromField(col, row);
			this->DrawChecker(this->board->cells[row][col], memDC, cellRect);
		}
	}

	memDC.SelectObject(oldPen);
	pen.DeleteObject();

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
}

void CCheckersField::DrawChecker(Tile* tile, CDC& dc, CRect rect) {
	if (typeid(*tile) == typeid(Checker)) {
		Checker* checker = (Checker*)tile;
		if (checker->player == White) {
			if (checker->king) {
				if (checker->selected) {
					this->printer->DrawSelectedWhiteKingChecker(dc, rect);
				}
				else {
					this->printer->DrawWhiteKingChecker(dc, rect);
				}
			}
			else {
				if (checker->selected) {
					this->printer->DrawSelectedWhiteChecker(dc, rect);
				}
				else {
					this->printer->DrawWhiteChecker(dc, rect);
				}
			}
		}
		else if (checker->player == Black) {
			if (checker->king) {
				if (checker->selected) {
					this->printer->DrawSelectedBlackKingChecker(dc, rect);
				}
				else {
					this->printer->DrawBlackKingChecker(dc, rect);
				}
			}
			else {
				if (checker->selected) {
					this->printer->DrawSelectedBlackChecker(dc, rect);
				}
				else {
					this->printer->DrawBlackChecker(dc, rect);
				}
			}
		}
	}
}

CRect CCheckersField::GetRectFromField(int x, int y) {
	CRect rect;
	CRect rectWnd;
	GetClientRect(&rectWnd);
	int hPartSize = (rectWnd.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rectWnd.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;
	rect.left = FIELDNUMBERSPACE + x * hPartSize;
	rect.top = FIELDNUMBERSPACE + y * vPartSize;
	rect.right = FIELDNUMBERSPACE + ((x + 1) * hPartSize);
	rect.bottom = FIELDNUMBERSPACE + ((y + 1) * vPartSize);
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
	position.x = -1;
	position.y = -1;

	int hPartSize = (rect.right - 2 * FIELDNUMBERSPACE) / this->fieldXSize;
	int vPartSize = (rect.bottom - 2 * FIELDNUMBERSPACE) / this->fieldYSize;
	for (int i = 0; i < this->fieldXSize; i++) {
		if ((point.x >= FIELDNUMBERSPACE + i * hPartSize) && (point.x < FIELDNUMBERSPACE + (i + 1) * hPartSize))
		{
			position.x = i;
		}
	}
	for (int i = 0; i < this->fieldYSize; i++) {
		if ((point.y >= FIELDNUMBERSPACE + i * vPartSize) && (point.y < FIELDNUMBERSPACE + (i + 1) * vPartSize))
		{
			position.y = i;
		}
	}

	return position;
}

void CCheckersField::HighlightSelection(CDC& dc) {
	if ((this->nSelectedX < 0) || (this->nSelectedY < 0)) {
		return;
	}
	CRect rect = this->GetRectFromField(nSelectedX, nSelectedY);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(230, 255, 230));
	HGDIOBJ oldPen = dc.SelectObject(pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(230, 255, 230));
	HGDIOBJ oldBrush = dc.SelectObject(brush);
	dc.Rectangle(rect);
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
	pen.DeleteObject();
	brush.DeleteObject();
}

BOOL CCheckersField::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}


void CCheckersField::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	int x, y;
	CRect rect;
	GetClientRect(&rect);


	if (point.x > FIELDNUMBERSPACE && point.y > FIELDNUMBERSPACE && point.x < rect.right - FIELDNUMBERSPACE && point.y < rect.bottom - FIELDNUMBERSPACE) {
		CPoint p = this->GetFieldPosition(point);

		if (this->selectedChecker != nullptr) {
			EmptyCell* chosenCell = this->board->GetEmptyCell(p.x, p.y);

			if (!this->board->continuousJump) {
				this->board->DeselectAllCheckers();
			}

			if (chosenCell == nullptr) {
				this->board->DeselectAllCheckers();
				this->selectedChecker = nullptr;
			}
			else {
				MoveTypes inRange = chosenCell->InRange(selectedChecker);
				if (inRange != MoveTypes::Wrong) {
					if (inRange == MoveTypes::Jump) {
						if (selectedChecker->OpponentJump(chosenCell->position.first, chosenCell->position.second)) {
							selectedChecker->Move(chosenCell->position.first, chosenCell->position.second);
							if (selectedChecker->CanJumpAny()) {
								selectedChecker->selected = true;
								this->board->continuousJump = true;
							}
							else {
								this->board->ChangePlayerTurn();
								this->selectedChecker = nullptr;
							}
							//return true;
						}
					}
					else if (inRange == MoveTypes::RegularMove && !this->board->jumpExist) {
						if (!selectedChecker->CanJumpAny()) {
							selectedChecker->Move(chosenCell->position.first, chosenCell->position.second);
							this->board->ChangePlayerTurn();
							this->selectedChecker = nullptr;
							//return true;
						}
					}
				}
			}
		}
		else {
			Checker* chosenChecker = nullptr;
			bool hasSelectedChecker = this->board->CheckIfPlayerHasSelectedCheckers();

			if (hasSelectedChecker) {
				chosenChecker = this->board->GetSelectedChecker();
			}
			else {
				chosenChecker = this->board->GetChecker(p.x, p.y);
			}

			if ((!this->board->continuousJump || hasSelectedChecker) && chosenChecker != nullptr && chosenChecker->allowedToMove) {
				this->board->DeselectAllCheckers();
				this->selectedChecker = chosenChecker;
				this->selectedChecker->selected = true;
			}
		}

		this->Invalidate();
	}

	CWnd::OnLButtonDown(nFlags, point);
}
