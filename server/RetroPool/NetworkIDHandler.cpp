#include "NetworkIDHandler.hpp"
#include <iostream>

std::unordered_map<sf::Uint16, NetworkObjectInfo> NetworkIDHandler::m_networkIDs;

sf::Uint16 NetworkIDHandler::GetUniqueNetworkID()
{
    for (auto id : m_networkIDs)
    {
        if (!id.second.m_inUse)
        {
            id.second.m_inUse = true;
            return id.first; 
        }
    }
    sf::Uint16 key = 1;;
    while (true)
    {   
        auto it = m_networkIDs.find(key);
        if (it == m_networkIDs.end())
        {
            m_networkIDs.emplace(key,NetworkObjectInfo());
            m_networkIDs[key].m_inUse = true;
            return key;
        }
        key++;
    }
}
