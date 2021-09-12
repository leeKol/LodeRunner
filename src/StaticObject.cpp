#include "StaticObject.h"

void StaticObject::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}
