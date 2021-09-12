#pragma once

#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "StaticObject.h"
#include "Player.h"
#include "Enemy.h"

class GameController
{
public:
	//c-tor:
	GameController();

	//d-tor:
	~GameController() = default;

	//set functions:
	static void setIsAddEnemy(bool);
	static void setIsRestartLevel(bool);

	//get functions:
	static int getLevel();
	static sf::Time getDeltaTime();
	static bool getIsCheckFall();
	
	//other functions:
	void run(sf::RenderWindow&, const sf::Sprite&);
	static void addLevelTime();
	
private:
	//members
	Player m_player;
	std::vector<std::unique_ptr <Enemy>> m_enemies;
	std::vector<std::vector<std::unique_ptr <StaticObject>>>m_board;

	sf::Vector2f m_cellSizes;
	int m_height;
	int m_width;
	static int m_level;

	static bool m_isRestartLevel;
	static bool m_isCheckFall;
	static bool m_isAddEnemy;

	sf::Clock m_clock;
	static sf::Time m_deltaTime;
	sf::Clock m_timer;
	static sf::Time m_levelTime;

	std::vector<sf::Text>m_infoDisplay;
	std::vector<std::string>m_infoDisplayStrings;
	std::vector<Hole*>m_holes;
	sf::Sprite m_shieldSprite;

	//private functions:
	bool loadLevel();
	sf::Vector2f calPosition(int, int);
	bool newLevel();
	void addStaticObject(char, int, int);
	void drawBoard(sf::RenderWindow&);
	void newGameReset(bool&);
	void levelReset(bool& isTimeOn);
	void checkMovement(MovingObject&, sf::Vector2i);
	void move(MovingObject&);
	void presentRand(int, int);
	void enemyRand(int, int);
	bool openFile(std::ifstream&);
	void drawInfoDisplay(sf::RenderWindow&);
	void dig();
	sf::Vector2i getCurrCell(GameObject&);
	void checkHoles();
	void announcement(int, int, sf::RenderWindow&);
	void checkTimer(bool&);
	void draw(sf::RenderWindow&, const sf::Sprite&);
	void animation(sf::RenderWindow&, const sf::Sprite&, int, int, int, int, sf::Vector2f, sf::Vector2f, sf::Text);
};