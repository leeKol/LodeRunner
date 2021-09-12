#pragma once

#include "Enemy.h"

class HorizontalEnemy : public Enemy
{
public:
    //c-tor:
    HorizontalEnemy(sf::Vector2f, const sf::Vector2f&);

    //other functions:
    virtual sf::Vector2f getMovementDirection() override;
    virtual void checkBorders() override;

    //handleCollision functions:
    using Enemy::handleCollision;
    virtual void handleCollision(Floor&) override;
};