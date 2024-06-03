#pragma once
#include "Board.h"
#include "CellType.h"
#include "BoardTile.h"
#include "Printer.h"
#include "EmptyCell.h"
#include "Checker.h"

#include <vector>
#include <string>
#include <utility>

class Tile;

class BoardMonteCarloEvaluator
{
private:
	Board* board;
	bool isVictory;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;

	std::pair<int, int> firsMoveCheckerPos, firsMoveTilePos;
	BoardTile startCheckerType;
public:
	bool jumpExist = false;
	bool continuousJump = false;
	int playerTurn = 1;

	BoardMonteCarloEvaluator(Board* board, int numIterations, BoardTile startCheckerType, std::pair<int, int> checkerPos, std::pair<int, int> tilePos);
	virtual ~BoardMonteCarloEvaluator();

	std::vector <std::vector<Tile*>> cells;
	std::vector <EmptyCell*> emptyCells;
	std::vector <Checker*> checkers;

	void EvaluateBoard();
	void Evaluate();
	int GetVictories() { return numVictories; };
	int GetLosses() { return numLosses; };
	int GetDraws() { return numDraws; };
	std::pair<int, int> GetFirstMoveCheckerPos() { return firsMoveCheckerPos; };
	std::pair<int, int> GetFirstMoveTilePos() { return firsMoveTilePos; };
};

