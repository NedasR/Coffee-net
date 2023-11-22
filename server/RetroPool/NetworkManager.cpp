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

std::pair<sf::IpAddress, unsigned short> NetworkManager::GetRecentSender()
{
	std::pair<sf::IpAddress, unsigned short> current = std::make_pair(m_receivedIP, m_receivedPort);
	return current;
}

void NetworkManager::BindSocket(sf::IpAddress& ipAddress, unsigned short port)
{
	m_socket.bind(port, ipAddress);
}

void NetworkManager::SocketListen()
{
	// catch client inputs and other stuff for tick updates
	m_receivedPacket.clear();
	if (m_socket.receive(m_receivedPacket, m_receivedIP, m_receivedPort) == sf::Socket::Done)
	{
		PacketProcessing::ProcessPacket(m_receivedPacket);
	}
}

void NetworkManager::SendBack(sf::Packet& packet)
{
	m_socket.send(packet,m_receivedIP,m_receivedPort);
}

void NetworkManager::ConnectToServer()
{
	// will need to be reworked to implement disconnection
	ClientInfo clientInfo;
	m_clientsConnected.push_back(std::make_tuple(m_receivedIP, m_receivedPort, clientInfo));
	std::cout << "client has connected: " << m_receivedIP << " IP << >> port  " << m_receivedPort <<std::endl;
}

void NetworkManager::SendToAllClients(sf::Packet& packet)
{
	for (auto it : m_clientsConnected)
	{
		// temp fix
		//if (m_receivedIP == it.first && m_receivedPort == it.second) { continue; }
		m_socket.send(packet, std::get<0>(it), std::get<1>(it));
	}
}

Client& NetworkManager::GetCurrentSender()
{
	for( auto& it : m_clientsConnected)
	{
		if (std::get<0>(it) == m_receivedIP &&
			std::get<1>(it) == m_receivedPort)
		{
			return it;
		}
	}
}

void NetworkManager::SendToClient(Client& client, sf::Packet& packet)
{
	m_socket.send(packet, std::get<0>(client), std::get<1>(client));
}
