#include "ProcessPacket.hpp"
#include <iostream>

void ProcessPacket::ReceiveUdpPackets(sf::Packet& packet)
{
	sf::Uint8 packetID;

	packet >> packetID;

	switch (packetID)
	{
		case (sf::Uint8)PacketIDs::Ping:
		{
			


			break;
		}

		case (sf::Uint8)PacketIDs::ReceiveNetworkID:
		{
			sf::Uint16 NetworkID = 0;

			NetworkID << packetID;

			std::cout << NetworkID << " << Network ID" << std::endl;

			break;
		}
	}

}
