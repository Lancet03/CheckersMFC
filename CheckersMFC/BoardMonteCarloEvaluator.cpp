#include "pch.h"

#include "BoardMonteCarloEvaluator.h"
#include "RandomPlayer.h"

#include <iostream>

BoardMonteCarloEvaluator::BoardMonteCarloEvaluator(Board* board, int numIterations, BoardTile startCheckerType, std::pair<int, int> firsMoveCheckerPos, std::pair<int, int> firsMoveTilePos) {
	this->board = board;
	this->numGames = numIterations;
	this->numVictories = 0;
	this->numLosses = 0;
	this->firsMoveCheckerPos = firsMoveCheckerPos;
	this->firsMoveTilePos = firsMoveTilePos;
	this->startCheckerType = startCheckerType;
}

BoardMonteCarloEvaluator::~BoardMonteCarloEvaluator() {

}

void BoardMonteCarloEvaluator::EvaluateBoard() {
	int maxMovesCount = 50;

	Board* b = new Board(this->board);
	RandomPlayer* p1 = new RandomPlayer();
	RandomPlayer* p2 = new RandomPlayer();
	RandomPlayer* currentPlayer;
	bool bGameFinished = false;

	p1->SetupPlayer(L"RandomP1", BoardTile::White);
	p2->SetupPlayer(L"RandomP2", BoardTile::Black);
	p1->SetBoard(b);
	p2->SetBoard(b);
	currentPlayer = (this->startCheckerType == BoardTile::White) ? p1 : p2;

	if (!currentPlayer->MakeFirstMove(this->firsMoveCheckerPos, this->firsMoveTilePos)) {
		std::cout << "First Move Error!!!" << std::endl;
	}
	currentPlayer = (currentPlayer == p1) ? p2 : p1;

	if (b->CheckEndCondition()) {
		if (b->IsVictory()) {
			if (currentPlayer == p2) {
				numLosses++;
			}
			else {
				numVictories++;
			}
		}
		else {
			numDraws++;
		}
		delete p1;
		delete p2;
		delete b;

		bGameFinished = true;
		return;
	}

	int movesCount = 0;

	while (!bGameFinished && movesCount < maxMovesCount) {
		//while (!currentPlayer->MakeMove());
		currentPlayer->MakeMove();

		if (b->CheckEndCondition()) {
			if (b->IsVictory()) {
				if (currentPlayer == p2) {
					numVictories++;
				}
				else {
					numLosses++;
				}
			}
			else {
				numDraws++;
			}
			bGameFinished = true;
		} 
		currentPlayer = (currentPlayer == p1) ? p2 : p1;
		movesCount++;
	}

	if (movesCount == maxMovesCount - 1) {
		numDraws++;
	}

	delete p1;
	delete p2;
	delete b;
}

void BoardMonteCarloEvaluator::Evaluate() {
	for (int i = 0; i < this->numGames; i++) {
		this->EvaluateBoard();
	}
}

