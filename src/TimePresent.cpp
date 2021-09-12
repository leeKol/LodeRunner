#include "TimePresent.h"

void TimePresent::handleCollision(GameObject& gameObject) 
{
	gameObject.handleCollision(*this);
}
