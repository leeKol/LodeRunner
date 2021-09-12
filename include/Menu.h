#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Button.h"

class Menu
{
public:
	//c-tor:
	Menu();

	//d-tor:
	~Menu() = default;

	//other functions:
	void draw(sf::RenderWindow&);
	int click(sf::Vector2f) const;
	void run(sf::RenderWindow&, const sf::Sprite&);

private:
	//members:
	std::vector <Button> m_menu;
	std::vector <std::string> m_buttonStrings;
	sf::Text m_gameName;

	//private functions:
	void setButtonStirngs();
	void handleClick(sf::RenderWindow&, sf::Vector2f);
};