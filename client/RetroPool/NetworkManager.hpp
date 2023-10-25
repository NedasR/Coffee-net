#pragma once
#include <SFML/Network.hpp>
#include "NetSprite.hpp"
#include <unordered_map>
#include <queue>

class NetworkManager
{
	private:

	sf::IpAddress m_serverIP = sf::IpAddress("192.168.1.153");
	unsigned short m_serverPort = 60000;

	sf::IpAddress m_clientIP = sf::IpAddress("192.168.1.153");
	unsigned short m_clientPort = 60001;

	sf::IpAddress m_recivedIP;
	unsigned short m_recivedPort = 0;

	sf::UdpSocket m_socket;
	sf::Packet m_receivedPacket;

	std::unordered_map<sf::Uint16,NetSprite*> m_networkId;

	std::queue<NetSprite*> m_netIDAssignmentQueue;

	public:

	static NetworkManager* m_instance;

	NetworkManager();

	void AssignNetID(sf::Uint16 id);

	void AddToNetwork(NetSprite& sprite);

	void SocketListen();

	void SendBack(sf::Packet& packet);

	void SendPacketServer(sf::Packet& packet);

	void ConnectToServer(sf::IpAddress ipaddress,unsigned short port); 

};