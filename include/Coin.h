#pragma once

#include "StaticObject.h"

class Coin : public StaticObject
{
public:
    //c-tor:
    Coin(sf::Vector2f, const sf::Vector2f&);

    //d-tor:
    ~Coin();

    //get function:
    static int getNumOfCoins();

    //other function:
    virtual void animation() override;

    //handleCollision functions:
    virtual void handleCollision(GameObject&) override;
    using StaticObject::handleCollision;

private:
    //member:
    static int m_numOfCoins;
    sf::Vector2i m_source;
    sf::Clock m_clock;
    sf::Time m_deltaTime;
};