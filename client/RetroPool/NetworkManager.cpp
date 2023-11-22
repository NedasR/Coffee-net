#include "NetworkManager.hpp"
#include "ProcessPacket.hpp"
#include <iostream>
#include "TickManager.hpp"

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

void NetworkManager::SyncNetID(sf::Uint16 id, std::shared_ptr<NetSprite>& sprite)
{
    sprite->SetNetworkID(id);
    m_networkId[id] = sprite;
    std::cout << sprite.get()->GetNetworkID() << "New synced ID" << std::endl;
}

void NetworkManager::AssignNetID(sf::Uint16 id)
{
    std::shared_ptr<NetSprite> ptr = m_netIDAssignmentQueue.front();
    ptr->SetNetworkID(id);
    std::pair<sf::Uint16, std::shared_ptr<NetSprite>> pair = std::make_pair(id, ptr);
    m_networkId[id] = ptr;
    m_netIDAssignmentQueue.pop();
}

void NetworkManager::AssignNetID(sf::Uint16 id, sf::Uint16 localID)
{
    std::shared_ptr<NetSprite> ptr = m_LocalToNetAssignmentQueue.front();
    if (ptr->GetLocalID() == localID)
    {
        ptr->SetNetworkID(id);
        m_LocalToNetAssignmentQueue.erase(m_LocalToNetAssignmentQueue.begin());
    }
    else // if it is the wrong id it will go trough the rest of the list
    {
        int count = 0;
        for (auto it : m_LocalToNetAssignmentQueue)
        {
            if (it->GetLocalID() == localID)
            {
                it->SetNetworkID(id);
                m_LocalToNetAssignmentQueue.erase(m_LocalToNetAssignmentQueue.begin() + count);
                break;
            }
            count++;
        }
    }
    std::pair<sf::Uint16, std::shared_ptr<NetSprite>> pair = std::make_pair(id, ptr);
    m_networkId.emplace(pair);
}

void NetworkManager::AddToNetwork(std::shared_ptr<NetSprite> sprite)
{

    // rework in the near future
    if (sprite == nullptr)
    {
        std::cerr << "Error: The object is invalid." << std::endl;
        return;
    }
    m_netIDAssignmentQueue.push(sprite);
}

void NetworkManager::AddToNetwork(std::shared_ptr<NetSprite> sprite,bool local)
{
    // rework in the near future this too
    if (sprite == nullptr)
    {
        std::cerr << "Error: The object is invalid." << std::endl;
        return;
    }
    m_LocalToNetAssignmentQueue.push_back(sprite);
}

void NetworkManager::SocketListen()
{
    m_receivedPacket.clear();
    if (m_socket.receive(m_receivedPacket, m_recivedIP, m_recivedPort) == sf::Socket::Done)
    {
        if (TickManager::m_instance->IsTickPacket(m_receivedPacket))
        {
            TickManager::m_instance->SaveTickPacket(m_receivedPacket);
        } 
        else
        {
            ProcessPacket::ReceiveUdpPackets(m_receivedPacket);
        }
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
    packet << false;
    m_socket.send(packet,ipaddress,port);
}

bool NetworkManager::NetworkIDExists(sf::Uint16 networkID)
{
    if (m_networkId[networkID])
    {
        std::cout << networkID << " id dose exist" << std::endl;
        return true;
    }
    std::cout << networkID << " id dose not exist" << std::endl;
    return false;
}

void NetworkManager::SyncLateJoiner()
{
    if(m_netIDAssignmentQueue.empty() && !m_lateJoinerSynced)
    {
    sf::Packet packet;
    packet << (sf::Uint8)PacketIDs::LateJoinerSync;
    NetworkManager::m_instance->SendPacketServer(packet);
    m_lateJoinerSynced = true;
    }
}

std::shared_ptr<NetSprite> NetworkManager::GetNetworkedObject(sf::Uint16 networkID)
{
    if (!m_networkId[networkID])
    {
        std::cout << "dose not exist" <<std::endl;
    }
    return m_networkId[networkID];
}
