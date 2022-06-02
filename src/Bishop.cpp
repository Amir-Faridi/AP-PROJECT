
#include "../headers/Bishop.h"

bool Bishop::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]){
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;
    if(abs(col - curCol) == abs(row - curRow)){
        int DeltaRow = (row - curRow > 0) ? 1 : -1;
        int DeltaCol = (col - curCol > 0) ? 1 : -1;
        for(int R = curRow + DeltaRow, C = curCol + DeltaCol; R != row; R += DeltaRow, C += DeltaCol){
            if(Board[R][C]->is_alive())
                return false;
        }
        return true;
    }
    return false;
}

vector<int> Bishop::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]){
    vector<int> moves;

    for(int i = curRow+1, j = curCol+1; i < DIM && j < DIM; i++, j++){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    for(int i = curRow+1, j = curCol-1; i < DIM && j >= 0; i++, j--){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    for(int i = curRow-1, j = curCol+1; i >= 0 && j < DIM; i--, j++){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    for(int i = curRow-1, j = curCol-1; i >= 0 && j >= 0; i--, j--){ if(this->isValidMove(curRow, curCol, i, j, Board)) moves.push_back(i*DIM + j); }
    
    return moves;
}

Bishop::Bishop(char color, bool stat) : Piece(color, 'B', stat) {}
Bishop::~Bishop() {}