#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
private:
    // Tile Size and Position
    unsigned int width;
    unsigned int xPos;
    unsigned int yPos;

    bool alive;
    bool nextState;

    sf::RectangleShape *shape;
    sf::Color color;
public:
    Tile(unsigned int x, unsigned int y, unsigned int newWidth);
    ~Tile();

    unsigned int getWidth();
    bool isAlive();

    void draw(sf::RenderWindow &window);

    // Update the current state of the tile to the next state
    void updateState();

    // Change the current state of the tile
    void changeState();

    // Set the current State of the Tile
    void setCurrentState(bool state);

    // Set the next State of the Tile
    void setNextState(bool state);


private:
    // Determine the colour of the Tile based on the state
    void determineColor();
};


