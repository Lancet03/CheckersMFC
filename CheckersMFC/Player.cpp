#include "pch.h"

#include <iostream>
#include "Player.h"
#include "MoveTypes.h"

Player::Player() {

}

Player::~Player() {

}

void Player::SetupPlayer(CString name, BoardTile cellType) {
	this->name = name;
	this->cellType = cellType;
}

void Player::SetBoard(Board* board)
{
	this->board = board;
}

CString Player::GetName() {
	return this->name;
}
