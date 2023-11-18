#include "NetSprite.hpp"
#include "Application.hpp"
#include "NetworkManager.hpp"

sf::Uint16 NetSprite::m_localIDCount;

void NetSprite::RequastNetworkID(bool useLocalID)
{
	// change this to only apply to objects that not dynamically allocated
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
	RequastNetworkID(false);
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
	NetworkManager::m_instance->AddToNetwork(shared_from_this(), local);
}
