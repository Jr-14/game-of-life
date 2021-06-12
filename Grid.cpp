#include "Grid.h"

Grid::Grid(sf::RenderWindow *newWindow, unsigned int width)
{
    // Determine the number of rows and columns in the game board
    this->rows = newWindow->getSize().y / width;
    this->cols = newWindow->getSize().x / width;
    this->window = newWindow;
    this->gridSize = width;

    this->isLeftMouseButtonRelased = true;
    this->isRightMouseButtonReleased = true;
}

Grid::~Grid()
{

}

unsigned int Grid::getNumberOfRows()
{
    return this->rows;
}

unsigned int Grid::getNumberOfColumns()
{
    return this->cols;
}

unsigned int Grid::getGridSize()
{
    return this->gridSize;
}