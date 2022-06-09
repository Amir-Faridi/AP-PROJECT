#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stack>
#include <map>
#include <SFML/Graphics.hpp>
using namespace std;

const int DIM = 8;
const int cell_size = 100;

class Cell;
void error(string message);
typedef typename std::vector<std::vector<Cell>> Cells;
class Cell{
    public:
        sf::RectangleShape rect;
        bool isAccupied = false;
};

class Piece{
    private:
        friend class GameBoard;
        char piece_color, piece_type;
        bool status;
        virtual bool isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]) { return false; }
        virtual vector<int> AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]) { vector<int> TMP; return TMP;}
        void set_sprite(Cell& cell, sf::RenderWindow& window);

    public:
        Piece(char color, char type, bool stat);
        Piece() {}
        ~Piece() {}

        char get_type();
        char get_color();

        bool is_alive();

        void kill_piece();
        void revive_piece();

        string representation();
};