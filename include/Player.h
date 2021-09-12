#pragma once

#include <SFML/Audio.hpp>

#include "MovingObject.h"

class Player : public MovingObject
{
public:
	//c-tors:
	Player();
	Player(sf::Vector2f, const sf::Vector2f&, int, int);

	//get functions:
	int getScore() const;
	int getCurrScore() const;
	int getLives() const;

	//other functions:
	void incScore(int);
	virtual sf::Vector2f getMovementDirection() override;
	void decLife();
	void resetScore();
	void resetLives();
	virtual void handleHole(sf::Vector2f) override;
	bool isProtectionOver() const;

	//handleCollision functions:
	using MovingObject::handleCollision;
	virtual void handleCollision(Player&) override {};
	virtual void handleCollision(Enemy&) override;
	virtual void handleCollision(Coin&) override;
	virtual void handleCollision(TimePresent&) override;
	virtual void handleCollision(BadPresent&) override;
	virtual void handleCollision(ScorePresent&) override;
	virtual void handleCollision(LifePresent&) override;
	virtual void handleCollision(ShieldPresent&) override;
	virtual void handleCollision(GameObject&) override {};

private:
	//members:
	int m_lives;
	int m_score;
	int m_currScore;
	sf::Clock m_clock;
	sf::Time m_protectionTime;

	//private function:
	void disqualification();
};