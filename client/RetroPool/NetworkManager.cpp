#include "NetworkManager.hpp"
#include "ProcessPacket.hpp"
#include <iostream>

NetworkManager* NetworkManager::m_instance = nullptr;

NetworkManager::NetworkManager()
{
    if (!m_instance)
    {
        m_instance = this;
    }

    if (m_socket.bind(m_clientPort, m_clientIP) == sf::Socket::Error) { std::cout << "failed to connect" << std::endl; }

    m_socket.setBlocking(false);
}

void NetworkManager::AssignNetID(sf::Uint16 id)
{
    NetSprite* prt = m_netIDAssignmentQueue.front();
    prt->SetNetworkID(id);
    m_networkId.emplace(id, prt);
    m_netIDAssignmentQueue.pop();
}

void NetworkManager::AddToNetwork(NetSprite& sprite)
{
    if(&sprite != nullptr)
    {
    m_netIDAssignmentQueue.push(&sprite);
    }
}

void NetworkManager::SocketListen()
{
    m_receivedPacket.clear();
    if (m_socket.receive(m_receivedPacket, m_recivedIP, m_recivedPort) == sf::Socket::Done);
    {
        ProcessPacket::ReceiveUdpPackets(m_receivedPacket);
    }
}

void NetworkManager::SendBack(sf::Packet& packet)
{
    m_socket.send(packet,m_recivedIP,m_recivedPort);
}

void NetworkManager::SendPacketServer(sf::Packet& packet)
{
    m_socket.send(packet, m_serverIP, m_serverPort);
}

void NetworkManager::ConnectToServer(sf::IpAddress ipaddress, unsigned short port)
{
    sf::Packet packet;
    packet << (sf::Uint8)PacketIDs::ConnectToServer;
    m_socket.send(packet,ipaddress,port);
}
