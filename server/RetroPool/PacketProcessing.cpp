#include "PacketProcessing.hpp"
#include "NetworkIDHandler.hpp"
#include "NetworkManager.hpp"
#include <iostream>
#include "TickManager.hpp"

std::chrono::milliseconds PacketProcessing::serverTimeStamp;

void PacketProcessing::ProcessPacket(sf::Packet packet)
{

	sf::Packet sendPacket;
	sf::Uint8 packetID;

	packet >> packetID;

	switch (packetID)
	{
		case (sf::Uint8)PacketIDs::Ping:
		{
			std::uint64_t clientTime;

			packet >> clientTime;

			Client& client = NetworkManager::m_instance->GetCurrentSender();
			
			std::get<2>(client).RTT = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - serverTimeStamp;

			std::cout << "RTT TIME: " << std::get<2>(client).RTT.count() << std::endl;

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
			sendPacket << -1;
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

			TickManager::m_instance->InitialClientTickSync();
			//sendPacket << -1;
			//sendPacket << (sf::Uint8)PacketIDs::SendCurrentTick;
			//sendPacket << TickManager::m_instance->GetCurrentTick();
			//NetworkManager::m_instance->SendBack(sendPacket);

			break;
		}

		case (sf::Uint8)PacketIDs::PostionUpdate:
		{
			sf::Int8 W = 0, A = 0, S = 0, D = 0;
			sf::Uint16 ID;
			packet >> ID;
			NetworkObjectInfo& ptr = NetworkIDHandler::GetNetworkObjectInfo(ID);
			//packet >> ptr.m_position.x >> ptr.m_position.y;
			packet >> W >> A >> S >> D;
			if (W)
			{
				ptr.m_position.y -= 20.0f * 0.4f;
			}
			if (A)
			{
				ptr.m_position.x -= 20.0f * 0.4f;
			}
			if (S)
			{
				ptr.m_position.y += 20.0f * 0.4f;
			}
			if (D)
			{
				ptr.m_position.x += 20.0f * 0.4f;
			}
			sendPacket << TickManager::m_instance->GetCurrentTick();
			sendPacket << (sf::Uint8)PacketIDs::PostionUpdate;
			sendPacket << ID << ptr.m_position.x << ptr.m_position.y;
			//std::cout << "Networked ID : " << ID << " Position :" << x << " " << y << std::endl;
			NetworkManager::m_instance->SendToAllClients(sendPacket);
			break;
		}

		// this will need a a big rework since the late joiner should get everything updated on it's side 
		// but the other clients should update only the new objects that have been created because of the new client
		case (sf::Uint8)PacketIDs::LateJoinerSync:
		{
			
			//auto requestSender = NetworkManager::m_instance->GetRecentSender();
			for (auto it : NetworkManager::m_instance->m_clientsConnected)
			{
				std::cout << " client : "<< std::get<0>(it) << " port : " << std::get<1>(it) << std::endl;

				//client checks each id if it has it or not if it dose it won't sync the id
				for(auto& ids : NetworkIDHandler::m_networkIDs)
				{
				
				sendPacket.clear();
				sendPacket << -1;
				sendPacket << (sf::Uint8)PacketIDs::SyncObject;
				sendPacket << (sf::Uint8)ObjectTypeIDs::Character;
				sendPacket << ids.first;// id
				NetworkObjectInfo& ptr = NetworkIDHandler::GetNetworkObjectInfo(ids.first);
				// expand to have stuff like scale, rotation and other stuff
				sendPacket << ptr.m_position.x << ptr.m_position.y;

				NetworkManager::m_instance->SendToAllClients(sendPacket);
				}
			}
			break;
		}

		case (sf::Uint8)PacketIDs::ClientSyncCallback:
		{
			Client& client = NetworkManager::m_instance->GetCurrentSender();

			std::cout << "Server A is : " << TickManager::m_instance->GetCurrentTick() << std::endl ;
			std::cout << "Client B is : " << std::get<2>(client).currentClientTick << std::endl;
			
			//float latancyGap = ((float)TickManager::m_instance->GetCurrentTick() - (float)std::get<2>(client).currentClientTick) / 2.0f;

			float latancyGap = std::get<2>(client).tickCounter.GetCount() / 2;

			//std::get<2>(client).tickCounter.StopCounter();

			std::cout << "gap is " << latancyGap << std::endl;

			break;
		}
	}
}
