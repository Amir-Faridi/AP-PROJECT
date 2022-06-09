#include "../headers/GameBoard.h"

using namespace sf;
int main()
{
    RenderWindow window(VideoMode(800, 800), "Chess", Style::Close | Style::Titlebar);
    GameBoard board(&window);
    board.play();
    return 0;
}