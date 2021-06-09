#include "GameBoard.h"

// Constructor
GameBoard::GameBoard(sf::RenderWindow *newWindow, unsigned int width)
{   
    // Determine the number of rows and columns in the game board
    this->rows = newWindow->getSize().y / width;
    this->cols = newWindow->getSize().x / width;
    this->window = newWindow;
    this->tileSize = width;
    this->isSimulationRunning = false;

    this->isLeftMouseButtonRelased = true;
    this->isRightMouseButtonReleased = true;
}

// Destructor
GameBoard::~GameBoard()
{
}

// Get the number of rows
unsigned int GameBoard::getNumberOfRows()
{
    return this->rows;
}

// Get the number of columns
unsigned int GameBoard::getNumberOfColumns()
{
    return this->cols;
}

// Get the size of the Tiles
unsigned int GameBoard::getTileSize()
{
    return this->tileSize;
}

// Set the current clicked tile to Alive
void GameBoard::setTileToAlive()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

    // Calculate tilesize
    float xSize = (float)this->window->getSize().x / (float)this->cols;
    float ySize = (float)this->window->getSize().y / (float)this->rows;
    unsigned int j = mousePos.x / xSize;
    unsigned int i = mousePos.y / ySize;

    unsigned int iMax = tiles.size();
    unsigned int jMax = tiles[0].size();

    if (i > iMax)
    {
        i = iMax - 1;
    } 
    else if (i < 0)
    {
        i = 0;
    }

    if (j > jMax)
    {
        j = jMax - 1;
    }
    else if (j < 0)
    {
        j = 0;
    }

    tiles[i][j].setCurrentState(true);

    //std::cout << "Mouse was clicked at " << mousePos.x << ", " << mousePos.y << ". The tile is now alive" << std::endl;
}

// Set the current clicked tile to Dead
void GameBoard::setTileToDead()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);

    // Calculate tilesize
    float xSize = (float)this->window->getSize().x / (float)this->cols;
    float ySize = (float)this->window->getSize().y / (float)this->rows;
    unsigned int j = mousePos.x / xSize;
    unsigned int i = mousePos.y / ySize;

    unsigned int iMax = tiles.size();
    unsigned int jMax = tiles[0].size();

    if (i > iMax)
    {
        i = iMax - 1;
    } 
    else if (i < 0)
    {
        i = 0;
    }

    if (j > jMax)
    {
        j = jMax - 1;
    }
    else if (j < 0)
    {
        j = 0;
    }

    tiles[i][j].setCurrentState(false);

    //std::cout << "Mouse was clicked at " << mousePos.x << ", " << mousePos.y << ". The tile is now dead" << std::endl;
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
void GameBoard::drawTiles()
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

// Resets the GameBoard
void GameBoard::clear()
{
    // Loop through the game board and resets the tile states 
    for (int i = 0; i < this->tiles.size(); i++)
    {
        for (int j = 0; j < this->tiles[i].size(); j++)
        {   
            tiles[i][j].setCurrentState(false);
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
                    else if (event.key.code == sf::Keyboard::S)
                    {
                        std::cout << "Simulation has stopped running\n";
                        isSimulationRunning = false;
                    }
                    else if (event.key.code == sf::Keyboard::C)
                    {   
                        // Stop the simulat if it's running
                        if (isSimulationRunning)
                        {
                            isSimulationRunning = false;
                        }
                        clear();
                        std::cout << "The Board has been cleared\n";
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        isLeftMouseButtonRelased = false;
                        setTileToAlive();
                    }
                    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    {   
                        isRightMouseButtonReleased = false;
                        setTileToDead();
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    isLeftMouseButtonRelased = true;
                    isRightMouseButtonReleased = true;
                    break;
                case sf::Event::MouseMoved:
                    if (!isLeftMouseButtonRelased)
                    {
                        setTileToAlive();
                    }
                    else if (!isRightMouseButtonReleased)
                    {
                        setTileToDead();
                    }
            }
        }

        // Determine if the Simulation is running
        if (isSimulationRunning)
        {   
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() > 25)
            {
                window->clear(sf::Color::Black);
                drawTiles();
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
            drawTiles();
            window->display();
        }
    }
}

// Get the position of the Mouse click relative to the size of the window
void GameBoard::getMouseClickPos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
    std::cout << "Mouse was clicked at " << mousePos.x << ", " << mousePos.y << std::endl;
}