
#pragma once

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
#include <iostream>

class Grid
{
private:
    /* data */
    unsigned int rows;
    unsigned int cols;
    unsigned int tileSize;

    // boolean to determine hold and drag of mouse buttons
    bool isLeftMouseButtonRelased;
    bool isRightMouseButtonReleased;

    //////////////////////////////////////////////////////////////////
    /// \brief The window toe draw the Grid. Uses SFML Render Window
    //////////////////////////////////////////////////////////////////
    sf::RenderWindow *window;
    
    std::vector<std::vector<Tile*>> tiles;

public:
    //////////////////////////////////////////////////////////////////
    /// \brief Constructor
    //////////////////////////////////////////////////////////////////
    Grid(sf::RenderWindow *window, unsigned int width);

    //////////////////////////////////////////////////////////////////
    /// \brief Destructor
    //////////////////////////////////////////////////////////////////
    ~Grid();

    //////////////////////////////////////////////////////////////////
    /// \brief Initialise the Grid. Must be called before run to
    /// construct the tiles on the Grid
    //////////////////////////////////////////////////////////////////
    void initialise();

    //////////////////////////////////////////////////////////////////
    /// \brief Run the Grid on an SFML Window
    //////////////////////////////////////////////////////////////////
    void run();

protected:
    //////////////////////////////////////////////////////////////////
    /// \brief Get the number of rows from the Grid
    //////////////////////////////////////////////////////////////////
    unsigned int getNumberOfRows();

    //////////////////////////////////////////////////////////////////
    /// \brief Get the number of columns from the Grid
    //////////////////////////////////////////////////////////////////
    unsigned int getNumberOfColumns();

    //////////////////////////////////////////////////////////////////
    /// \brief Get the grid size
    //////////////////////////////////////////////////////////////////
    unsigned int getGridSize();

    //////////////////////////////////////////////////////////////////
    /// \brief Draw the grid tiles
    //////////////////////////////////////////////////////////////////
    void drawGrid();

    //////////////////////////////////////////////////////////////////
    /// \brief Get the position of the mouse click relative to the size of the window
    //////////////////////////////////////////////////////////////////
    void getMouseClickPos();
};


