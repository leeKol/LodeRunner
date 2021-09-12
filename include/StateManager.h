#pragma once

#include <SFML/Graphics.hpp>

#include "Resources.h"
#include "GameController.h"
#include "Menu.h"
#include "GameInstructions.h"


class StateManager
{
public:
	//c-tor:
	StateManager();

	//d-tor:
	~StateManager() = default;

	//set function:
	static void setState(int);

	//get function:
	static int getState();

	//other function:
	void run();

private:
	//members:
	Menu m_menu;
	GameController m_gameController;
	sf::Sprite m_background;
	static int m_state;
	GameInstructions m_gameInstructions;
};