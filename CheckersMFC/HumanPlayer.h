#pragma once
#include "Board.h"
#include "Player.h"
#include <string>

class HumanPlayer : public Player {
	Checker* SelectChecker();
	bool SelectWhereCheckerWillGo(Checker* selectedChecker);
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	bool MakeMove();
};