#include "pch.h"

#include "HumanPlayer.h"
#include <iostream>

HumanPlayer::HumanPlayer() {

}

HumanPlayer::~HumanPlayer() {

}

bool HumanPlayer::MakeMove()
{
	Checker* selectedChecker = this->SelectChecker();
	if (selectedChecker == nullptr) return false;

	return this->SelectWhereCheckerWillGo(selectedChecker);
}

Checker* HumanPlayer::SelectChecker() {
	std::string position;

	std::vector<Checker*> checkersThatCanMove = this->board->GetCheckersThatCanMove();

	std::cout << "Шашки, которые могут идти: ";
	for (int i = 0; i < checkersThatCanMove.size(); i++) {
		Checker* checkerThatCanMove = checkersThatCanMove[i];

		std::cout << checkerThatCanMove->GetTextPosition() << ((i == checkersThatCanMove.size() - 1) ? "." : ", ");
	}
	std::cout << std::endl;

	Checker* selectedChecker = nullptr;
	bool hasSelectedChecker = this->board->CheckIfPlayerHasSelectedCheckers();

	if (hasSelectedChecker) {
		selectedChecker = this->board->GetSelectedChecker();
	}
	else {
		std::cout << "Игрок " << this->name << ", ваш ход..." << std::endl;
		std::cout << "Выберите шашку: (координаты в виде A1): ";
		std::cin >> position;
	}

	if (!hasSelectedChecker && this->board->CheckIfPositionIsCorrect(position)) {
		std::pair<int, int> coords = this->board->ParsePosition(position);
		selectedChecker = this->board->GetChecker(coords.first, coords.second);
	}

	if (selectedChecker == nullptr) {
		std::cout << "Шашка была выбрана неправильно!" << std::endl;
		return nullptr;
	}

	if (selectedChecker->player != this->cellType) {
		std::cout << "Вы выбрали шашку другого игрока!" << std::endl;
		return nullptr;
	}

	if ((!this->board->continuousJump || hasSelectedChecker) && selectedChecker->allowedToMove) {
		this->board->DeselectAllCheckers();
		selectedChecker->selected = true;
	}
	else {
		std::string exists = "Существует атака для другой шашки, пожалуйста выберите другую";
		std::string continious = "Существует продолжительная атака, пожалуйста, прыгайте той же шашкой";
		std::string message = !this->board->continuousJump ? exists : continious;
		std::cout << message << std::endl;
		return nullptr;
	}

	return selectedChecker;
}

bool HumanPlayer::SelectWhereCheckerWillGo(Checker* selectedChecker) {
	std::string position;

	std::vector<EmptyCell*> availableTurns = selectedChecker->GetTilesAvailable();
	std::cout << "Доступные ходы: ";
	for (int i = 0; i < availableTurns.size(); i++) {
		EmptyCell* availableTurn = availableTurns[i];

		std::cout << availableTurn->GetTextPosition() << ((i == availableTurns.size() - 1) ? "." : ", ");
	}
	std::cout << std::endl;

	std::cout << "Выберите место, куда должна пойти шашка " << selectedChecker->GetTextPosition() << " (координаты в виде A1): ";

	std::cin >> position;
	EmptyCell* selectedCell = nullptr;
	if (this->board->CheckIfPositionIsCorrect(position)) {
		std::pair<int, int> coords = this->board->ParsePosition(position);
		selectedCell = this->board->GetEmptyCell(coords.first, coords.second);

		if (!this->board->continuousJump) {
			this->board->DeselectAllCheckers();
		}
	}

	if (selectedCell == nullptr) {
		std::cout << "Клетка была выбрана неправильно!" << std::endl;

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
			else {
				std::cout << "Вы должны атаковать!" << std::endl;
			}
		}
	}
}