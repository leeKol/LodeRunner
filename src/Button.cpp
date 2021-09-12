#include "Button.h"
#include "Macros.h"
#include "Resources.h"

Button::Button(sf::Vector2f position, std::string buttonString)
{
	m_text = Resources::getResources().getText();
	m_text.setString(buttonString);
	m_text.setCharacterSize(40);
	m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);

	m_sprite = Resources::getResources().getSprite(button);
	m_sprite.setScale(BUTTON_SIZE);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(position);
}

void Button::drawButton(sf::RenderWindow& window) const
{		
	window.draw(m_sprite);
	window.draw(m_text);
}

sf::FloatRect Button::getButtonGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}