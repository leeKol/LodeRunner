#include "ScorePresent.h"

void ScorePresent::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}