#include "Player.h"
#include "Macros.h"
#include "Resources.h"
#include "GameController.h"
#include "Coin.h"
#include "Hole.h"
#include "TimePresent.h"
#include "BadPresent.h"
#include "LifePresent.h"
#include "ShieldPresent.h"
#include "ScorePresent.h"

Player::Player()
	:m_currScore(0), m_lives(FULL_LIFE), m_score(0), m_protectionTime(sf::seconds(0))
{
	m_clock.restart();
}

Player::Player(sf::Vector2f position, const sf::Vector2f& cellSizes, int score, int lives)
	:MovingObject(Resources::getResources().getSprite(player) ,position, cellSizes),
	m_currScore(0), m_lives(lives), m_score(score), m_protectionTime(sf::seconds(0))
{
	m_clock.restart();
}

sf::Vector2f Player::getMovementDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		return LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		return RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		return UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		return DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		return DIG_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		return DIG_LEFT;
	}
	return STAND;
}

void Player::decLife()
{
	m_lives--;
}

void Player::resetScore()
{
	m_score = 0;
}

void Player::resetLives()
{
	m_lives = FULL_LIFE;
}

int Player::getScore() const
{
	return m_score;
}

void Player::incScore(int addition)
{
	m_score += addition;
}

int Player::getCurrScore() const
{
	return m_currScore;
}

int Player::getLives() const
{
	return m_lives;
}

void Player::handleCollision(Enemy& enemy)
{
	if (m_protectionTime.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0)
	{
		if (!GameController::getIsCheckFall())
		{
			disqualification();
		}
	}
}

void Player::handleCollision(Coin& coin)
{
	coin.disappear();
	m_currScore += GameController::getLevel()*2;
	Resources::getResources().playSound(coinSound);
}

void Player::handleCollision(TimePresent& timePresent)
{
	timePresent.disappear();
	GameController::addLevelTime();
	Resources::getResources().playSound(presentSound);
	Resources::getResources().stopSound(timer);
}

void Player::handleCollision(BadPresent& badPresent)
{
	badPresent.disappear();
	GameController::setIsAddEnemy(true);
	Resources::getResources().playSound(presentSound);
}

void Player::handleCollision(ScorePresent& scorePresent)
{
	scorePresent.disappear();
	m_currScore += 50;
	Resources::getResources().playSound(presentSound);
}

void Player::handleCollision(LifePresent& lifePresent)
{
	lifePresent.disappear();
	m_lives++;
	Resources::getResources().playSound(presentSound);
}

void Player::handleCollision(ShieldPresent& shieldPresent)
{
	m_protectionTime = sf::seconds(5);
	shieldPresent.disappear();
	m_clock.restart();
	Resources::getResources().playSound(presentSound);
}

void Player::handleHole(sf::Vector2f foo)
{
	disqualification();
}

bool Player::isProtectionOver() const
{
	return m_protectionTime.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0;
}

void Player::disqualification()
{
	disappear();
	m_lives--;
	GameController::setIsRestartLevel(true);
	Resources::getResources().playSound(lose);
}