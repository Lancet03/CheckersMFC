#include "pch.h"

#include "EmptyCell.h"
#include "Board.h"
#include <vector>

EmptyCell::EmptyCell(int row, int col, Board* board) {
	this->position.first = col;
	this->position.second = row;
	this->board = board;
}
