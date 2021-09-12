#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	//c-tors:
	Button() = default;
	Button(sf::Vector2f, std::string);

	//d-tor:
	~Button() = default;

	//other functions:
	void drawButton(sf::RenderWindow&) const;
	sf::FloatRect getButtonGlobalBounds() const;

private:
	//members:
	sf::Text m_text;
	sf::Sprite m_sprite;
};