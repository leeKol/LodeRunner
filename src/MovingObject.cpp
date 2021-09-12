#include "MovingObject.h"
#include "Macros.h"
#include "Floor.h"
#include "Rope.h"
#include "Ladder.h"
#include "Hole.h"
#include "GameController.h"

MovingObject::MovingObject()
	:m_isFalling(false), m_isOnLadder(false), m_isOnRope(false), m_isInHole(false), m_objectSide(LEFT)
{
}

MovingObject::MovingObject(sf::Sprite sprite, sf::Vector2f position, const sf::Vector2f& cellSizes)
	:GameObject(sprite, position, MOVING_OBJECT_RATIO, cellSizes),
		m_isFalling(false), m_isOnLadder(false), m_isOnRope(false), m_isInHole(false), m_objectSide(LEFT)
{
}

void MovingObject::move()
{
	m_direction = getMovementDirection();

	if (m_objectSide != m_direction && (m_direction == RIGHT || m_direction == LEFT))
	{
		flipSprite();
		m_objectSide = m_direction;
	}

	if (m_direction != STAND && m_direction != DIG_RIGHT && m_direction != DIG_LEFT)
	{
		moveSprite(m_direction);
		checkBorders();
	}
}

void MovingObject::checkBorders()
{
	if ((BOARD_SIZE_HEIGHT - (getSize().y / 2)) <= getPosition().y || (getSize().y / 2) >= getPosition().y ||
		(WINDOW_SIZE_WIDTH - (getSize().x / 2)) <= getPosition().x || (getSize().x / 2) >= getPosition().x)
	{
		goToLastPosition();
	}
}

void MovingObject::handleCollision(Floor& floor)
{
	goToLastPosition();
	setIsFalling(false);
}

void MovingObject::handleCollision(Ladder& ladder)
{
	if (m_direction == UP || m_direction == DOWN)
	{
		setPosition(sf::Vector2f(ladder.getPosition().x, getPosition().y));
	}
	m_isFalling = false;
	m_isOnLadder = true;
	m_isOnRope = false;
}

void MovingObject::handleCollision(Rope& rope)
{
	if (m_direction == UP)
	{
		goToLastPosition();
	}

	if (m_direction == RIGHT || m_direction == LEFT || (GameController::getIsCheckFall() && !m_isOnRope))
	{
		setPosition(sf::Vector2f(getPosition().x, rope.getPosition().y));
		m_isOnRope = true;
		m_isOnLadder = false;
	}
	m_isFalling = false;

	if (m_direction == DOWN && (!m_isOnRope || getPosition().y > rope.getPosition().y))
	{
		m_isFalling = true;
	}
}

void MovingObject::handleCollision(Hole& hole)
{
	if (hole.getTimeLeft() <= 0 && m_isInHole)
	{
		handleHole(hole.getSize());
		hole.setIsEmpty(true);
		m_isInHole = false;
		return;
	}
	if (hole.getPosition().x - (hole.getSize().x / 2) < getPosition().x
		&& hole.getPosition().x + (hole.getSize().x / 2) > getPosition().x
		&& hole.getIsEmpty())
	{
		setPosition(sf::Vector2f(hole.getPosition().x, getPosition().y));
		hole.setIsEmpty(false);
		m_isInHole = true;
	}
	if (getPosition().y >= hole.getPosition().y && m_isInHole)
	{
		setPosition(sf::Vector2f(hole.getPosition().x, getPosition().y));
		setIsFalling(false);
		if (getDirection() == DOWN)
		{
			goToLastPosition();
		}
	}
	if (!hole.getIsEmpty() && !m_isInHole)
	{
		goToLastPosition();
		setIsFalling(false);
	}
}

sf::Vector2f MovingObject::getDirection() const
{
	return m_direction;
}

void MovingObject::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

void MovingObject::setIsFalling(bool status)
{
	m_isFalling = status;
}

void MovingObject::setIsOnLadder(bool status)
{
	m_isOnLadder = status;
}

void MovingObject::setIsOnRope(bool status)
{
	m_isOnRope = status;
}

bool MovingObject::getIsFalling() const
{
	return m_isFalling;
}

bool MovingObject::getIsOnLadder() const
{
	return m_isOnLadder;
}

bool MovingObject::getIsOnRope() const
{
	return m_isOnRope;
}

bool MovingObject::getIsInHole() const
{
	return m_isInHole;
}