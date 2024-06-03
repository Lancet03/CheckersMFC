#include "pch.h"

#include <iostream>
#include "Player.h"
#include "MoveTypes.h"

Player::Player() {

}

Player::~Player() {

}

void Player::SetupPlayer(std::string name, BoardTile cellType) {
	this->name = name;
	this->cellType = cellType;
}

void Player::SetBoard(Board* board)
{
	this->board = board;
}

std::string Player::GetName() {
	return this->name;
}
