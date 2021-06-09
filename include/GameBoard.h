#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <iostream>

class GameBoard
{
private:
    /* data */
    unsigned int rows;
    unsigned int cols;
    unsigned int tileSize;

    bool isSimulationRunning;

    sf::RenderWindow *window;

    std::vector<std::vector<Tile>> tiles;
public:
    // Constructor
    GameBoard(sf::RenderWindow *window, unsigned int width);
    // Destructor
    ~GameBoard();

    /* Accessor Methods */
    unsigned int getNumberOfRows();
    unsigned int getNumberOfColumns();
    unsigned int getTileSize();

    // Update the game board
    void drawTiles();

    // Run the Window
    void initialise();
    void run();

    // Change colour of a square
    void changeState();
    void setTileToAlive();
    void setTileToDead();

    // Determine the next states of the tiles
    void determineNextStates();

    // Set the next state of the Tile to the current state
    void updateTilesToNextState();

    // Run Simulation
    void startSimulation();

    // Clear the game board and reset the tile states
    void clear();

private:
    // Get the position of the mouse click relative to the size of the window
    void getMouseClickPos();
};


