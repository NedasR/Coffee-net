#pragma once
#include <SFML/Network/Packet.hpp>

enum class PacketIDs : sf::Uint8
{	
	Ping = 1,
	RequastNetworkID = 2,
};

class ProcessPacket
{
	public:

	static void UDPUnPackPacket(sf::Packet& packet);

};