#include "Grid.h"

Grid::Grid(sf::RenderWindow *newWindow, unsigned int width)
{
    // Determine the number of rows and columns in the game board
    this->rows = newWindow->getSize().y / width;
    this->cols = newWindow->getSize().x / width;
    this->window = newWindow;
    this->tileSize = width;

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
    return this->tileSize;
}

// Determine the number of tiles in a row and column
void Grid::initialise()
{   
    unsigned int width = this->tileSize;
    unsigned int y = 0;

    for (unsigned int i = 0; i <= this->rows; i++)
    {
        unsigned int x = 0;
        std::vector<Tile*> rowTile;
        for (unsigned int j = 0; j <= this->cols; j++)
        {
            Tile *tile = new Tile(x, y, width);
            rowTile.push_back(tile);
            x += width;
            // delete tile;
        }
        y += width;
        this->tiles.push_back(rowTile);
    }
}

// Update the game board with the new tile states
void Grid::drawGrid()
{
    // Loop through creating 
    for (int i = 0; i < this->tiles.size(); i++)
    {
        for (int j = 0; j < this->tiles[i].size(); j++)
        {   
            tiles[i][j]->draw(*this->window);
        }
    }
}

// Run the game board
void Grid::run()
{   
    // Clock 
    sf::Clock clock;

    // Main Game Loop
    while (this->window->isOpen())
    {
        sf::Event event;

        // Poll for Events
        while (this->window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        window->close();
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        isLeftMouseButtonRelased = false;
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {   
                        isRightMouseButtonReleased = false;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    isLeftMouseButtonRelased = true;
                    isRightMouseButtonReleased = true;
                    break;
                case sf::Event::MouseMoved:
                    if (!isLeftMouseButtonRelased)
                    {
                    }
                    else if (!isRightMouseButtonReleased)
                    {
                    }
                    break;
            }
        }

        // Display the Window
        window->clear(sf::Color::Black);
        drawGrid();
        window->display();
    }
}