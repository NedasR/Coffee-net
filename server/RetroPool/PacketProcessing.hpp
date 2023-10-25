#pragma once

#include <SFML/Network.hpp>

enum class PacketIDs : sf::Uint8
{
	Ping = 1,
	RequastNetworkID = 2,
	ReceiveNetworkID = 3,
	ConnectToServer = 4,
	FailedToConnect = 5,
};

class PacketProcessing
{
	private:

	public:

	static void ProcessPacket(sf::Packet packet);

};