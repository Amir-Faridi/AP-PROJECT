#pragma once
#include "../headers/Piece.h"

class King : public Piece{
    private:
        friend class GameBoard;
        bool isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]);
        vector<int> AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]);
    public:
        King(char color, bool stat);
        ~King();
};