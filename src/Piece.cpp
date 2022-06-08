
#include <sstream>
#include <iostream>
#include "../headers/Piece.h"

void error(string message){
    cerr << message << endl;
    abort();
}

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

void Piece::set_sprite(Cell& cell, sf::RenderWindow& window){
        string path = "Textures/";
        if(piece_color == 'W') path += "w_";
        else path += "b_";

        switch(piece_type){
            case 'P': path += "pawn.png"; break;
            case 'N': path += "knight.png"; break;
            case 'B': path += "bishop.png"; break;
            case 'R': path += "rook.png"; break;
            case 'Q': path += "queen.png"; break;
            case 'K': path += "king.png"; break;
        }
        
        sf::Texture texture;
        if(!texture.loadFromFile(path)) error("Texture not found");
        sf::Sprite sprite(texture);
        sprite.setPosition(cell.rect.getPosition().x, cell.rect.getPosition().y);
        cell.isAccupied = true;
        sprite.setScale(0.5, 0.5);
        sprite.move(cell_size/5, cell_size/5);
        window.draw(sprite);
}