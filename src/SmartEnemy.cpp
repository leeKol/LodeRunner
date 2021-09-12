#include "SmartEnemy.h"
#include "Player.h"
#include "Macros.h"

SmartEnemy::SmartEnemy(sf::Vector2f position, const sf::Vector2f& cellSizes, const Player* playerPtr)
	:Enemy(position, cellSizes), m_playerPtr(playerPtr), m_deltaTime(sf::seconds(1))
{
	m_clock.restart();
}

sf::Vector2f SmartEnemy::getMovementDirection()
{
	if (abs(m_playerPtr->getPosition().y - getPosition().y) <= EPSILON)
	{
		if (m_playerPtr->getPosition().x > getPosition().x)
		{
			return RIGHT;
		}
		else if (m_playerPtr->getPosition().x < getPosition().x)
		{
			return LEFT;
		}
	}

	else
	{
		if (getIsOnLadder() && m_playerPtr->getPosition().y < getPosition().y)
		{
			return UP;
		}
		else if ((getIsOnLadder() || getIsOnRope()) && m_playerPtr->getPosition().y > getPosition().y)
		{
			return DOWN;
		}
		else
		{
			if (m_playerPtr->getPosition().x > getPosition().x)
			{
				return RIGHT;
			}
			else if (m_playerPtr->getPosition().x  < getPosition().x)
			{
				return LEFT;
			}
		}
	}
	return STAND;
}