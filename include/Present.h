#pragma once

#include "StaticObject.h"

class Present : public StaticObject
{
public:
	//c-tor:
	Present(sf::Vector2f, const sf::Vector2f&);

	//handleCollision functions:
	using StaticObject::handleCollision;
	virtual void handleCollision(GameObject&) override {};
};