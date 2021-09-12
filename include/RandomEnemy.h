#pragma once

#include "Enemy.h"

class RandomEnemy : public Enemy
{
public:
	//c-tor:
	RandomEnemy(sf::Vector2f, const sf::Vector2f&);

	//other functions:
	virtual sf::Vector2f getMovementDirection() override;
	virtual void checkBorders() override;

	//handleCollision function:
	using Enemy::handleCollision;

private:
	sf::Clock m_clock;
	sf::Time m_deltaTime;
};