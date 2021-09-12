#include "Floor.h"
#include "Resources.h"
#include "Macros.h"

Floor::Floor(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(floors), position, 1, cellSizes)
{
}

void Floor::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}
