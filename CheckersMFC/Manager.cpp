#include "pch.h"

#include "Manager.h"
#include <iostream>
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include "RandomPlayer.h"

Manager::Manager() {

}

Manager::~Manager() {
	delete this->p2;
	delete this->p1;
	delete this->board;
}

bool Manager::Init() {
	this->board = new Board();
	std::string playerName;
	int playerType;

	std::cout << "Введите тип игрока #1 (1 - человек, 2 - случайный игрок, любое другое число - Компьютер: ";
	std::cin >> playerType;
	if (playerType == 1) {
		this->p1 = new HumanPlayer();
	}
	else if (playerType == 2) {
		this->p1 = new RandomPlayer();
	}
	else {
		this->p1 = new ComputerPlayer();
	}

	std::cout << "Введите тип игрока #2 (1 - человек, 2 - случайный игрок, любое другое число - Компьютер: ";
	std::cin >> playerType;
	if (playerType == 1) {
		this->p2 = new HumanPlayer();
	}
	else if (playerType == 2) {
		this->p2 = new RandomPlayer();
	}
	else {
		this->p2 = new ComputerPlayer();
	}

	std::cout << "Введите имя игрока, играющего белыми шашками: ";
	std::cin >> playerName;
	this->p1->SetupPlayer(playerName, BoardTile::White);
	
	std::cout << "Введите имя игрока, играющего черными шашками: ";
	std::cin >> playerName;
	this->p2->SetupPlayer(playerName, BoardTile::Black);

	this->p1->SetBoard(this->board);
	this->p2->SetBoard(this->board);
	this->currentPlayer = this->p1;

	return true;
}

void Manager::ShowBoard() {
	//this->board->Show();
}

void Manager::MakeMove() {
	this->ShowBoard();
	while (!this->currentPlayer->MakeMove()) {
		std::cout << "Недопустимый ход, попробуйте ещё раз" << std::endl;
		this->ShowBoard();
	}

	if (this->board->CheckEndCondition()) {
		if (this->board->IsVictory()) {
			std::cout << "Игрок " << this->currentPlayer->GetName() << " победил!" << std::endl;
		}

		this->isGameFinished = true;
		this->ShowBoard();

		return;
	}

	if (this->currentPlayer->cellType != this->board->playerTurn) {
		this->currentPlayer = (currentPlayer == this->p1) ? this->p2 : this->p1;
	}
}

bool Manager::IsGameFinished() {
	return this->isGameFinished;
}