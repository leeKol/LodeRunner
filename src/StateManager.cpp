#include "StateManager.h"
#include "Macros.h"

int StateManager::m_state = menu;

StateManager::StateManager()
    :m_background(Resources::getResources().getSprite(background))
{
    Resources::getResources().playMusic();
}

void StateManager::run()
{
    auto window = sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT), "Lode Runner");

   while (true)
   {
       switch(m_state)
       {
       case menu:
           m_menu.run(window, m_background);
           break;

       case game:
           m_gameController.run(window, m_background);
           m_state = menu;
           break;

       case instructions:
           m_gameInstructions.run(window, m_background);
           m_state = menu;
           break;
       } 
   }
}

void StateManager::setState(int state)
{
    m_state = state;
}

int StateManager::getState()
{
    return m_state;
}
