#include "NetworkManager.hpp"
#include "PacketProcessing.hpp"
#include <iostream>

NetworkManager* NetworkManager::m_instance = nullptr;

NetworkManager::NetworkManager()
{
	if (!m_instance)
	{
		m_instance = this;
	}

	m_socket.setBlocking(false);
}

void NetworkManager::BindSocket(sf::IpAddress& ipAddress, unsigned short port)
{
	m_socket.bind(port, ipAddress);
}

void NetworkManager::SocketListen()
{
	if (m_socket.receive(m_receivedPacket, m_receivedIP, m_receivedPort) == sf::Socket::Done)
	{
		PacketProcessing::ProcessPacket(m_receivedPacket);
	}
}

void NetworkManager::SendBack(sf::Packet& packet)
{
	m_socket.send(packet,m_receivedIP,m_receivedPort);
}
