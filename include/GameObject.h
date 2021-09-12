#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Floor;
class Player;
class Ladder;
class Rope;
class Enemy;
class Coin;
class ScorePresent;
class LifePresent;
class BadPresent;
class TimePresent;
class ShieldPresent;
class Hole;

class GameObject
{
public:
	//c-tors:
	GameObject();
	GameObject(sf::Sprite, sf::Vector2f, double, const sf::Vector2f&);

	//d-tor:
	virtual ~GameObject() = default;

	//set functions:
	void setPosition(sf::Vector2f);

	//get functions:
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	bool getIsAppear() const;
	sf::Vector2f getLastPosition() const;

	//other functions:
	void draw(sf::RenderWindow&);
	bool collidesWith(const GameObject&);
	void moveSprite(const sf::Vector2f&);
	void flipSprite();
	void goToLastPosition();
	void disappear();
	virtual void animation() {};
	void changeSprite(const sf::Vector2i);

	//handleCollision functions:
	virtual void handleCollision(GameObject&) {};
	virtual void handleCollision(Floor &) = 0;
	virtual void handleCollision(Player&) = 0;
	virtual void handleCollision(Enemy&) = 0;
	virtual void handleCollision(Ladder&) = 0;
	virtual void handleCollision(Rope&) = 0;
	virtual void handleCollision(Coin&) = 0;
	virtual void handleCollision(TimePresent&) = 0;
	virtual void handleCollision(BadPresent&) = 0;
	virtual void handleCollision(ScorePresent&) = 0;
	virtual void handleCollision(LifePresent&) = 0;
	virtual void handleCollision(ShieldPresent&) = 0;
	virtual void handleCollision(Hole&) = 0;

private:
	//members:
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	sf::Vector2f m_lastPosition;
	bool m_isAppear;
};