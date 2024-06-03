#pragma once
#include "Player.h"
#include "Checker.h"
#include <utility>

class RandomPlayer : public Player {
public:
	RandomPlayer();
	virtual ~RandomPlayer();
	virtual bool MakeMove();
	bool MakeFirstMove(std::pair<int, int> checkerPos, std::pair<int, int> moveToTilePos);
	Checker* SelectChecker(std::pair<int, int> checkerPos);
	bool SelectWhereCheckerWillGo(Checker* selectedChecker, std::pair<int, int> moveToTilePos);
};