#include "NetSprite.hpp"
#include "Application.hpp"
#include "NetworkManager.hpp"

sf::Uint16 NetSprite::m_localIDCount;

void NetSprite::RequastNetworkID(bool useLocalID)
{
	m_localIDCount++;
	LocalID = m_localIDCount;
	sf::Packet packet;
	packet << (sf::Uint8)PacketIDs::RequastNetworkID;
	packet << useLocalID;
	packet << LocalID;
	NetworkManager::m_instance->SendPacketServer(packet);
}

NetSprite::NetSprite()
{
	// this could cause wrong assignment of networkID to localID since udp dose not 100% grantee that packets will be sent in order
	RequastNetworkID(false); // will need change in near future
}

NetSprite::NetSprite(bool useLocalID)
{
	RequastNetworkID(useLocalID);
}

NetSprite::NetSprite(sf::Uint16 networkIdSync)
{

}

void NetSprite::SyncNetworkID(sf::Uint16 networkedID)
{
	m_itSelf = shared_from_this();
	NetworkManager::m_instance->SyncNetID(networkedID, m_itSelf);
}

void NetSprite::SyncToNetwork()
{
	NetworkManager::m_instance->AddToNetwork(shared_from_this());
}

void NetSprite::SyncToNetwork(bool local)
{
	//m_itSelf = shared_from_this();
	NetworkManager::m_instance->AddToNetwork(shared_from_this(), local);
}
