#include "ProcessPacket.hpp"
#include <iostream>
#include "NetworkManager.hpp"
#include "RendererManager.hpp"
#include "NetSprite.hpp"
#include "Character.hpp"
#include <memory>

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
			//std::cout << NetworkID << " update " << NetworkManager::m_instance->NetworkIDExists(NetworkID) << std::endl;
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
					ptr.get()->setPosition(20.0f, 20.0f);
					ptr.get()->setScale(7, 7);
					ptr.get()->setTexture(RendererManager::texture);
					ptr.get()->setColor(sf::Color(sf::Color::Blue));
					RendererManager::AddToRenderer(ptr);
					ptr.get()->SyncNetworkID(NetworkID);
					//NetworkManager::m_instance->SyncNetID(NetworkID, ptr);
					}
					break;
				}

			}

			break;
		}
	}

}
