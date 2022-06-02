#pragma once

#include <stack>
#include <iostream>

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"

void error(string message);

class GameBoard{
    private:
        Piece* Board[DIM][DIM];
        stack<vector<int>> moves_stack;
        bool isWhiteTurn;
    public:
        GameBoard();
        ~GameBoard();

        bool isCheckMate(char color);
        bool isInCheck(char color);
        bool hasAnyMoves(char color);
        bool move(int cur_pos, int end_pos);

        void switchTurns();
        void Display_Board();
        void undo_move();
};