#pragma once

#include "Enemy.h"

class SmartEnemy : public Enemy {
public:
    //c-tor:
    SmartEnemy(sf::Vector2f, const sf::Vector2f&, const Player*);

    //other function:
    virtual sf::Vector2f getMovementDirection() override;

    //handleCollision function:
    using Enemy::handleCollision;
    
private:
    //members:
    const Player* m_playerPtr;
    sf::Clock m_clock;
    sf::Time m_deltaTime;
};