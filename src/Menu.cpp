#include "Menu.h"
#include "Macros.h"
#include "Resources.h"
#include "StateManager.h"

Menu::Menu()
{
    setButtonStirngs();

    for (int button = 0; button < NUM_OF_BUTTONS; button++)
    {
        Button newButton;
        newButton = Button(sf::Vector2f(float(WINDOW_SIZE_WIDTH / 2), float((WINDOW_SIZE_HEIGHT + (button*300)) / 2)),
                            m_buttonStrings[button]);
        m_menu.push_back(newButton);
    }

    m_gameName = Resources::getResources().getText();
    m_gameName.setString("Lode Knight");
    m_gameName.setCharacterSize(200);
    m_gameName.setFillColor(sf::Color(179, 89, 0));
    m_gameName.setOrigin(m_gameName.getLocalBounds().width / 2, m_gameName.getLocalBounds().height / 2);
    m_gameName.setPosition(WINDOW_SIZE_WIDTH / 2, 150);
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int button = 0; button < NUM_OF_BUTTONS; button++)
    {
        m_menu[button].drawButton(window);
    }
}

int Menu::click(sf::Vector2f location) const
{
    for (int button = 0; button < NUM_OF_BUTTONS; button++)
    {
        if (m_menu[button].getButtonGlobalBounds().contains(location))
        {
            return button;
        }
    }
    return NUM_OF_BUTTONS;
}

void Menu::setButtonStirngs()
{
    std::string newGame = "New Game";
    m_buttonStrings.push_back(newGame);
    std::string howToPlay = "How To Play";
    m_buttonStrings.push_back(howToPlay);
    std::string exit = "Exit";
    m_buttonStrings.push_back(exit);
}

void Menu::run(sf::RenderWindow& window, const sf::Sprite& background)
{
    while (window.isOpen() && StateManager::getState() == menu)
    {
        window.clear();

        window.draw(background);
        draw(window);
        window.draw(m_gameName);

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
                    handleClick(window, location);
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

void Menu::handleClick(sf::RenderWindow& window, sf::Vector2f location)
{
    switch (click(location))
    {
    case newGame:
        Resources::getResources().playSound(clickSound);
        StateManager::setState(game);
        break;

    case howToPlay:
        Resources::getResources().playSound(clickSound);
        StateManager::setState(instructions);
        break;

    case exitGame:
        Resources::getResources().playSound(clickSound);
        window.close();
        exit(EXIT_SUCCESS);
        break;

    default:
        break;
    }
}