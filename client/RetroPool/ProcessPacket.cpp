#include "ProcessPacket.hpp"
#include <iostream>
#include "NetworkManager.hpp"

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
			sf::Uint16 NetworkID;

			packet >> NetworkID;
			NetworkManager::m_instance->AssignNetID(NetworkID);

			std::cout << NetworkID << " << Network ID" << std::endl;

			break;
		}
	}

}
