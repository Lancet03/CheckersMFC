#pragma once
#include "Board.h"
#include "Player.h"
#include <string>

class HumanPlayer : public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	bool MakeMove();
};