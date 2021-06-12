#include "Cell.h"
#include <iostream>

// Constructor
Cell::Cell(unsigned int x, unsigned int y, unsigned int newWidth) : Tile(x, y, newWidth)
{   
    //this->xPos = x;
    //this->yPos = y;
    //this->width = newWidth;
    //this->color = sf::Color::Black;
    //this->shape = new sf::RectangleShape(sf::Vector2f(this->width, this->width));
    //this->shape->setPosition(sf::Vector2f(this->xPos, yPos));
    //this->shape->setOutlineColor(sf::Color(50,50,50));
    //this->shape->setOutlineThickness(1.0f);
    //this->shape->setFillColor(this->color);

    this->alive = false;
    this->aliveStateColor = sf::Color(80,160,220);
    this->deadStateColor = sf::Color::Black;
}

// Destructor
Cell::~Cell()
{
    delete this->shape;
}

// Draw the tile
void Cell::draw(sf::RenderWindow &window)
{   
    determineColor();
    this->shape->setFillColor(this->color);
    window.draw(*this->shape);
}

// Determine if the tile is alive
bool Cell::isAlive()
{
    return this->alive;
}

// Set the next state of the tile
void Cell::setNextState(bool state)
{
    this->nextState = state;
}

// Set the current State of the Tile
void Cell::setCurrentState(bool state)
{
    this->alive = state;
}

// Update the the current state of the tile to the next state
void Cell::updateState()
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
void Cell::determineColor()
{
    if (this->alive)
    {
        this->color = this->aliveStateColor;
    }
    else
    {
        this->color = this->deadStateColor;
    }
}

// Change the state of the Tile
void Cell::changeState()
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
