#pragma once
#include "Player.h"

struct CheckerMove {
	std::pair<int, int> checkerPos;
	std::pair<int, int> moveToPos;
};

class ComputerPlayer : public Player {
private:
	CheckerMove CalcMove();
public:
	ComputerPlayer();
	virtual ~ComputerPlayer();
	virtual bool MakeMove();
};