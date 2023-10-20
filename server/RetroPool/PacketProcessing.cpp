#include "PacketProcessing.hpp"

void PacketProcessing::ProcessPacket(sf::Packet packet)
{
	sf::Uint8 packetID;

	packet >> packetID;

	switch (packetID)
	{
		case (sf::Uint8)PacketIDs::Ping:
		{

			break;
		}
		case (sf::Uint8)PacketIDs::RequastNetworkID:
		{
			

			break;
		}
	}
}
