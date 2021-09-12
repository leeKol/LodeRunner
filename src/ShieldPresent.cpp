#include "ShieldPresent.h"

void ShieldPresent::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}