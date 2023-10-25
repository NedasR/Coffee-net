#include "PacketProcessing.hpp"
#include "NetworkIDHandler.hpp"
#include "NetworkManager.hpp"
#include <iostream>

void PacketProcessing::ProcessPacket(sf::Packet packet)
{
	sf::Packet sendPacket;
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
			sf::Uint16 id = NetworkIDHandler::GetUniqueNetworkID();
			std::cout << "network ID: " << id << std::endl;
			sendPacket << (sf::Uint8)PacketIDs::ReceiveNetworkID;
			sendPacket << id;
			NetworkManager::m_instance->SendBack(sendPacket);
			break;
		}
	}
}
