#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <unordered_map>

struct NetworkObjectInfo
{
	bool m_inUse = false;
	sf::Uint8 m_ObjectTypeID = 0;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_scale;

};

class NetworkIDHandler
{
	private:

	static std::unordered_map<sf::Uint16, sf::Uint16> m_localToNetworkIDs;

	public:
	//make a function in the future to access this
	static std::unordered_map<sf::Uint16, NetworkObjectInfo> m_networkIDs;

	static sf::Uint16 GetSyncedLocalID(sf::Uint16 localID);

	static sf::Uint16 GetUniqueNetworkID();

};