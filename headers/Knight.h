#pragma once
#include "../headers/Piece.h"

class Knight : public Piece{
    private:
        friend class GameBoard;
        const int DELTA_ROW[8] = {2, 1, -1, -2, -2, -1, 1, 2};
        const int DELTA_COL[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
        bool isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]);
        vector<int> AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]);
    public:
        Knight(char color, bool stat);
        ~Knight();
};