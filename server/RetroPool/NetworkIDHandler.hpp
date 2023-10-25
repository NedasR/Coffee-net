#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <unordered_map>

struct NetworkObjectInfo
{
	bool m_inUse = false;
	sf::Uint8 ObjectID = 0;
};

class NetworkIDHandler
{
	private:

	static std::unordered_map<sf::Uint16, NetworkObjectInfo> m_networkIDs;

	public:

	static sf::Uint16 GetUniqueNetworkID();

};