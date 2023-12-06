#include "TickManager.hpp"
#include <iostream>
#include "NetworkManager.hpp"
#include "PacketProcessing.hpp"
#include <chrono>

TickManager* TickManager::m_instance;

TickManager::TickManager()
{
	if (!m_instance)
	{
		m_instance = this;
	}
	m_currentTick = 0;
}

void TickManager::TickUpdate()
{
	m_currentTick++;

	m_currentTick %= m_tickRate + 1;

	std::cout << m_currentTick << std::endl;

	NetworkManager::m_instance->UpdateClientTickCounters();

	if (!NetworkManager::m_instance->m_clientsConnected.empty())
	{
		if (m_currentTick == m_tickRate)
		{
			sf::Packet sendPacket;

			sendPacket << -1;
			sendPacket << (sf::Uint8)PacketIDs::Ping;

			PacketProcessing::serverTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			NetworkManager::m_instance->SendToAllClients(sendPacket);
		}
	}
}

bool TickManager::DoTickUpdate()
{
	if (clock.getElapsedTime() >= sf::seconds(m_tickInterval))
	{
		clock.restart();
		return true;
	}
	return false;
}

void TickManager::InitialClientTickSync()
{
	sf::Packet sendPacket;

	sendPacket << -1;
	sendPacket << (sf::Uint8)PacketIDs::SyncClientTick;
	int clienttick = TickManager::m_instance->GetCurrentTick();
	sendPacket << clienttick;

	Client& client = NetworkManager::m_instance->GetCurrentSender();

	std::get<2>(client).tickCounter.StartCounter();

	std::get<2>(client).currentClientTick = clienttick;

	NetworkManager::m_instance->SendBack(sendPacket);
}
