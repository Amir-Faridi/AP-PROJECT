
#include "../headers/GameBoard.h"

map<int, char> convertIC = { {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'} };
map<char, int> convertCI = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7} };

void error(string message){
    cerr << message << endl;
    abort();
}

GameBoard::GameBoard(){
    char color, Mode;
    cin >> color >> Mode;
    isWhiteTurn = (color == 'W') ? true : false;

    string inp = "";
    for(int R = 0; R < DIM; R++){
        for(int C = 0; C < DIM; C++){
            cin >> inp;
            if(inp == "--")
                Board[R][C] = new Piece('X', 'X', false);
            else if(inp[0] == 'N')
                Board[R][C] = new Knight(inp[1], true);
            else if(inp[0] == 'R')
                Board[R][C] = new Rook(inp[1], true);
            else if(inp[0] == 'B')
                Board[R][C] = new Bishop(inp[1], true);
            else if(inp[0] == 'K')
                Board[R][C] = new King(inp[1], true);
            else if(inp[0] == 'Q')
                Board[R][C] = new Queen(inp[1], true);
            else if(inp[0] == 'P')
                Board[R][C] = new Pawn(inp[1], true);
            else
                error("[ERROR]... Invalid input.");
        }
    }
    Display_Board();
}

GameBoard::~GameBoard(){
    for(int R = 0; R < DIM; R++)
        for(int C = 0; C < DIM; C++)
            delete Board[R][C];
}

void GameBoard::Display_Board(){
    for(int R = 0; R < DIM; R++){
        cout << R << "   ";
        for(int C = 0; C < DIM; C++)
            cout << Board[R][C]->representation() << " ";
        cout << "\n";
    }
    cout << "    ";
    for(int i = 0; i < DIM; i++)
        cout << " " << i << " ";
    cout << "\n" << "\n";
}

void GameBoard::undo_move(){
    if(moves_stack.empty()) error("stack is empty...");
    int curRow = moves_stack.top()[0] / DIM, curCol = moves_stack.top()[0] % DIM;
    int row = moves_stack.top()[1] / DIM, col = moves_stack.top()[1] % DIM;

    Piece* TEMP = Board[row][col];
    Board[row][col] = Board[curRow][curCol];
    Board[curRow][curCol] = TEMP;

    if(Board[row][col]->get_type() != 'X')
        Board[row][col]->revive_piece();
    moves_stack.pop();
    switchTurns();
}

void GameBoard::switchTurns(){ isWhiteTurn = !isWhiteTurn; }

bool GameBoard::isCheckMate(char color){ return (isInCheck(color) && !hasAnyMoves(color)); }

bool GameBoard::move(int cur_pos, int end_pos){
    int curRow = cur_pos / DIM, curCol = cur_pos % DIM, row = end_pos / DIM, col = end_pos % DIM;
    char turn = isWhiteTurn ? 'W' : 'B';
    if(Board[row][col]->get_type() == 'K') return false;
    if((Board[curRow][curCol]->get_color() != turn) || (!Board[curRow][curCol]->isValidMove(curRow, curCol, row, col, Board)))
        return false;
    
    Piece* TEMP = Board[row][col];
    Board[row][col] = Board[curRow][curCol];
    Board[curRow][curCol] = TEMP;
    if(Board[curRow][curCol]->get_type() != 'X')
        Board[curRow][curCol]->kill_piece();
    
    if(isInCheck(turn)){
        Board[curRow][curCol] = Board[row][col];
        Board[row][col] = TEMP;
        if(Board[row][col]->get_type() != 'X')
            Board[row][col]->revive_piece();
        return false;
    }

    switchTurns();
    vector<int> tmp = {cur_pos, end_pos};
    moves_stack.push(tmp);
    return true;
}

bool GameBoard::hasAnyMoves(char color){
    for(int i = 0; i < DIM; i++)
    for(int j = 0; j < DIM; j++)
        if(Board[i][j]->is_alive() && Board[i][j]->get_color() == color){
            vector<int> moves = Board[i][j]->AllMoves(i, j, Board);
            for(int M = 0; M < moves.size(); M++){
                if(move(i*DIM + j, moves[M])){ undo_move(); return true; }
            }
        }
    return false;
}

bool GameBoard::isInCheck(char color){
    int R = -1, C = -1;
    bool flag = false;
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++)
            if(Board[i][j]->is_alive() && Board[i][j]->get_color() == color && Board[i][j]->get_type() == 'K'){ R = i; C = j; flag = true; break; }
        if(flag) break;
    }

    if(R == -1 && C == -1) error("CANNOT FIND THE KING...");

    char enemy = (color == 'W') ? 'B' : 'W';
    for(int i = 0; i < DIM; i++)
        for(int j = 0; j < DIM; j++)
            if(Board[i][j]->is_alive())
                if(Board[i][j]->get_color() == enemy)
                    if(Board[i][j]->isValidMove(i, j, R, C, Board))
                        return true;
    return false;
}
