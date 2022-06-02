#include "../headers/Rook.h"

bool Rook::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]){
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;
    if(curRow == row){
        int moveDirection = (col - curCol > 0) ? 1 : -1;
        for(int C = curCol + moveDirection; C != col; C += moveDirection)
            if(Board[curRow][C]->is_alive())
                return false;
        return true;
    }
    else if(curCol == col){
        int moveDirection = (row - curRow > 0) ? 1 : -1;
        for(int R = curRow + moveDirection; R != row; R += moveDirection)
            if(Board[R][curCol]->is_alive())
                return false;
        return true;
    }
    return false;
}

vector<int> Rook::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]){
    vector<int> moves;

    for(int i = curRow-1; i >= 0; i--){ if(this->isValidMove(curRow, curCol, i, curCol, Board)) moves.push_back(i*DIM + (curCol)); }
    for(int i = curRow+1; i < DIM; i++){ if(this->isValidMove(curRow, curCol, i, curCol, Board)) moves.push_back(i*DIM + (curCol)); }
    for(int i = curCol+1; i < DIM; i++){ if(this->isValidMove(curRow, curCol, curRow, i, Board)) moves.push_back(curRow*DIM + (i)); }
    for(int i = curCol-1; i >= 0; i--){ if(this->isValidMove(curRow, curCol, curRow, i, Board)) moves.push_back(curRow*DIM + (i)); }
    
    return moves;
}

Rook::Rook(char color, bool stat) : Piece(color, 'R', stat) {}
Rook::~Rook() {}