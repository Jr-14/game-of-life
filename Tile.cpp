#include "Tile.h"
#include <iostream>

// Constructor
Tile::Tile(unsigned int x, unsigned int y, unsigned int newWidth)
{   
    this->xPos = x;
    this->yPos = y;
    this->width = newWidth;
    this->color = sf::Color::Black;
    this->shape = new sf::RectangleShape(sf::Vector2f(this->width, this->width));
    this->shape->setPosition(sf::Vector2f(this->xPos, yPos));
    this->shape->setOutlineColor(sf::Color(50,50,50));
    this->shape->setOutlineThickness(1.0f);
    this->shape->setFillColor(this->color);
}

// Destructor
Tile::~Tile()
{
    delete this->shape;
}

// Draw the tile
void Tile::draw(sf::RenderWindow &window)
{   
    this->shape->setFillColor(this->color);
    window.draw(*this->shape);
}

// Returns the width of the tile
unsigned int Tile::getWidth()
{
    return this->width;
}