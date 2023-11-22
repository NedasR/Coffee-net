#include "ProcessPacket.hpp"
#include <iostream>
#include "NetworkManager.hpp"
#include "RendererManager.hpp"
#include "NetSprite.hpp"
#include "Character.hpp"
#include <memory>
#include <chrono>

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
			std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			sendPacket << (sf::Uint8)PacketIDs::Ping;
			sendPacket << static_cast<std::uint64_t>(time.count());
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
	}

}
