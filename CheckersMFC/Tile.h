#pragma once
#include <utility>
#include <string>
#include "MoveTypes.h"

class Board;
class Checker;

class Tile
{
protected:
	Board* board;
public:
	Tile() {};
	virtual ~Tile() {};
	std::pair<int, int> position;
	MoveTypes InRange(Checker* checker);
	void SetPostion(int x, int y);
};

