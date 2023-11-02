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
			bool localToNetworkIDMapping;
			sf::Uint16 id = 0;
			sf::Uint16 localID;
			bool assignToLocalID = false;
			packet >> localToNetworkIDMapping;
			packet >> localID;

			switch (localToNetworkIDMapping)
			{
				case true :
				{
					id = NetworkIDHandler::GetSyncedLocalID(localID);
					assignToLocalID = true;
					break;
				}

				case false :
				{
					id = NetworkIDHandler::GetUniqueNetworkID();
					assignToLocalID = false;
					break;
				}
			}
			sendPacket << (sf::Uint8)PacketIDs::ReceiveNetworkID;
			sendPacket << assignToLocalID;
			sendPacket << id;
			sendPacket << localID;
			std::cout << "network ID: " << id << std::endl;
			NetworkManager::m_instance->SendBack(sendPacket);
			break;
		}

		case (sf::Uint8)PacketIDs::ConnectToServer:
		{
			NetworkManager::m_instance->ConnectToServer();
			break;
		}

		case (sf::Uint8)PacketIDs::PostionUpdate:
		{
			sf::Uint16 ID;
			float x;
			float y;
			packet >> ID >> x >> y;
			sendPacket << (sf::Uint8)PacketIDs::PostionUpdate;
			sendPacket << ID << x << y;
			//std::cout << "Networked ID : " << ID << " Position :" << x << " " << y << std::endl;
			NetworkManager::m_instance->SendToAllClients(sendPacket);
			break;
		}

		case (sf::Uint8)PacketIDs::LateJoinerSync:
		{
			//will need change to sync since this avoids sending to the sender so id dose not copy it's self
			auto requestSender = NetworkManager::m_instance->GetRecentSender();
			for (auto it : NetworkManager::m_instance->m_clientsConnected)
			{
				std::cout << " client : "<< it.first << " port : " << it.second << std::endl;
				//if (it.first == requestSender.first
				//    && it.second == requestSender.second) return;

				for(auto& ids : NetworkIDHandler::m_networkIDs)
				{
				sendPacket.clear();
				sendPacket << (sf::Uint8)PacketIDs::SyncObject;
				sendPacket << (sf::Uint8)ObjectTypeIDs::Character;
				sendPacket << ids.first;// id

				NetworkManager::m_instance->SendToAllClients(sendPacket);
				}
			}
			break;
		}

	}
}
