#pragma once

#include <SFML/Network.hpp>

enum class PacketIDs : sf::Uint8
{
	Ping = 1,
	RequastNetworkID = 2,
	ReceiveNetworkID = 3,
};

class PacketProcessing
{
	private:

	public:

	static void ProcessPacket(sf::Packet packet);

};