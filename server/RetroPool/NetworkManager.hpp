#pragma once
#include <SFML/Network.hpp>

class NetworkManager
{
	private:

	sf::IpAddress m_serverAddress;
	unsigned short m_serverPort;
	sf::UdpSocket m_socket;

	unsigned short m_receivedPort;
	sf::IpAddress m_receivedIP;
	sf::Packet m_receivedPacket;

	public:
	// needs change
	std::vector<std::pair<sf::IpAddress, unsigned short>> m_clientsConnected;

	NetworkManager();

	std::pair<sf::IpAddress, unsigned short> GetRecentSender();

	static NetworkManager* m_instance;

	void BindSocket(sf::IpAddress& ipAddress,unsigned short port);

	void SocketListen();

	void SendBack(sf::Packet& packet);

	void ConnectToServer();

	void SendToAllClients(sf::Packet& packet);
};