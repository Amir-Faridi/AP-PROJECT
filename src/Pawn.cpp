#pragma once
#include "../headers/Pawn.h"

bool Pawn::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]){
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;

    if((this->get_color() == 'W' && curRow == 6 && row == 4 && !Board[curRow-1][curCol]->is_alive() && !Board[curRow-2][curCol]->is_alive()) || (this->get_color() == 'B' && curRow == 1 && row == 3 && !Board[curRow+1][curCol]->is_alive() && !Board[curRow+2][curCol]->is_alive()))
        return true;
    
    if(!Board[row][col]->is_alive())
        if(curCol == col && ((this->get_color() == 'W' && row == curRow - 1) || (this->get_color() == 'B' && row == curRow + 1)))
            return true;
    
    if(Board[row][col]->is_alive())
        if((curCol == col + 1 || curCol == col - 1) && ((this->get_color() == 'W' && row == curRow - 1) || (this->get_color() == 'B' && row == curRow + 1)))
            return true;
    
    return false;
}

vector<int> Pawn::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]){
    vector<int> moves;
    char C = this->get_color();
    if(C == 'W' && curRow == 6 && this->isValidMove(curRow, curCol, curRow-2, curCol, Board))
        moves.push_back(((curRow - 2) * DIM) + curCol);
    else if(C == 'B' && curRow == 1 && this->isValidMove(curRow, curCol, curRow+2, curCol, Board))
        moves.push_back((curRow + 2) * DIM + curCol);
    
    if(C == 'W'){
        if(this->isValidMove(curRow, curCol, curRow-1, curCol, Board)) moves.push_back((curRow - 1) * DIM + curCol);
        if(this->isValidMove(curRow, curCol, curRow-1, curCol+1, Board)) moves.push_back((curRow - 1) * DIM + curCol + 1);
        if(this->isValidMove(curRow, curCol, curRow-1, curCol-1, Board)) moves.push_back((curRow - 1) * DIM + curCol - 1);
    }
    else if(C == 'B'){
        if(this->isValidMove(curRow, curCol, curRow+1, curCol, Board)) moves.push_back((curRow + 1) * DIM + curCol);
        if(this->isValidMove(curRow, curCol, curRow+1, curCol+1, Board)) moves.push_back((curRow + 1) * DIM + curCol + 1);
        if(this->isValidMove(curRow, curCol, curRow+1, curCol-1, Board)) moves.push_back((curRow + 1) * DIM + curCol - 1);
    }
    return moves;
}

Pawn::Pawn(char color, bool stat) : Piece(color, 'P', stat) {}
Pawn::~Pawn() {}