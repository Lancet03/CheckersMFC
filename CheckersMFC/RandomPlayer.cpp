#include "pch.h"

#include "RandomPlayer.h"
#include "EmptyCell.h"
#include <vector>
#include <utility>
#include <iostream>

RandomPlayer::RandomPlayer() {

}

RandomPlayer::~RandomPlayer() {

}

bool RandomPlayer::MakeMove() {
	srand(time(NULL));

	unsigned int checkerIndex;
	unsigned int movePosIndex;

	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();
	if (checkersThatCanMove.size() == 0) {
		return false;
	}
	checkerIndex = (unsigned int)(rand() % checkersThatCanMove.size());
	Checker* selectedChecker = checkersThatCanMove[checkerIndex];
	if (selectedChecker->player != this->cellType) {
		return false;
	}

	std::vector<EmptyCell*> tilesAvailableToMove = selectedChecker->GetTilesAvailable();
	movePosIndex = (unsigned int)(rand() % tilesAvailableToMove.size());
	EmptyCell* moveTile = tilesAvailableToMove[movePosIndex];

	MoveTypes inRange = moveTile->InRange(selectedChecker);
	if (inRange != MoveTypes::Wrong) {
		if (inRange == MoveTypes::Jump) {
			if (selectedChecker->OpponentJump(moveTile->position.first, moveTile->position.second)) {
				selectedChecker->Move(moveTile->position.first, moveTile->position.second);
				if (selectedChecker->CanJumpAny()) {
					selectedChecker->selected = true;
					this->board->continuousJump = true;
				}
				else {
					this->board->ChangePlayerTurn();
				}
				return true;
			}
		}
		else if (inRange == MoveTypes::RegularMove && !this->board->jumpExist) {
			if (!selectedChecker->CanJumpAny()) {
				selectedChecker->Move(moveTile->position.first, moveTile->position.second);
				this->board->ChangePlayerTurn();
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool RandomPlayer::MakeFirstMove(std::pair<int, int> checkerPos, std::pair<int, int> moveToTilePos) {
	Checker* selectedChecker = this->SelectChecker(checkerPos);
	if (selectedChecker == nullptr) {
		return false;
	}
	return this->SelectWhereCheckerWillGo(selectedChecker, moveToTilePos);
}

Checker* RandomPlayer::SelectChecker(std::pair<int, int> checkerPos) {
	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();

	Checker* selectedChecker = nullptr;
	bool hasSelectedChecker = this->board->CheckIfPlayerHasSelectedCheckers();

	if (hasSelectedChecker) {
		selectedChecker = this->board->GetSelectedChecker();
	}


	if (!hasSelectedChecker) {
		selectedChecker = this->board->GetChecker(checkerPos.first, checkerPos.second);
	}

	if (selectedChecker == nullptr) {
		std::cout << "RandomPlayer Error:: Шашка была выбрана неправильно!" << std::endl;
		return nullptr;
	}

	if (selectedChecker->player != this->cellType) {
		return nullptr;
	}

	if ((!this->board->continuousJump || hasSelectedChecker) && selectedChecker->allowedToMove) {
		this->board->DeselectAllCheckers();
		selectedChecker->selected = true;
	}
	else {
		return nullptr;
	}

	return selectedChecker;
}

bool RandomPlayer::SelectWhereCheckerWillGo(Checker* selectedChecker, std::pair<int, int> moveToTilePos) {
	std::vector<EmptyCell*> availableTurns = selectedChecker->GetTilesAvailable();

	EmptyCell* selectedCell = this->board->GetEmptyCell(moveToTilePos.first, moveToTilePos.second);

	if (!this->board->continuousJump) {
		this->board->DeselectAllCheckers();
	}

	if (selectedCell == nullptr) {
		if (!this->board->continuousJump) {
			this->board->DeselectAllCheckers();
		}

		return false;
	}

	MoveTypes inRange = selectedCell->InRange(selectedChecker);
	if (inRange != MoveTypes::Wrong) {
		if (inRange == MoveTypes::Jump) {
			if (selectedChecker->OpponentJump(selectedCell->position.first, selectedCell->position.second)) {
				selectedChecker->Move(selectedCell->position.first, selectedCell->position.second);
				if (selectedChecker->CanJumpAny()) {
					selectedChecker->selected = true;
					this->board->continuousJump = true;
				}
				else {
					this->board->ChangePlayerTurn();
				}
				return true;
			}
		}
		else if (inRange == MoveTypes::RegularMove && !this->board->jumpExist) {
			if (!selectedChecker->CanJumpAny()) {
				selectedChecker->Move(selectedCell->position.first, selectedCell->position.second);
				this->board->ChangePlayerTurn();
				return true;
			}
		}
	}
}