#include "LifePresent.h"

void LifePresent::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}