#include "HorizontalEnemy.h"
#include "Macros.h"
#include "Floor.h"
#include "GameController.h"

HorizontalEnemy::HorizontalEnemy(sf::Vector2f position, const sf::Vector2f& cellSizes)
    :Enemy(position, cellSizes)
{
    srand(unsigned int(time(NULL)));

    switch (rand() % 2)
    {
    case left:
        setDirection(LEFT);
        break;

    case right:
        setDirection(RIGHT);
        break;

    default:
        break;
    }
}

sf::Vector2f HorizontalEnemy::getMovementDirection()
{
    return getDirection();
}

void HorizontalEnemy::handleCollision(Floor& floor)
{
    if (!GameController::getIsCheckFall())
    {
        setDirection(getDirection() * OPPOSITE);
    }
    goToLastPosition();
    setIsFalling(false);
}

void HorizontalEnemy::checkBorders()
{
    if ((BOARD_SIZE_HEIGHT - (getSize().y / 2)) <= getPosition().y || (getSize().y / 2) >= getPosition().y ||
        (WINDOW_SIZE_WIDTH - (getSize().x / 2)) <= getPosition().x || (getSize().x / 2) >= getPosition().x)
    {
        goToLastPosition();
        setDirection(getDirection() * OPPOSITE);
    }
}