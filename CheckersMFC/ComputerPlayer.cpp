#include "pch.h"

#include "ComputerPlayer.h"
#include "BoardMonteCarloEvaluator.h"
#include "Checker.h"
#include "EmptyCell.h"
#include "BoardTile.h"

#include <iostream>
#include <vector>
#include <utility>

ComputerPlayer::ComputerPlayer() {

}

ComputerPlayer::~ComputerPlayer() {

}

bool ComputerPlayer::MakeMove() {
	CheckerMove checkerMove = this->CalcMove();

	std::pair<int, int> checkerToMovePos = checkerMove.checkerPos;
	std::pair<int, int> moveToTilePos = checkerMove.moveToPos;
	Checker* checkerToMove = this->board->GetChecker(checkerToMovePos.first, checkerToMovePos.second);
	if (checkerToMove == nullptr) {
		AfxMessageBox(L"Computer Player Error:: Should get Checker");
		return false;
	}

	EmptyCell* selectedCell = this->board->GetEmptyCell(moveToTilePos.first, moveToTilePos.second);

	MoveTypes inRange = selectedCell->InRange(checkerToMove);
	if (inRange != MoveTypes::Wrong) {
		if (inRange == MoveTypes::Jump) {
			if (checkerToMove->OpponentJump(selectedCell->position.first, selectedCell->position.second)) {
				checkerToMove->Move(selectedCell->position.first, selectedCell->position.second);
				if (checkerToMove->CanJumpAny()) {
					checkerToMove->selected = true;
					this->board->continuousJump = true;
				}
				else {
					this->board->ChangePlayerTurn();
				}
				return true;
			}
		}
		else if (inRange == MoveTypes::RegularMove && !this->board->jumpExist) {
			if (!checkerToMove->CanJumpAny()) {
				checkerToMove->Move(selectedCell->position.first, selectedCell->position.second);
				this->board->ChangePlayerTurn();
				return true;
			}
			else {
				AfxMessageBox(L"Computer Player Error:: Вы должны атаковать!");
				//std::cerr << "Computer Player Error:: Вы должны атаковать!" << std::endl;
				return false;
			}
		}
	}
}

CheckerMove ComputerPlayer::CalcMove() {
	std::vector<BoardMonteCarloEvaluator*> evaluators;

	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();
	for (int i = 0; i < checkersThatCanMove.size(); i++) {
		Checker* checkerThatCanMove = checkersThatCanMove[i];
		std::vector<EmptyCell*> availableToMoveCells = checkerThatCanMove->GetTilesAvailable();

		for (int j = 0; j < availableToMoveCells.size(); j++) {
			EmptyCell* availableToMoveCell = availableToMoveCells[j];
			BoardMonteCarloEvaluator* evaluator = new BoardMonteCarloEvaluator(this->board, 100, this->cellType, checkerThatCanMove->position, availableToMoveCell->position);
			evaluators.push_back(evaluator);
		}
	}


	for (int i = 0; i < evaluators.size(); i++) {
		evaluators[i]->Evaluate();
	}

	int biggestVictories = -1;
	int biggestDraws = -1;
	for (int i = 0; i < evaluators.size(); i++) {
		if (evaluators[i]->GetVictories() > biggestVictories) {
			biggestVictories = evaluators[i]->GetVictories();
		}

		if (evaluators[i]->GetDraws() > biggestDraws) {
			biggestDraws = evaluators[i]->GetDraws();
		}
	}

	std::vector<BoardMonteCarloEvaluator*> biggestWinEvaluators;
	std::vector<BoardMonteCarloEvaluator*> biggestDrawsEvaluators;
	for (int i = 0; i < evaluators.size(); i++) {
		int numVictories, numDraws;
		if (this->cellType == BoardTile::White) {
			numVictories = evaluators[i]->GetVictories();
		}
		else {
			numVictories = evaluators[i]->GetLosses();
		}
		numDraws = evaluators[i]->GetDraws();

		if (numVictories == biggestVictories) {
			biggestWinEvaluators.push_back(evaluators[i]);
		}
		if (numDraws == biggestDraws) {
			biggestDrawsEvaluators.push_back(evaluators[i]);
		}
	}

	std::pair<int, int> checkerToMovePos;
	std::pair<int, int> moveToTilePos;
	if (biggestWinEvaluators.size() > 0) {
		checkerToMovePos = biggestWinEvaluators[0]->GetFirstMoveCheckerPos();
		moveToTilePos = biggestWinEvaluators[0]->GetFirstMoveTilePos();
	}
	else if (biggestDrawsEvaluators.size() > 0) {
		checkerToMovePos = biggestDrawsEvaluators[0]->GetFirstMoveCheckerPos();
		moveToTilePos = biggestDrawsEvaluators[0]->GetFirstMoveTilePos();
	}
	else {
		checkerToMovePos = evaluators[0]->GetFirstMoveCheckerPos();
		moveToTilePos = evaluators[0]->GetFirstMoveCheckerPos();
	}

	CheckerMove checkerMove;
	checkerMove.checkerPos = checkerToMovePos;
	checkerMove.moveToPos = moveToTilePos;

	for (int i = 0; i < evaluators.size(); i++) {
		delete evaluators[i];
	}
	evaluators.clear();
	biggestWinEvaluators.clear();
	biggestDrawsEvaluators.clear();

	return checkerMove;
}