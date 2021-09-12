#pragma once

#include "StaticObject.h"

class Ladder : public StaticObject
{
public:
	//c-tor:
	Ladder(sf::Vector2f, const sf::Vector2f&);

	//handleCollision functions:
	using StaticObject::handleCollision;
	virtual void handleCollision(GameObject&) override;
};