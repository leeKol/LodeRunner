#include "GameObject.h"
#include "GameController.h"
#include "Macros.h"

GameObject::GameObject()
	: m_isAppear(true)
{
}

GameObject::GameObject(sf::Sprite sprite, sf::Vector2f position, double ratio, const sf::Vector2f& cellSizes)
	:m_size(cellSizes), m_isAppear(true)
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	m_size.x /= float(ratio);
	m_size.y /= float(ratio);

	sprite.setScale(m_size.x / (sprite.getLocalBounds().width), m_size.y / (sprite.getLocalBounds().height));

	sprite.setPosition(position);
	m_sprite = sprite;
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::draw(sf::RenderWindow& window)
{
	animation();

	if (getIsAppear())
	{
		window.draw(m_sprite);
	}
}

void GameObject::changeSprite(const sf::Vector2i source)
{
	m_sprite.setTextureRect(sf::IntRect(source.x * SIZE_OF_COIN, source.y, SIZE_OF_COIN, SIZE_OF_COIN));
	m_sprite.setScale(m_size.x / (m_sprite.getLocalBounds().width), m_size.y / (m_sprite.getLocalBounds().height));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

bool GameObject::collidesWith(const GameObject& object)
{
	 return m_sprite.getGlobalBounds().intersects(object.m_sprite.getGlobalBounds());
}

void GameObject::moveSprite(const sf::Vector2f& direction)
{
	m_lastPosition = m_sprite.getPosition();
	m_sprite.move(direction * PIXEL_PER_SECOND * GameController::getDeltaTime().asSeconds());
}

void GameObject::flipSprite()
{
	m_sprite.scale(-1.f, 1.f);
}

void GameObject::goToLastPosition()
{
	m_sprite.setPosition(m_lastPosition);
}

sf::Vector2f GameObject::getLastPosition() const
{
	return m_lastPosition;
}

void GameObject::disappear()
{
	m_isAppear = false;
}

sf::Vector2f GameObject::getSize() const
{
	return m_size;
}

bool GameObject::getIsAppear() const
{
	return m_isAppear;
}