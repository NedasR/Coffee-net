#include "ProcessPacket.hpp"
#include <iostream>
#include "NetworkManager.hpp"
#include "RendererManager.hpp"
#include "NetSprite.hpp"
#include "Character.hpp"
#include <memory>
#include <chrono>
#include "TickManager.hpp"

void ProcessPacket::ReceiveUdpPackets(sf::Packet& packet)
{

	sf::Uint8 packetID;
	
	int tickstuff;
	//which tick we are on or if it is a tick packet or not
	packet >> tickstuff;

	packet >> packetID;

	switch (packetID)
	{
		case (sf::Uint8)PacketIDs::Ping:
		{

			sf::Packet sendPacket;
			sendPacket << (sf::Uint8)PacketIDs::Ping;
			NetworkManager::m_instance->SendBack(sendPacket);
			break;
		}

		case (sf::Uint8)PacketIDs::ReceiveNetworkID:
		{
			bool assignToLocalID;
			sf::Uint16 networkID;
			sf::Uint16 localID;

			packet >> assignToLocalID;
			packet >> networkID;
			packet >> localID;
			switch (assignToLocalID)
			{
				case true :
				{
					NetworkManager::m_instance->AssignNetID(networkID, localID);
					break;
				}

				case false :
				{
					NetworkManager::m_instance->AssignNetID(networkID);
					break;
				}
			}
			std::cout << networkID << " Got NetworkID " << NetworkManager::m_instance->NetworkIDExists(networkID) << std::endl;

			break;
		}

		case (sf::Uint8)PacketIDs::PostionUpdate:
		{
			sf::Uint16 NetworkID;
			// rework needed here to be server dictated
			float x,y;

			packet >> NetworkID >> x >> y;

			if (NetworkManager::m_instance->NetworkIDExists(NetworkID))
			{
			NetworkManager::m_instance->GetNetworkedObject(NetworkID).get()->setPosition(x,y);
			}
			break;
		}

		case (sf::Uint8)PacketIDs::SyncObject:
		{
			sf::Uint8 objectTypeId;
			packet >> objectTypeId;

			sf::Uint16 NetworkID;
			packet >> NetworkID;
			switch (objectTypeId)
			{
				case (sf::Uint8)ObjectTypeIDs::Character:
				{
					if (!NetworkManager::m_instance->NetworkIDExists(NetworkID))
					{
					std::shared_ptr<NetSprite> ptr = std::make_shared<Character>(NetworkID);
					RendererManager::image;
					RendererManager::texture;
					sf::Vector2f pos;
					packet >> pos.x >> pos.y;
					ptr.get()->setPosition(pos);
					ptr.get()->setScale(7, 7);
					ptr.get()->setTexture(RendererManager::texture);
					ptr.get()->setColor(sf::Color(sf::Color::Blue));
					RendererManager::AddToRenderer(ptr);
					ptr.get()->SyncNetworkID(NetworkID);

					}
					break;
				}

			}

			break;
		}

		case (sf::Uint8)PacketIDs::SendCurrentTick:
		{
			int tick;
			packet >> tick;
			std::cout << "TICK is : " << tick << std::endl;
			TickManager::m_instance->SetCurrentTick(tick);
			break;
		}

		case (sf::Uint8)PacketIDs::SyncClientTick:
		{
			int tick;
			packet >> tick;
			TickManager::m_instance->SetCurrentTick(tick);
			std::cout << "the server current tick is " << tick << std::endl;
			sf::Packet sendPacket;
			sendPacket << (sf::Uint8)PacketIDs::ClientSyncCallback;
			NetworkManager::m_instance->SendBack(sendPacket);
			

			break;
		}

		case (sf::Uint8)PacketIDs::TickAdjustment:
		{
			int tickAdjustment;
			packet >> tickAdjustment;
			int adjusted = TickManager::m_instance->getCurrentTick() + tickAdjustment;
			TickManager::m_instance->SetCurrentTick(adjusted);
			break;
		}

	}

}
