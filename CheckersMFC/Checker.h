#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include "BoardTile.h"

class EmptyCell;

class Checker :
    public Tile
{
private:
    bool CheckIfTileAvailableToMove(int x, int y);
public:
    bool allowedToMove = true;
    bool selected = false;
    bool king = false;
    int player;
    Checker(int row, int col, int player, Board* board);
    void MakeKing();
    bool Move(int x, int y);
    bool CanJumpAny();
    Checker* CanOpponentJump(int x, int y);
    bool OpponentJump(int x, int y);
    void Remove();

    std::vector<EmptyCell*> GetTilesAvailable();
};

