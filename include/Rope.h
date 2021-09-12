#pragma once

#include "StaticObject.h"

class Rope : public StaticObject
{
public:
	//c-tor:
	Rope(sf::Vector2f, const sf::Vector2f&);

	//handleCollision functions:
	using StaticObject::handleCollision;  
	virtual void handleCollision(GameObject&) override;
};