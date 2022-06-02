#pragma once
#include "../headers/Queen.h"

bool Queen::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]){
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;
    int DeltaRow, DeltaCol;
    if(row == curRow){
        DeltaCol = (col - curCol > 0) ? 1 : -1;
        for(int C = curCol + DeltaCol; C != col; C += DeltaCol)
            if(Board[curRow][C]->is_alive())
                return false;
        return true;
    }
    else if(col == curCol){
        DeltaRow = (row - curRow > 0) ? 1 : -1;
        for(int R = curRow + DeltaRow; R != row; R += DeltaRow)
            if(Board[R][col]->is_alive())
                return false;
        return true;
    }
    else if(abs(col - curCol) == abs(row - curRow)){
        DeltaRow = (row - curRow > 0) ? 1 : -1;
        DeltaCol = (col - curCol > 0) ? 1 : -1;
        for(int R = curRow + DeltaRow, C = curCol + DeltaCol; R != row; R += DeltaRow, C += DeltaCol)
            if(Board[R][C]->is_alive())
                return false;
        return true;
    }
    return false;
}

vector<int> Queen::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]){
    vector<int> moves;
    for(int i = curRow-1, j = curCol-1; i >= 0 && j >= 0; i--, j--){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }

    for(int i = curCol-1; i >= 0; i--){ if(this->isValidMove(curRow, curCol, curRow, i, Board)) moves.push_back(curRow*DIM + (i)); }
    for(int i = curCol+1; i < DIM; i++){ if(this->isValidMove(curRow, curCol, curRow, i, Board)) moves.push_back(curRow*DIM + (i)); }
    for(int i = curRow+1; i < DIM; i++){ if(this->isValidMove(curRow, curCol, i, curCol, Board)) moves.push_back(i*DIM + (curCol)); }
    for(int i = curRow-1; i >= 0; i--){ if(this->isValidMove(curRow, curCol, i, curCol, Board)) moves.push_back(i*DIM + (curCol)); }
    
    for(int i = curRow+1, j = curCol+1; i < DIM && j < DIM; i++, j++){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    for(int i = curRow+1, j = curCol-1; i < DIM && j >= 0; i++, j--){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    for(int i = curRow-1, j = curCol+1; i >= 0 && j < DIM; i--, j++){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    

    return moves;
}

Queen::Queen(char color, bool stat) : Piece(color, 'Q', stat) {}
Queen::~Queen() {}