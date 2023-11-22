#pragma once
#include <SFML/Network.hpp>
#include <chrono>

struct ClientInfo
{
	std::chrono::milliseconds RTT;
	// make an ID for each new client if they don't have an ID then give them one
};

typedef std::tuple<sf::IpAddress, unsigned short, ClientInfo> Client;

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

	std::vector<Client> m_clientsConnected;

	NetworkManager();

	std::pair<sf::IpAddress, unsigned short> GetRecentSender();

	static NetworkManager* m_instance;

	void BindSocket(sf::IpAddress& ipAddress,unsigned short port);

	void SocketListen();

	void SendBack(sf::Packet& packet);

	void ConnectToServer();

	void SendToAllClients(sf::Packet& packet);

	void SendToClient(Client& client,sf::Packet& packet);

	Client& GetCurrentSender();
};