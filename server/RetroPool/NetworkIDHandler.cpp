#include "NetworkIDHandler.hpp"
#include <iostream>

std::unordered_map<sf::Uint16, NetworkObjectInfo> NetworkIDHandler::m_networkIDs;
std::unordered_map<sf::Uint16, sf::Uint16> NetworkIDHandler::m_localToNetworkIDs;

sf::Uint16 NetworkIDHandler::GetSyncedLocalID(sf::Uint16 localID)
{
    auto it = m_localToNetworkIDs.find(localID);

    if (it == m_localToNetworkIDs.end())
    {
        // if the local id not mapped to networkID this will map it
        m_localToNetworkIDs.emplace(localID,GetUniqueNetworkID());
        return m_localToNetworkIDs[localID];
    }
    else
    {
        return m_localToNetworkIDs[localID];
    }
}

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
