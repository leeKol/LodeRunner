#pragma once

#include <SFML/Graphics.hpp>

class GameInstructions
{
public:
	//c-tor:
	GameInstructions();

	//d-tor:
	~GameInstructions() = default;

	//other function:
	void run(sf::RenderWindow&, const sf::Sprite&);

private:
	//memeber:
	sf::Sprite m_gameInstructions;
	sf::Sprite m_backButton;
};