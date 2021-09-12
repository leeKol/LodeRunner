#include "GameInstructions.h"
#include "Resources.h"
#include "Macros.h"
 
GameInstructions::GameInstructions()
    :m_gameInstructions(Resources::getResources().getSprite(gameInstructions)),
    m_backButton(Resources::getResources().getSprite(backButton))
{
    m_gameInstructions.setOrigin(m_gameInstructions.getLocalBounds().width / 2, m_gameInstructions.getLocalBounds().height / 2);
    m_gameInstructions.setPosition(WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2);
    m_gameInstructions.setScale(2, 2);

    m_backButton.setOrigin(m_backButton.getLocalBounds().width / 2, m_backButton.getLocalBounds().height / 2);
    m_backButton.setPosition(100, 100);
    m_backButton.setScale(1.5, 1.5);
}

void GameInstructions::run(sf::RenderWindow& window, const sf::Sprite& background)
{
    while (window.isOpen())
    {
        window.clear();

        window.draw(background);
        window.draw(m_gameInstructions);
        window.draw(m_backButton);
        window.display();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                exit(EXIT_SUCCESS);
                break;

            case sf::Event::MouseButtonReleased:
            {
                auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    if (m_backButton.getGlobalBounds().contains(location))
                    {
                        Resources::getResources().playSound(clickSound);
                        return;
                    }
                    break;
                case sf::Mouse::Button::Right:
                    break;
                }
                break;
            }
            }
        }
    }
}