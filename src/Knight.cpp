
#include "../headers/Knight.h"

bool Knight::isValidMove(int curRow, int curCol, int row, int col, Piece* Board[DIM][DIM]) {
    if(row > 7 || row < 0 || col > 7 || col < 0 || !(this->is_alive() && Board[row][col]->get_color() != this->get_color()))
        return false;
    for(int D = 0; D < DIM; D++)
        if(curRow + DELTA_ROW[D] == row && curCol + DELTA_COL[D] == col)
            return true;
    return false;
}

vector<int> Knight::AllMoves(int curRow, int curCol, Piece* Board[DIM][DIM]) {
    vector<int> moves;
    for(int D = 0; D < DIM; D++)
        if(curRow + DELTA_ROW[D] < DIM && curCol + DELTA_COL[D] < DIM && curRow + DELTA_ROW[D] >= 0 && curCol + DELTA_COL[D] >= 0
            && this->isValidMove(curRow, curCol, curRow + DELTA_ROW[D], curCol + DELTA_COL[D], Board))
            moves.push_back((curRow + DELTA_ROW[D])*DIM + (curCol + DELTA_COL[D]));
    return moves;
}

Knight::Knight(char color, bool stat) : Piece(color, 'N', stat) {}
Knight::~Knight() {}