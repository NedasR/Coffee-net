#include "Delta.hpp"
#include "Character.hpp"
#include "NetworkManager.hpp"
#include "ProcessPacket.hpp"
#include <iostream>

void Character::Controls()
{
    if(isMain)
    {
        sf::Int8 W = 0,A = 0,S = 0,D = 0;
        sf::Vector2f vec = sf::Vector2f(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            //vec.y -= 300.0f * Delta::Time();
            vec.y -= 20.0f * speed;
            W = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //vec.x -= 300.0f * Delta::Time();
            vec.x -= 20.0f * speed;
            A = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            //vec.y += 300.0f * Delta::Time();
            vec.y += 20.0f * speed;
            S = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //vec.x += 300.0f * Delta::Time();
            vec.x += 20.0f * speed;
            D = 1;
        }
        if (vec.x == 0 && vec.y == 0) {return;}

        this->setPosition(this->getPosition() + vec);
        // will need to be reworked to have server authority
        sf::Packet packet;
        packet << (sf::Uint8)PacketIDs::PostionUpdate;
        packet << GetNetworkID();
        packet << W << A << S << D;
        //packet << this->getPosition().x << this->getPosition().y;
        NetworkManager::m_instance->SendPacketServer(packet);
    }
}

Character::Character()
{
    speed = 0.4f;
    objectTypeID = (sf::Uint8)ObjectTypeIDs::Character;
}

Character::Character(sf::Uint16 networkIdSync) : NetSprite(networkIdSync)
{
    speed = 0.4f;
    objectTypeID = (sf::Uint8)ObjectTypeIDs::Character;
}

Character::Character(bool useLocalID) : NetSprite(useLocalID)
{
    speed = 0.4f;
    objectTypeID = (sf::Uint8)ObjectTypeIDs::Character;
}

void Character::Update()
{
    Controls();
}
