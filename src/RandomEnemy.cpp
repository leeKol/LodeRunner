#include "RandomEnemy.h"
#include "Macros.h"

RandomEnemy::RandomEnemy(sf::Vector2f position, const sf::Vector2f& cellSizes)
    :Enemy(position, cellSizes), m_deltaTime(sf::seconds(1))
{
    m_clock.restart();
}

sf::Vector2f RandomEnemy::getMovementDirection()
{
    int direction;

    if (m_deltaTime.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0)
    {
        m_clock.restart();

        if (getIsOnLadder())
        {
            direction = rand() % 4;
        }
        else if (getIsOnRope())
        {
            direction = rand() % 3;
        }
        else
        {
            direction = rand() % 2;
        }
        switch (direction)
        {
        case left:
            return LEFT;
            break;

        case right:
            return RIGHT;
            break;

        case down:
            return DOWN;
            break;

        case up:
            return UP;
            break;

        default:
            break;
        }
        return STAND;
    }
    else
    {
        return getDirection();
    }
}

void RandomEnemy::checkBorders()
{
    if ((BOARD_SIZE_HEIGHT - (getSize().y / 2)) <= getPosition().y || (getSize().y / 2) >= getPosition().y ||
        (WINDOW_SIZE_WIDTH - (getSize().x / 2)) <= getPosition().x || (getSize().x / 2) >= getPosition().x)
    {
        goToLastPosition();
    }
}