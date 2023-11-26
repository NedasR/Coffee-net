#include "NetworkManager.hpp"
#include "PacketProcessing.hpp"
#include <iostream>
#include "TickManager.hpp"

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
		if (NETWORK_LATENCY_SIMULATOR)
		{
			PacketProcessing::ProcessPacket(m_receivedPacket);
		}
		else
		{
			DelayedPacketReceiving(m_receivedPacket);
		}
	}
	if (NETWORK_LATENCY_SIMULATOR) {ProcessDelayedPackets();};
}

void NetworkManager::SendBack(sf::Packet& packet)
{
	Send(packet,m_receivedIP,m_receivedPort);
}

void NetworkManager::ConnectToServer()
{
	// will need to be reworked to implement disconnection
	ClientInfo clientInfo;
	m_clientsConnected.push_back(std::make_tuple(m_receivedIP, m_receivedPort, clientInfo));
	std::cout << "client has connected: " << m_receivedIP << " IP << >> port  " << m_receivedPort <<std::endl;
	sf::Packet packet;
	packet << (sf::Uint8)PacketIDs::SendCurrentTick;
	packet << TickManager::m_instance->GetCurrentTick();
	SendBack(packet);
}

void NetworkManager::SendToAllClients(sf::Packet& packet)
{
	for (auto it : m_clientsConnected)
	{
		// temp fix
		// we might want to exclude a client
		//if (m_receivedIP == it.first && m_receivedPort == it.second) { continue; }
		Send(packet, std::get<0>(it), std::get<1>(it));
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
	//add return here might need to change return to a pointer 
}

void NetworkManager::ProcessDelayedPackets()
{
	auto it = DelayedPacketReceivingList.begin();
	while (it != DelayedPacketReceivingList.end())
	{
		if (it->counter.getElapsedTime() >= sf::milliseconds(NETWORK_LATENCY_RTT_MS / 2))
		{
			m_receivedIP = it->IP;
			m_receivedPort = it->port;
			PacketProcessing::ProcessPacket(it->packet);
			it = DelayedPacketReceivingList.erase(it);
		}
		else
		{
			++it;
		}
	}

	auto its = DelayedPacketSendingList.begin();
	while (its != DelayedPacketSendingList.end())
	{
		if (its->counter.getElapsedTime() >= sf::milliseconds(NETWORK_LATENCY_RTT_MS / 2))
		{
			Send(it->packet,it->IP,it->port);
			its = DelayedPacketSendingList.erase(it);
		}
		else
		{
			++its;
		}
	}
}

void NetworkManager::DelayedPacketSending(sf::Packet& packet,sf::IpAddress& ip,unsigned int port)
{
	DelayedPacket delayedPacket;
	delayedPacket.packet = packet;
	delayedPacket.IP = ip;
	delayedPacket.port = port;

	DelayedPacketReceivingList.push_back(delayedPacket);
}

void NetworkManager::Send(sf::Packet& packet, sf::IpAddress ip, unsigned int port)
{
	m_socket.send(packet, ip, port);
}

void NetworkManager::SendToClient(Client& client, sf::Packet& packet)
{
	Send(packet, std::get<0>(client), std::get<1>(client));
}

void NetworkManager::DelayedPacketReceiving(sf::Packet& packet)
{
	DelayedPacket delayedPacket;
	delayedPacket.packet = packet;
	delayedPacket.IP = m_receivedIP;
	delayedPacket.port = m_receivedPort;
	
	DelayedPacketReceivingList.push_back(delayedPacket);
}