#include "TickManager.hpp"
#include <iostream>

TickManager* TickManager::m_instance;

std::map<int, std::vector<sf::Packet>> TickManager::tickCache;

TickManager::TickManager()
{
    if (!m_instance)
    {
        m_instance = this;
    }
}

void TickManager::TickUdpate()
{
    m_currentTick++;
    if (m_currentTick > m_tickRate)
    {
        m_currentTick = 0;
    }
    std::cout << m_currentTick << std::endl;
}

bool TickManager::DoTickUdpate()
{
    if (m_clock.getElapsedTime() >= sf::seconds(m_tickInterval))
    {
        m_clock.restart();
        return true;
    }

    return false;
}

bool TickManager::IsTickPacket(sf::Packet packet)
{
    int tickNumber;
    packet >> tickNumber;
    if (tickNumber == -1){return false;}

    return true;
}

void TickManager::SaveTickPacket(sf::Packet packet)
{
    //broken not working fix later
    int tickNumber;
    sf::Uint8 type;
    packet >> type;
    std::cout << "type is : " << type << std::endl;
    packet >> tickNumber;
    std::cout << tickNumber << " this tick is" << std::endl;
    m_currentTick = tickNumber;
    tickCache[tickNumber].push_back(packet);
}
