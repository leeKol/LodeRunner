#pragma once

#include "StaticObject.h"

class Floor : public StaticObject 
{
public:
	//c-tor: 
	Floor(sf::Vector2f, const sf::Vector2f&);

	//handleCollision functions:
	using StaticObject::handleCollision;
	virtual void handleCollision(GameObject&) override;
};