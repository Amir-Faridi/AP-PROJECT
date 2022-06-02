#pragma once
#include "../headers/Piece.h"

class Bishop : public Piece{
    private:
        friend class GameBoard;
        bool isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]);
        vector<int> AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]);
    public:
        Bishop(char color, bool stat) : Piece(color, 'B', stat) {}
        ~Bishop() {}
};