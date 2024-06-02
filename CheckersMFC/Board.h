#pragma once

#include "BoardTile.h"
//#include "Printer.h"
#include "EmptyCell.h"
#include "Checker.h"

#include <vector>
#include <string>
#include <utility>

class Tile;

struct Score {
	int player1 = 0;
	int player2 = 0;
};

class Board
{
private:
	std::vector <std::vector<BoardTile>> tiles{
		{Empty, White, Empty, White, Empty, White, Empty, White},
		{White, Empty, White, Empty, White, Empty, White, Empty},
		{Empty, White, Empty, White, Empty, White, Empty, White},
		{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
		{Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty},
		{Black, Empty, Black, Empty, Black, Empty, Black, Empty},
		{Empty, Black, Empty, Black, Empty, Black, Empty, Black},
		{Black, Empty, Black, Empty, Black, Empty, Black, Empty}
	};

	//Printer printer;

	bool isVictory;
public:
	Score score;
	bool jumpExist = false;
	bool continuousJump = false;
	int playerTurn = 1;

	Board();
	Board(Board* board);
	virtual ~Board();

	std::vector <std::vector<Tile*>> cells;
	std::vector <EmptyCell*> emptyCells;
	std::vector <Checker*> checkers;
	
	void Show();
	bool CheckLegal(int xpos, int ypos);
	bool CheckEndCondition();
	bool IsVictory();

	void PrintCell(int row, int col);

	bool IsValidPlaceToMove(int row, int col);
	void ChangePlayerTurn();
	int CheckIfSomeoneWon();
	void Clear();

	void CheckIfJumpExists();
	bool CheckIfPositionOnBoard(int x, int y);
	bool CheckIfPositionIsCorrect(std::string position);
	bool CheckIfCheckerOnPosition(int x, int y);
	bool CheckIfEmptyCellOnPosition(int x, int y);

	Checker* GetChecker(int x, int y);
	EmptyCell* GetEmptyCell(int x, int y);
	void RemoveChecker(Checker* checker);

	std::pair<int, int> ParsePosition(std::string position);

	Checker* GetSelectedChecker();
	bool CheckIfPlayerHasSelectedCheckers();
	void DeselectAllCheckers();

	std::vector<Checker*> GetCheckersThatCanMove();

	Score GetScore() { return this->score; };
};

