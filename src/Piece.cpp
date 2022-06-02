#pragma once
#include <sstream>
#include "../headers/Piece.h"

Piece::Piece(char color, char type, bool stat){
    piece_color = color;
    piece_type = type;
    status = stat;
}

char Piece::get_type(){ return piece_type; }
char Piece::get_color(){ return piece_color; }

bool Piece::is_alive(){ return status; }

void Piece::kill_piece(){ status = false; }
void Piece::revive_piece(){ status = true; }

string Piece::representation(){
    ostringstream os;
    if(is_alive()) os << get_type() << get_color();
    else os << "--";
    return os.str();
}