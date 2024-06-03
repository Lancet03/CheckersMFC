#pragma once
#include "Board.h"
#include "Player.h"

class Manager
{
private:
	Board* board;
	Player* p1;
	Player* p2;
	Player* currentPlayer;
	bool isGameFinished = false;
public:
	Manager();
	virtual ~Manager();
	bool Init();
	void ShowBoard();
	void MakeMove();
	bool IsGameFinished();
};

