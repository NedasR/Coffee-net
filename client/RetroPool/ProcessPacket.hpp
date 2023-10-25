#pragma once
#include <SFML/Network/Packet.hpp>

enum class PacketIDs : sf::Uint8
{	
	Ping = 1,
	RequastNetworkID = 2,
	ReceiveNetworkID = 3,
	ConnectToServer = 4,
	FailedToConnect = 5,

};

class ProcessPacket
{
	public:

	static void ReceiveUdpPackets(sf::Packet& packet);

};