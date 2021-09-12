#include "Coin.h"
#include "Resources.h"
#include "Macros.h"

int Coin::m_numOfCoins = 0;

Coin::Coin(sf::Vector2f position, const sf::Vector2f& cellSizes)
	:StaticObject(Resources::getResources().getSprite(coin), position, TAKEABLE_OBJECT_RATIO, cellSizes),
		m_source(0, 0), m_deltaTime(sf::seconds(0.1f))
{
	changeSprite(m_source);
	m_clock.restart();
	++m_numOfCoins;
}

Coin::~Coin()
{
	--m_numOfCoins;
}

void Coin::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

int Coin::getNumOfCoins()
{
	return m_numOfCoins;
}

void Coin::animation()
{
	if (m_deltaTime.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0)
	{
		m_source.x++;
		if (m_source.x == NUM_OF_SPRITE_COIN)
		{
			m_source.x = 0;
		}
		changeSprite(m_source);
		m_clock.restart();
	}
}
