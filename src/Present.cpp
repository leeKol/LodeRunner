#include "Present.h"
#include "Resources.h"
#include "Macros.h"

Present::Present(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(present), position, TAKEABLE_OBJECT_RATIO, cellSizes)
{
}
