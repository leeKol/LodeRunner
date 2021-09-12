#include "Ladder.h"
#include "Resources.h"
#include "Macros.h"

Ladder::Ladder(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(ladder), position, 1, cellSizes)
{
}

void Ladder::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}