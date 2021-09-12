#include "GameController.h"
#include "Macros.h"
#include "Coin.h"
#include "LifePresent.h"
#include "ScorePresent.h"
#include "TimePresent.h"
#include "ShieldPresent.h"
#include "BadPresent.h"
#include "Floor.h"
#include "Rope.h"
#include "Ladder.h"
#include "HorizontalEnemy.h"
#include "RandomEnemy.h"
#include "SmartEnemy.h"
#include "Hole.h"
#include "Resources.h"

#include <iostream>
#include <string>
#include <thread>

int GameController::m_level = 0;
sf::Time GameController::m_deltaTime = sf::seconds(0);
bool GameController::m_isRestartLevel = false;
bool GameController::m_isCheckFall = false;
bool GameController::m_isAddEnemy = false;
sf::Time GameController::m_levelTime = sf::seconds(0);

GameController::GameController()
    :m_height(0), m_width(0), m_shieldSprite(Resources::getResources().getSprite(shield))
{
    m_shieldSprite.setOrigin(m_shieldSprite.getLocalBounds().width / 2, m_shieldSprite.getLocalBounds().height / 2);
    m_shieldSprite.setColor(sf::Color(255, 255, 255, 85));

    sf::Vector2f position = sf::Vector2f(WINDOW_SIZE_WIDTH/(NUM_OF_INFO + 2) + (WINDOW_SIZE_WIDTH / (NUM_OF_INFO + 2))/2,
                                        BOARD_SIZE_HEIGHT + (INFO_DISPLAY_SIZE_HEIGHT/4));

    for (int info = 0; info < NUM_OF_INFO; info++)
    {
        sf::Text newInfoDisplay;
        newInfoDisplay = Resources::getResources().getText();
        newInfoDisplay.setCharacterSize(40);
        newInfoDisplay.setFillColor(sf::Color::White);
        newInfoDisplay.setStyle(sf::Text::Bold);
        
        newInfoDisplay.setPosition(position);
        position += sf::Vector2f(WINDOW_SIZE_WIDTH / (NUM_OF_INFO + 2), 0);

        m_infoDisplay.push_back(newInfoDisplay);
        std::string newString;
        m_infoDisplayStrings.push_back(newString);
    }
}

bool GameController::loadLevel()
{
    std::ifstream boardFile;

    if (!openFile(boardFile))
    {
        return false;
    }

    m_cellSizes.x = float(WINDOW_SIZE_WIDTH) / m_width;
    m_cellSizes.y = float(BOARD_SIZE_HEIGHT) / m_height;

    for (int row = 0; row < m_height; row++)
    {
        m_board.push_back({});

        for (int col = 0; col < m_width; col++)
        {
            char character = boardFile.get();
           
            if (character == PLAYER)
            {
                m_player = Player(calPosition(row, col), m_cellSizes, m_player.getScore(), m_player.getLives());
                m_board[row].push_back(nullptr);
            }
            else if (character == ENEMY)
            {
                enemyRand(row, col);
                m_board[row].push_back(nullptr);
            }
            else
            {
                addStaticObject(character,row, col);
            }
        }
        boardFile.get();
    }
    boardFile.close();

    m_infoDisplay[3].setFillColor(sf::Color::White);

    return true;
}

bool GameController::openFile(std::ifstream& boardFile)
{
    std::string fileName = std::to_string(m_level) + ".txt";

    boardFile.open(fileName);

    if (!boardFile.is_open())
    {
        return false;
    }

    float levelTime;

    boardFile >> m_height;
    boardFile.get();

    boardFile >> m_width;
    boardFile.get();

    boardFile >> levelTime;
    boardFile.get();

    m_levelTime = sf::seconds(levelTime);

    return true;
}

void GameController::enemyRand(int row, int col)
{
    switch (rand() % 3)
    {
    case smart:
    {
        m_enemies.push_back(std::make_unique<SmartEnemy>(calPosition(row, col), m_cellSizes, &m_player));
        break;
    }
    case random:
    {
        m_enemies.push_back(std::make_unique<RandomEnemy>(calPosition(row, col), m_cellSizes));

        break;
    }
    case horizontal:
    {
        m_enemies.push_back(std::make_unique<HorizontalEnemy>(calPosition(row, col), m_cellSizes));
        break;
    }
    default:
        break;
    }
}

void GameController::presentRand(int row, int col)
{
    int present;

    if (m_levelTime.asSeconds() == -1)
    {
        present = rand() % 4;
    }
    else
    {
        present = rand() % 5;
    }
    switch (present)
    {
    case lifePresent:
    {
        m_board[row].push_back(std::make_unique<LifePresent>(calPosition(row, col), m_cellSizes));
        break;
    }
    case scorePresent:
    {
        m_board[row].push_back(std::make_unique<ScorePresent>(calPosition(row, col), m_cellSizes));
        break;
    }
    case badPresent:
    {
        m_board[row].push_back(std::make_unique<BadPresent>(calPosition(row, col), m_cellSizes));
        break;
    }
    case shieldPresent:
    {
        m_board[row].push_back(std::make_unique<ShieldPresent>(calPosition(row, col), m_cellSizes));
        break;
    }
    case timePresent:
    {
        m_board[row].push_back(std::make_unique<TimePresent>(calPosition(row, col), m_cellSizes));
        break;
    }
    default:
        break;
    }
}

void GameController::addStaticObject(char character, int row, int col)
{
    switch (character)
    {
    case FLOOR:
    {
        m_board[row].push_back(std::make_unique<Floor>(calPosition(row, col), m_cellSizes));
        break;
    }
    case COIN:
    {
        m_board[row].push_back(std::make_unique<Coin>(calPosition(row, col), m_cellSizes));
        break;
    }
    case LADDER:
    {
        m_board[row].push_back(std::make_unique<Ladder>(calPosition(row, col), m_cellSizes));
        break;
    }
    case ROPE:
    {
        auto ropeSizes = sf::Vector2f(m_cellSizes.x, m_cellSizes.y / 4);
        m_board[row].push_back(std::make_unique<Rope>(calPosition(row, col), ropeSizes));
        break;
    }
    case EMPTY:
    {
        m_board[row].push_back(nullptr);
        break;
    }
    case PRESENT:
    {
        presentRand(row, col);
    }
    }
}

sf::Vector2f GameController::calPosition(int row, int col)
{
    sf::Vector2f position;

    position.y = float(m_cellSizes.y * (row)+(m_cellSizes.y / 2));
    position.x = float(m_cellSizes.x * (col) + (m_cellSizes.x / 2));

    return position;
}

void GameController::newGameReset(bool& isTimeOn)
{
    m_level = 0;
    m_player.resetScore();
    m_player.resetLives();
    levelReset(isTimeOn);
}

void GameController::levelReset(bool& isTimeOn)
{
    Resources::getResources().stopSound(timer);
    isTimeOn = false;
    m_clock.restart();
    m_timer.restart();
    m_holes.clear();
    m_board.clear();
    m_enemies.clear();
    m_isRestartLevel = false;
}

void GameController::run(sf::RenderWindow& window, const sf::Sprite& backgroundSprite)
{
    bool isTimeOn = false;

    newGameReset(isTimeOn);

    while (window.isOpen())
    {
        if (m_player.getLives() <= 0)
        {
            levelReset(isTimeOn);
            announcement(gameOver, gameOverSound, window);
            return;
        }

        if (Coin::getNumOfCoins() == 0)
        {
            levelReset(isTimeOn);
            if (!newLevel())
            {
                announcement(win, winSound, window);
                return;
            }
        }
        
        checkTimer(isTimeOn);

        window.clear();
        draw(window, backgroundSprite);
        window.display();
        
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                exit(EXIT_SUCCESS);
                break;
            }
        }

        m_deltaTime = m_clock.restart();
        if (m_deltaTime.asSeconds() > DELTA_TIME)
        {
            m_deltaTime = sf::seconds(float(DELTA_TIME));
        }

        if (m_isRestartLevel)
        {
            sf::Text fooText;
            animation(window, backgroundSprite, heart, heartSound, NUM_OF_ROWS_SPRITE_HEART, 
                        NUM_OF_SPRITE_HEART, sf::Vector2f(SIZE_OF_HEART, SIZE_OF_HEART), sf::Vector2f(WINDOW_SIZE_WIDTH / 2, BOARD_SIZE_HEIGHT / 2), fooText);
            levelReset(isTimeOn);
            bool foo = loadLevel();
            m_isRestartLevel = false;
        }
        else
        {
            move(m_player);
            if (!m_isRestartLevel)
            {
                for (int currEnemy = 0; currEnemy < m_enemies.size(); currEnemy++)
                {
                    move(*m_enemies[currEnemy]);
                }
            }
        }
        checkHoles();
    }
}

void GameController::drawBoard(sf::RenderWindow& window)
{
    for (int row = 0; row < m_board.size(); row++)
    {
        for (int object = 0; object < m_board[row].size(); object++)
        {
            if (m_board[row][object] != nullptr)
            {
                m_board[row][object]->draw(window);
            }
        }   
    }
}

void GameController::checkHoles()
{
    for (int hole = 0; hole < m_holes.size();)
    {
        if (m_holes[hole]->getTimeLeft() <= 0)
        {
            auto currCell = getCurrCell(*m_holes[hole]);
            m_board[currCell.y][currCell.x] = std::make_unique<Floor>(calPosition(currCell.y, currCell.x), m_cellSizes);
            m_holes.erase(m_holes.begin() + hole);
        }
        else
        {
            hole++;
        }
    }
}

void GameController::drawInfoDisplay(sf::RenderWindow& window)
{
    m_infoDisplayStrings[0] = "Level: " + std::to_string(m_level);
    m_infoDisplayStrings[1] = "Lives: " + std::to_string(m_player.getLives());
    m_infoDisplayStrings[2] = "Score: " + std::to_string(m_player.getScore() + m_player.getCurrScore());

    if (m_levelTime.asSeconds() == -1)
    {
        m_infoDisplayStrings[3] = "Time: -";
    }
    else
    {
        m_infoDisplayStrings[3] = "Time: " + std::to_string(int(m_levelTime.asSeconds() - m_timer.getElapsedTime().asSeconds()));
    }

    for (int info = 0; info < m_infoDisplay.size(); info++)
    {
        m_infoDisplay[info].setString(m_infoDisplayStrings[info]);
        m_infoDisplay[info].setOrigin(m_infoDisplay[info].getLocalBounds().width / 2, m_infoDisplay[info].getLocalBounds().height / 2);
        window.draw(m_infoDisplay[info]);
    }
}

void GameController::dig()
{
    auto currCell = getCurrCell(m_player);

    if (m_player.getDirection() == DIG_RIGHT)
    {
        currCell.x += 1;
    }
    else
    {
        currCell.x -= 1;
    }

    if (currCell.x >= 0 && currCell.x < m_width)
    {
        if (!dynamic_cast<Ladder*>(m_board[currCell.y][currCell.x].get()))
        {
            currCell.y += 1;
            if (dynamic_cast<Floor*>(m_board[currCell.y][currCell.x].get()))
            {
                Resources::getResources().playSound(digSound);
                m_board[currCell.y][currCell.x] = std::make_unique<Hole>(calPosition(currCell.y, currCell.x), m_cellSizes);
                Hole* newHole = static_cast<Hole*>(m_board[currCell.y][currCell.x].get());
                m_holes.push_back(newHole);
            }
        }
    }
}

void GameController::addLevelTime()
{
    m_levelTime += sf::seconds(10);
}

void GameController::move(MovingObject& object)
{
    if (!object.getIsFalling() && !object.getIsInHole())
    {
        object.move();

        if (object.getDirection() == DIG_RIGHT || object.getDirection() == DIG_LEFT)
        {
            dig();
        }
    }

    auto currCell = getCurrCell(object);

    object.setIsFalling(true);
    m_isCheckFall = false;
    checkMovement(object, currCell);

    if (object.getIsFalling())
    {
        object.moveSprite(DOWN);
        m_isCheckFall = true;
        checkMovement(object, currCell);

        if (!object.getIsFalling())
        {
            if (object.getIsOnLadder())
            {
                object.goToLastPosition();
                object.setIsOnLadder(false);
            }
        }
    }
    if (m_isAddEnemy)
    {
        int row, col;
        do
        {
            row = rand() % m_height;
            col = rand() % m_width;
        } while (m_board[row][col] != nullptr);

        enemyRand(row, col);
        m_isAddEnemy = false;
    }
}

sf::Vector2i GameController::getCurrCell(GameObject& object)
{
    return sf::Vector2i(int((object.getPosition().x / WINDOW_SIZE_WIDTH) * m_width),
                    int((object.getPosition().y / BOARD_SIZE_HEIGHT) * m_height));
}

void GameController::checkMovement(MovingObject& object, sf::Vector2i currCell)
{
    bool isCollision = false;

    for (int row = currCell.y - 1; row <= currCell.y + 1; row++)
    {
        for (int col = currCell.x - 1; col <= currCell.x + 1; col++)
        {
            if (row >= 0 && row < m_height && col >= 0 && col < m_width)
            {
                if (m_board[row][col] != nullptr)
                {
                    if (object.collidesWith(*m_board[row][col]))
                    {
                         m_board[row][col]->handleCollision(object);
                         isCollision = true;
                    }

                    if (!m_board[row][col]->getIsAppear())
                    {
                        m_board[row][col] = nullptr;
                    }
                }
            }
        }
    }
    
    if (!isCollision)
    {
        object.setIsOnLadder(false);
        object.setIsOnRope(false);
    }

    if (dynamic_cast<Player*>(&object))
    {
        for (int currEnemy = 0; currEnemy < m_enemies.size(); currEnemy++)
        {
            if (m_player.collidesWith(*m_enemies[currEnemy]))
            {
                m_enemies[currEnemy]->handleCollision(m_player);
                isCollision = true;
            }
        }
    }
    else
    {
        if (m_player.collidesWith(object))
        {
            object.handleCollision(m_player);
            isCollision = true;
        }
    }
}

bool GameController::newLevel()
{
    if (m_level != 0)
    {
        m_player.incScore((50 * m_level) + m_player.getCurrScore());
        Resources::getResources().playSound(levelEnd);
    }
    m_level++;

    return(loadLevel());
}

int GameController::getLevel()
{
    return m_level;
}

sf::Time GameController::getDeltaTime()
{
    return m_deltaTime;
}

void GameController::setIsRestartLevel(bool status)
{
    m_isRestartLevel = status;
}

bool GameController::getIsCheckFall()
{
    return m_isCheckFall;
}

void GameController::setIsAddEnemy(bool status)
{
    m_isAddEnemy = status;
}

void GameController::announcement(int sprite, int sound, sf::RenderWindow& window)
{
    window.clear(); 

    auto score = Resources::getResources().getText();
    score.setString("Score: " + std::to_string(m_player.getScore() + m_player.getCurrScore()));
    score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
    score.setPosition(750, 700);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(100);

    auto currSprite = Resources::getResources().getSprite(sprite);
    currSprite.setScale(window.getSize().x / currSprite.getLocalBounds().width,
        window.getSize().y / currSprite.getLocalBounds().height);

    window.draw(currSprite);
    window.draw(score);
    window.display();
    Resources::getResources().pauseMusic();
    Resources::getResources().playSound(sound);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    if (sprite == win)
    {
        animation(window, currSprite, fireworks, fireworksSound, NUM_OF_ROWS_SPRITE_FIREWORKS, NUM_OF_SPRITE_FIREWORKS, sf::Vector2f(SIZE_OF_FIREWORKS_WIDTH, SIZE_OF_FIREWORKS_HEIGHT), sf::Vector2f(300, 150), score);
    }
    
    Resources::getResources().playMusic();
}

void GameController::checkTimer(bool& isTimeOn)
{
    if (m_levelTime.asSeconds() - m_timer.getElapsedTime().asSeconds() <= 6)
    {
        if (m_levelTime.asSeconds() != -1 && !isTimeOn)
        {
            Resources::getResources().playSound(timer);
            m_infoDisplay[3].setFillColor(sf::Color::Red);
            isTimeOn = true;
        }
    }
    else
    {
        m_infoDisplay[3].setFillColor(sf::Color::White);
        isTimeOn = false;
    }

    if (m_levelTime.asSeconds() - m_timer.getElapsedTime().asSeconds() <= 0
        && m_levelTime.asSeconds() != -1)
    {
        Resources::getResources().playSound(lose);
        m_isRestartLevel = true;
        m_player.decLife();
    }
}

void GameController::draw(sf::RenderWindow& window, const sf::Sprite& backgroundSprite)
{
    window.draw(backgroundSprite);
    drawBoard(window);
    m_player.draw(window);

    if (!m_player.isProtectionOver())
    {
        m_shieldSprite.setPosition(m_player.getPosition());
        m_shieldSprite.setScale(m_player.getSize().x / (m_shieldSprite.getLocalBounds().width),
            m_player.getSize().y / (m_shieldSprite.getLocalBounds().height));
        window.draw(m_shieldSprite);
    }

    for (int currEnemy = 0; currEnemy < m_enemies.size(); currEnemy++)
    {
        m_enemies[currEnemy]->draw(window);
    }

    drawInfoDisplay(window);
}

void GameController::animation(sf::RenderWindow& window, const sf::Sprite& backgroundSprite, int spriteNum, int soundNum,
                                int numOfRows, int numOfImages, sf::Vector2f size, sf::Vector2f position, sf::Text score)
{
    sf::Sprite sprite;
    sprite = Resources::getResources().getSprite(spriteNum);
    sprite.setPosition(position);

    for (int row = 0; row < numOfRows; row++)
    {
        for (int image = 0; image < numOfImages; image++)
        {
            window.clear();
            if (spriteNum == heart)
            {
                draw(window, backgroundSprite);
            }
            else
            {
                window.draw(backgroundSprite);
                window.draw(score);
            }
            sprite.setTextureRect(sf::IntRect(int(image * size.x), int(row * size.y) , int(size.x), int(size.y)));
            sprite.setScale(3.5, 3);
            sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
            if (spriteNum == heart)
            {
                sprite.setColor(sf::Color(255, 255, 255, 200));
            }
            window.draw(sprite);
            window.display();
            if (row == 0 && image == 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                Resources::getResources().playSound(soundNum);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
}