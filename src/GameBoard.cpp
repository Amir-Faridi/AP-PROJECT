#include "../headers/GameBoard.h"

map<int, char> convertIC = { {0, 'a'}, {1, 'b'}, {2, 'c'}, {3, 'd'}, {4, 'e'}, {5, 'f'}, {6, 'g'}, {7, 'h'} };
map<char, int> convertCI = { {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7} };

GameBoard::GameBoard(sf::RenderWindow* _window) : window(_window){
    selected_piece = nullptr;
    isWhiteTurn = true;
    for(int C = 0; C < 8; C++)
        Board[6][C] = new Pawn('W', true);

    for(int C = 0; C < 8; C++)
        Board[1][C] = new Pawn('B', true);
    
    Board[7][0] = new Rook('W', true);
    Board[7][1] = new Knight('W', true);
    Board[7][2] = new Bishop('W', true);
    Board[7][3] = new Queen('W', true);
    Board[7][4] = new King('W', true);
    Board[7][5] = new Bishop('W', true);
    Board[7][6] = new Knight('W', true);
    Board[7][7] = new Rook('W', true);
    Board[0][0] = new Rook('B', true);
    Board[0][1] = new Knight('B', true);
    Board[0][2] = new Bishop('B', true);
    Board[0][3] = new Queen('B', true);
    Board[0][4] = new King('B', true);
    Board[0][5] = new Bishop('B', true);
    Board[0][6] = new Knight('B', true);
    Board[0][7] = new Rook('B', true);

    for(int R = 2; R < 6; R++)
        for(int C = 0; C < 8; C++)
            this->Board[R][C] = new Piece('X', 'X', false);

    this->window->setFramerateLimit(60);
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

bool GameBoard::isGameOver(){ return isCheckMate('W') && isCheckMate('B'); }

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

void GameBoard::init(){
    this->cells.resize(8);
    for(int R = 0; R < 8; R++){
        this->cells[R].resize(8);
        for(int C = 0; C < 8; C++){
            
            this->cells[R][C].rect.setPosition(sf::Vector2f(C * 100, R * 100));
            this->cells[R][C].rect.setSize(sf::Vector2f(100, 100));
            if((R + C) % 2 == 1)
                this->cells[R][C].rect.setFillColor(sf::Color::Cyan);
            else
                this->cells[R][C].rect.setFillColor(sf::Color::Magenta);
            this->cells[R][C].rect.setOutlineColor(sf::Color::Black);
            this->cells[R][C].rect.setOutlineThickness(1);
        }
    }
}

void GameBoard::draw(){
    for(int R = 0; R < 8; R++){
        for(int C = 0; C < 8; C++){
            window->draw(this->cells[R][C].rect);
            if(Board[R][C]->is_alive())
                Board[R][C]->set_sprite(cells[R][C], *(this->window));
        }
    }
}

void GameBoard::reset(){
    selected_piece = nullptr;
    for(int R = 0; R < DIM; R++){
        for(int C = 0; C < DIM; C++){
            if((R + C) % 2 == 1) this->cells[R][C].rect.setFillColor(sf::Color::Cyan);
            else this->cells[R][C].rect.setFillColor(sf::Color::Magenta);

            if(Board[R][C]->get_type() == 'K'){
                char color = Board[R][C]->get_color();
                if(isInCheck(color))
                    this->cells[R][C].rect.setFillColor(sf::Color::Red);
            }
        }
    }
}

void GameBoard::show_moves(int R, int C){
    vector<int> moves = selected_piece->AllMoves(R, C, Board);
    for(int M = 0; M < moves.size(); M++){
        int row = moves[M] / DIM, col = moves[M] % DIM;
        this->cells[row][col].rect.setFillColor(sf::Color(100, 100, 100));
    }
}

void GameBoard::CheckKingStatus(){
    char turn = isWhiteTurn ? 'W' : 'B';
    if(!isInCheck(turn)) return;

    if(isCheckMate(turn)){ cout << "Checkmate! " << (turn == 'W' ? "Black" : "White") << " wins!" << endl; window->close(); }
    cout << "Check!\n";
    int kingRow = -1, kingCol = -1;
    for(int R = 0; R < DIM; R++)
        for(int C = 0; C < DIM; C++)
            if(Board[R][C]->get_type() == 'K' && Board[R][C]->get_color() == turn){ kingRow = R; kingCol = C; }
    
    if(kingRow == -1 || kingCol == -1) error("King not found...");
    cells[kingRow][kingCol].rect.setFillColor(sf::Color(255, 0, 0));
}

void GameBoard::process_event(sf::Event event){
    if(event.type == sf::Event::Closed)
        window->close();
    
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        static int start, end;
        int pressed_row = event.mouseButton.y / 100, pressed_col = event.mouseButton.x / 100;
        cout << "Pressed: " << pressed_row << " " << pressed_col << endl;
        char turn = isWhiteTurn ? 'W' : 'B';
        if(Board[pressed_row][pressed_col]->is_alive() && Board[pressed_row][pressed_col]->get_color() == turn){
            reset();
            selected_piece = Board[pressed_row][pressed_col];
            show_moves(pressed_row, pressed_col);
            start = pressed_row * DIM + pressed_col; 
        }
        else if(selected_piece != nullptr){
            end = pressed_row * DIM + pressed_col;

            if(move(start, end)) CheckKingStatus();
            else cout << "Invalid move!" << "\n";

            reset();
            Display_Board();
            draw();
            window->display();
        }
    }
}

void GameBoard::play(){
    this->init();
    this->window->display();
    while(this->window->isOpen()){
        sf::Event event;
        while(this->window->pollEvent(event))
            process_event(event);

        this->window->clear();
        this->draw();
        this->window->display();
    }
}

