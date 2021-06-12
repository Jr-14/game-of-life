#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
protected:
    // Tile Size and Position
    unsigned int width;
    unsigned int xPos;
    unsigned int yPos;

    sf::RectangleShape *shape;
    sf::Color color;
public:
    Tile(unsigned int x, unsigned int y, unsigned int newWidth);
    ~Tile();

    unsigned int getWidth();

    // Draw the tile onto the window
    void draw(sf::RenderWindow &window);
};


