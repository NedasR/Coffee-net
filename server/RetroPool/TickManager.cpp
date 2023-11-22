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
	if (m_currentTick > m_tickRate)
	{
		m_currentTick = 0;
	}
	std::cout << m_currentTick << std::endl;

	if (!NetworkManager::m_instance->m_clientsConnected.empty())
	{
	sf::Packet sendPacket;

	sendPacket << -1;
	sendPacket << (sf::Uint8)PacketIDs::Ping;

	PacketProcessing::serverTimeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	NetworkManager::m_instance->SendToClient(NetworkManager::m_instance->m_clientsConnected[0], sendPacket);
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
