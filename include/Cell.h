
#pragma once

#include <SFML/Graphics.hpp>

#include "Tile.h"

class Cell : public Tile
{
private:
    bool alive;
    bool nextState;

    sf::Color aliveStateColor;
    sf::Color deadStateColor;

public:
    Cell(unsigned int x, unsigned int y, unsigned int newWidth);
    ~Cell();

    bool isAlive();

    // Draw the Cell onto the window
    void draw(sf::RenderWindow &window);

    // Update the current state of the tile to the next state
    void updateState();

    // Change the current state of the tile
    void changeState();

    // Set the current State of the Cell
    void setCurrentState(bool state);

    // Set the next State of the Cell
    void setNextState(bool state);

private:
    // Determine the colour of the Cell based on the state
    void determineColor();
};


