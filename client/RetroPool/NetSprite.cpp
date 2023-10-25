#include "NetSprite.hpp"
#include "Application.hpp"
#include "NetworkManager.hpp"
#include "ProcessPacket.hpp"

void NetSprite::RequastNetworkID()
{
	sf::Packet packet;
	packet << (sf::Uint8)PacketIDs::RequastNetworkID;
	NetworkManager::m_instance->SendPacketServer(packet);
}

NetSprite::NetSprite()
{
	RequastNetworkID();
	NetworkManager::m_instance->AddToNetwork(*this);
}
