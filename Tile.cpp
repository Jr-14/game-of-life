#include "Tile.h"
#include <iostream>

// Constructor
Tile::Tile(unsigned int x, unsigned int y, unsigned int newWidth)
{   
    this->xPos = x;
    this->yPos = y;
    this->width = newWidth;
    this->alive = false;
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
}

// Draw the tile
void Tile::draw(sf::RenderWindow &window)
{   
    determineColor();
    this->shape->setFillColor(this->color);
    window.draw(*this->shape);
}

// Returns the width of the tile
unsigned int Tile::getWidth()
{
    return this->width;
}

// Determine if the tile is alive
bool Tile::isAlive()
{
    return this->alive;
}

// Set the next state of the tile
void Tile::setNextState(bool state)
{
    this->nextState = state;
}

// Set the current State of the Tile
void Tile::setCurrentState(bool state)
{
    this->alive = state;
}

void Tile::updateState()
{   
    if (this->nextState)
    {
        this->alive = true;
    }
    else
    {
        this->alive = false;
    }
}

// Determine the colour of the tile based on the state
void Tile::determineColor()
{
    if (this->alive)
    {
        this->color = sf::Color(80,160,220);
    }
    else
    {
        this->color = sf::Color::Black;
    }
}

// Change the state of the Tile
void Tile::changeState()
{
    if (this->alive)
    {
        this->alive = false;
    } 
    else
    {
        this->alive = true;
    }
}
