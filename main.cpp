#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "GameBoard.h"

using namespace std;

int main()
{   
    // Window Size
    unsigned int WIN_WIDTH = 1920;
    unsigned int WIN_HEIGHT = 1080;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Conways Game of Life", sf::Style::Close | sf::Style::Resize);
    // Set the frame rate limit to 60 fps
    window->setFramerateLimit(60);

    // Creating the game board
    GameBoard *gameBoard = new GameBoard(window, 20);

    gameBoard->initialise();
    gameBoard->run();
    return 0;
}
