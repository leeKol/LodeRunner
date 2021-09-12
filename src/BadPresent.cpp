#include "BadPresent.h"

void BadPresent::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}
