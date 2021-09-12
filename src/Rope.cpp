#include "Rope.h"
#include "Macros.h"
#include "Resources.h"

Rope::Rope(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(rope), position, 1, cellSizes)
{
}

void Rope::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}