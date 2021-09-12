#pragma once

#include "MovingObject.h"

class Enemy : public MovingObject
{
public:
	//c-tor:
	Enemy(sf::Vector2f, const sf::Vector2f&);

	//other function:
	virtual sf::Vector2f getMovementDirection() = 0;
	virtual void handleHole(sf::Vector2f) override;

	//handleCollision functions:
	using MovingObject::handleCollision;
	virtual void handleCollision(Player&) override;
	virtual void handleCollision(Enemy&) override {};
	virtual void handleCollision(GameObject&)override {};
};