#include "GameBoard.h"


GameBoard::GameBoard(sf::RenderWindow *newWindow, unsigned int width)
{   
    // Determine the number of rows and columns in the game board
    this->rows = newWindow->getSize().y / width;
    this->cols = newWindow->getSize().x / width;
    this->window = newWindow;
    this->tileSize = width;
    this->isSimulationRunning = false;
}

GameBoard::~GameBoard()
{
}

unsigned int GameBoard::getNumberOfRows()
{
    return this->rows;
}

unsigned int GameBoard::getNumberOfColumns()
{
    return this->cols;
}

unsigned int GameBoard::getTileSize()
{
    return this->tileSize;
}

// Set the current clicked tile to Alive
void GameBoard::setTileToAlive()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    unsigned int j = mousePos.x / this->tileSize;
    unsigned int i = mousePos.y / this->tileSize;
    tiles[i][j].setCurrentState(true);
    std::cout << "Mouse was clicked at " << mousePos.x << ", " << mousePos.y << ". The tile is now alive" << std::endl;
}

// Set the current clicked tile to Dead
void GameBoard::setTileToDead()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    unsigned int j = mousePos.x / this->tileSize;
    unsigned int i = mousePos.y / this->tileSize;
    tiles[i][j].setCurrentState(false);
    std::cout << "Mouse was clicked at " << mousePos.x << ", " << mousePos.y << ". The tile is now dead" << std::endl;
}

// Determine the number of tiles in a row and column
void GameBoard::initialise()
{   
    unsigned int width = this->tileSize;
    unsigned int y = 0;

    for (unsigned int i = 0; i <= this->rows; i++)
    {
        unsigned int x = 0;
        std::vector<Tile> rowTile;
        for (unsigned int j = 0; j <= this->cols; j++)
        {
            Tile tile(x, y, width);
            rowTile.push_back(tile);
            x += width;
        }
        y += width;
        this->tiles.push_back(rowTile);
    }
}

// Update the game board with the new tile states
void GameBoard::update()
{
    // Loop through creating 
    for (int i = 0; i < this->tiles.size(); i++)
    {
        for (int j = 0; j < this->tiles[i].size(); j++)
        {   
            tiles[i][j].draw(*this->window);
        }
    }
}

// Set the next state of the Tile to the current state
void GameBoard::updateTilesToNextState()
{
    // Loop through creating 
    for (int i = 0; i < this->tiles.size(); i++)
    {
        for (int j = 0; j < this->tiles[i].size(); j++)
        {   
            tiles[i][j].updateState();
        }
    }
}

// Determine the next states of the tiles based on the game rules
void GameBoard::determineNextStates()
{

    /*
    These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

        Any live cell with two or three live neighbours survives.
        Any dead cell with three live neighbours becomes a live cell.
        All other live cells die in the next generation. Similarly, all other dead cells stay dead.
    */

    // Loop through the tiles to update their next states 
    for (int i = 0; i < this->tiles.size(); i++)
    {
        for (int j = 0; j < this->tiles[i].size(); j++)
        {   
            Tile currentTile = tiles[i][j];
            currentTile.draw(*this->window);

            int numberOfAliveNeighbours = 0;
            // Determine the number of alive cells
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {   
                    int xMax = tiles.size();
                    int yMax = tiles[0].size();
                    int xInd = i + x;
                    int yInd = j + y;
                    if (xInd > 0 && yInd > 0 && xInd < xMax && yInd < yMax && (x != 0 || y != 0))
                    {
                        Tile neighbour = tiles[xInd][yInd];
                        if (neighbour.isAlive())
                        {
                            numberOfAliveNeighbours++;
                        }
                    }
                }
            }

            // Determine the next states of the Tiles
            if (!currentTile.isAlive() && numberOfAliveNeighbours == 3)
            {
                // If the cell is dead, and has 3 or more neighbours 
                // It becomes alive
                currentTile.setNextState(true);
            }
            else if (currentTile.isAlive() && (numberOfAliveNeighbours == 2 || numberOfAliveNeighbours == 3))
            {   
                // If the cell is alive, and has 2 or 3 neighbours
                // It's alive on the next state
                currentTile.setNextState(true);
            }
            else
            {   
                // Every other cell dies
                currentTile.setNextState(false);
            }

            // Set the current tile to the updated tile
            tiles[i][j] = currentTile;
        }
    }
}


// Run the game board
void GameBoard::run()
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
                    else if (event.key.code == sf::Keyboard::R)
                    {   
                        std::cout << "Simulation is now running\n";
                        isSimulationRunning = true;
                    }
                    else if (event.key.code = sf::Keyboard::S)
                    {
                        std::cout << "Simulation has stopped running\n";
                        isSimulationRunning = false;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        setTileToAlive();
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {
                        setTileToDead();
                    }
                    break;
            }
        }

        // Determine if the Simulation is running
        if (isSimulationRunning)
        {   
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() > 50)
            {
                window->clear(sf::Color::Black);
                update();
                window->display();
                determineNextStates();
                updateTilesToNextState();
                clock.restart();
            }
        }
        else
        {
            // Display the Window
            window->clear(sf::Color::Black);
            update();
            window->display();
        }
    }
}
