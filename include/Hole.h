#pragma once

#include "StaticObject.h"

class Hole : public StaticObject
{
public:
	//c-tor:
	Hole(sf::Vector2f, const sf::Vector2f&);

	//set function:
	void setIsEmpty(bool);

	//get function:
	bool getIsEmpty() const;

	//other function:
	float getTimeLeft() const;

	//handleCollision functions:
	using StaticObject::handleCollision;
	virtual void handleCollision(GameObject&) override;

private:
	//member:
	bool m_isEmpty;
	sf::Time m_timer;
	sf::Clock m_clock;
};