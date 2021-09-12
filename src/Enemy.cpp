#include "Enemy.h"
#include "Macros.h"
#include "Resources.h"
#include "Player.h"

Enemy::Enemy(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:MovingObject(Resources::getResources().getSprite(enemy), position, cellSizes)
{
}

void Enemy::handleCollision(Player& player)
{
	player.handleCollision(*this);
}

void Enemy::handleHole(sf::Vector2f holeSize)
{
	setPosition(sf::Vector2f(getPosition().x, getPosition().y - holeSize.y));
	setIsFalling(false);
}