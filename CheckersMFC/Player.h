#pragma once
#include "Board.h"
#include <string>
#include "BoardTile.h"
#include "Checker.h"

class Player
{
protected:
	Board* board;
	CString name;
public:
	BoardTile cellType;
	Player();
	virtual ~Player();
	void SetupPlayer(CString name, BoardTile cellType);
	void SetBoard(Board* board);
	virtual bool MakeMove() = 0;
	CString GetName();
};

