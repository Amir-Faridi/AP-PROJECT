
#include "../headers/King.h"

bool King::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]){
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;
    int DeltaRow = row - curRow, DeltaCol = col - curCol;
    if(DeltaRow >= -1 && DeltaRow <= 1 && DeltaCol >= -1 && DeltaCol <= 1)
        return true;
    return false;
}

vector<int> King::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]){
    int MOVES[3] = {0, 1, -1};
    vector<int> moves;
    for(int i = 0; i < 3; i++)  
        for(int j = 0; j < 3; j++)
            if(i != 0 || j != 0)
                if(curRow + MOVES[i] >= 0 && curRow + MOVES[i] < DIM && curCol + MOVES[j] >= 0 && curCol + MOVES[j] < DIM
                    && this->isValidMove(curRow, curCol, curRow+MOVES[i], curCol+MOVES[j], Board))
                    moves.push_back((curRow + MOVES[i])*DIM + (curCol + MOVES[j]));
    return moves;
}

King::King(char color, bool stat) : Piece(color, 'K', stat) {}
King::~King() {}