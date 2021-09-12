#pragma once
#include <SFML/Graphics.hpp>

//the consts of the program

enum state {menu, game, instructions};
enum button{newGame, howToPlay, exitGame};
enum gameTexture{player, enemy, floors, hole, coin, ladder, rope, present, background, button, gameOver, win, heart, fireworks, gameInstructions, backButton, shield};
enum sound {coinSound, presentSound, levelEnd, winSound, lose, timer, gameOverSound, clickSound, digSound, heartSound, fireworksSound};
enum present{lifePresent, scorePresent, badPresent, shieldPresent, timePresent};
enum direction {left, right, down, up};
enum enemy {smart, random, horizontal};

const auto UP = sf::Vector2f(0, -1);
const auto DOWN = sf::Vector2f(0, 1);
const auto LEFT = sf::Vector2f(-1, 0);
const auto RIGHT = sf::Vector2f(1, 0);
const auto STAND = sf::Vector2f(0, 0);
const auto DIG_RIGHT = sf::Vector2f(2, 0);
const auto DIG_LEFT = sf::Vector2f(0, 2);
const auto OPPOSITE = float(-1);

const char PLAYER = '@';
const char ENEMY = '%';
const char FLOOR = '#';
const char COIN = '*';
const char LADDER = 'H';
const char ROPE = '-';
const char PRESENT = '+';
const char EMPTY = ' ';
const int FULL_LIFE = 3;

const sf::Vector2f BUTTON_SIZE(2, 1.5);
const sf::Color BUTTON_FRAME_FILL = sf::Color(77, 179, 77, 128);
const sf::Color BUTTON_FRAME_OUTLINE = sf::Color(96, 159, 96);
const int FRAME_OUTLINE_WIDTH = 3;
const int NUM_OF_BUTTONS = 3;
const int NUM_OF_INFO = 4;

const int INFO_DISPLAY_SIZE_HEIGHT = 50;
const int WINDOW_SIZE_HEIGHT = 900;
const int WINDOW_SIZE_WIDTH = 1800;
const int BOARD_SIZE_HEIGHT = WINDOW_SIZE_HEIGHT - INFO_DISPLAY_SIZE_HEIGHT;

const auto PIXEL_PER_SECOND = 230.f;
const double MOVING_OBJECT_RATIO = 1.3;
const double TAKEABLE_OBJECT_RATIO = 1.8;
const double DELTA_TIME = 0.05;
const double EPSILON = 0.1;

const int NUM_OF_SPRITE_COIN = 10;
const int SIZE_OF_COIN = 93;
const int NUM_OF_SPRITE_HEART = 6;
const int NUM_OF_ROWS_SPRITE_HEART = 1;
const int SIZE_OF_HEART = 150;
const int NUM_OF_SPRITE_FIREWORKS = 6;
const int NUM_OF_ROWS_SPRITE_FIREWORKS = 5;
const int SIZE_OF_FIREWORKS_WIDTH = 91;
const int SIZE_OF_FIREWORKS_HEIGHT = 90;