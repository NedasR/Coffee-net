#include "Character.hpp"
#include "NetworkManager.hpp"

void Character::Controls(sf::Event& event)
{
    if(isMain)
    {
        sf::Vector2f vec = sf::Vector2f(0.f, 0.f);
        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                vec.y -= 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                vec.x -= 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                vec.y += 1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                vec.x += 1;
            }
        }
        this->move(vec);
    }
}

Character::Character()
{
    //RequastNetworkID();
    //NetworkManager::m_instance->AddToNetwork(*this);
}

void Character::Update(sf::Event& event)
{
    Controls(event);
}
