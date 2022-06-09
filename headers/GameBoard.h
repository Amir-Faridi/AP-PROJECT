#pragma once

#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"

class GameBoard{
    private:
        sf::Font font;
        sf::RenderWindow* window;
        sf::Text status_text;

        Cells cells;

        Piece* Board[DIM][DIM];

        stack<vector<int>> moves_stack;
        bool isWhiteTurn;

        Piece* selected_piece;
        Piece* dummy;
    public:
        GameBoard(sf::RenderWindow* _window);
        ~GameBoard();

        bool isCheckMate(char color);
        bool isInCheck(char color);
        bool isGameOver();
        bool hasAnyMoves(char color);
        bool move(int cur_pos, int end_pos);

        void switchTurns();
        void Display_Board();
        void undo_move();
        void show_moves(int R, int C);
        void process_event(sf::Event event);
        void CheckKingStatus();
        void PrintBoard();

        void reset();
        void restart_game();
        void init();
        void draw();
        void play();
};