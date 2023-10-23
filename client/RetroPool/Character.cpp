#include "Character.hpp"
#include <SFML/Window/Event.hpp>
#include "Application.hpp"

void Character::Controls()
{
    sf::Event event;
    while (Application::m_window.pollEvent(event)) {

        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::W)
            {

            }
            if (event.key.code == sf::Keyboard::A)
            {

            }
            if (event.key.code == sf::Keyboard::S)
            {

            }
            if (event.key.code == sf::Keyboard::D)
            {

            }

        }
    }
}

void Character::Update()
{
    Controls();
}
