#include "pch.h"

#include "Tile.h"
#include "Checker.h"
#include "Board.h"
#include "distance.h"
#include <vector>
#include <cmath>

MoveTypes Tile::InRange(Checker* checker) {
	std::vector<Checker*> checkers = this->board->checkers;

	for (int i = 0; i < checkers.size(); i++) {
		if (checkers[i]->position.first == this->position.first && checkers[i]->position.second == this->position.second) {
			return MoveTypes::Wrong;
		}
	}

	if (!checker->king && checker->player == 1 && this->position.second < checker->position.second) {
		return MoveTypes::Wrong;
	}
	if (!checker->king && checker->player == 2 && this->position.second > checker->position.second) {
		return MoveTypes::Wrong;
	}

	double distanceToChecker = distance(this->position.first, this->position.second, checker->position.first, checker->position.second);
	if (distanceToChecker == std::sqrt(2)) {
		return MoveTypes::RegularMove;
	}
	else if (distanceToChecker == 2 * std::sqrt(2)) {
		return MoveTypes::Jump;
	}
}

void Tile::SetPostion(int x, int y) {
	this->position.first = x;
	this->position.second = y;
}

std::string Tile::GetTextPosition() {
	char xPos = 'A' + this->position.first;
	char yPos = '1' + this->position.second;

	std::string val = std::string(1, xPos) + yPos;

	return val;
}
