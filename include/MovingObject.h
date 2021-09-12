#pragma once

#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	//c-tors:
	MovingObject();
	MovingObject(sf::Sprite, sf::Vector2f, const sf::Vector2f&);

	//set functions:
	void setIsFalling(bool);
	void setIsOnLadder(bool);
	void setIsOnRope(bool);
	void setDirection(sf::Vector2f);

	//get functions:
	bool getIsFalling() const;
	bool getIsOnLadder() const;
	bool getIsOnRope() const;
	bool getIsInHole() const;
	sf::Vector2f getDirection() const;

	//other functions:
	void move();
	virtual sf::Vector2f getMovementDirection() = 0;
	virtual void checkBorders();
	virtual void handleHole(sf::Vector2f) = 0;
	
	//handleCollision functions:
	virtual void handleCollision(Floor&) override;
	virtual void handleCollision(Ladder&) override;
	virtual void handleCollision(Rope&) override;
	virtual void handleCollision(Coin&) override {};
	virtual void handleCollision(TimePresent&) override {};
	virtual void handleCollision(BadPresent&) override {};
	virtual void handleCollision(ScorePresent&) override {};
	virtual void handleCollision(LifePresent&) override {};
	virtual void handleCollision(ShieldPresent&) override {};
	virtual void handleCollision(GameObject&) override {};
	virtual void handleCollision(Hole&) override;

private:
	//members:
	sf::Vector2f m_direction;
	sf::Vector2f m_objectSide;
	bool m_isFalling;
	bool m_isOnLadder;
	bool m_isOnRope;
	bool m_isInHole;
};