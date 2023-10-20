#include "ProcessPacket.hpp"

void ProcessPacket::UDPUnPackPacket(sf::Packet& packet)
{
	sf::Uint8 packetID;

	packet >> packetID;

	switch (packetID)
	{
		case (sf::Uint8)PacketIDs::Ping:
		{
			


			break;
		}
	}

}
