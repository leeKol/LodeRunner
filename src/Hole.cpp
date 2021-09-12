#include "Hole.h"
#include "Resources.h"
#include "Macros.h"

Hole::Hole(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(hole), position, 1, cellSizes), m_isEmpty(true)
{
	m_timer = sf::seconds(6);
	m_clock.restart();
}

void Hole::setIsEmpty(bool status)
{
	m_isEmpty = status;
}

bool Hole::getIsEmpty() const
{
	return m_isEmpty;
}

float Hole::getTimeLeft() const
{
	return m_timer.asSeconds() - m_clock.getElapsedTime().asSeconds();
}

void Hole::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}