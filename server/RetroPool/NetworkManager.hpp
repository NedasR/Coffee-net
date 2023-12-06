#pragma once
#include <SFML/Network.hpp>
#include <chrono>
#include <vector>
#include "TickCounter.hpp"

#define NETWORK_LATENCY_SIMULATOR true
#define NETWORK_LATENCY_RTT_MS 100

struct ClientInfo
{
	std::chrono::milliseconds RTT;
	int currentClientTick;
	TickCounter tickCounter;

	// make an ID for each new client if they don't have an ID then give them one
};

struct DelayedPacket
{
	sf::Packet packet;
	sf::Clock counter;
	sf::IpAddress IP;
	unsigned int port;
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

	std::vector<DelayedPacket> DelayedPacketReceivingList;

	std::vector<DelayedPacket> DelayedPacketSendingList;

	NetworkManager();

	// old code
	std::pair<sf::IpAddress, unsigned short> GetRecentSender();
	//ends here
	static NetworkManager* m_instance;

	void BindSocket(sf::IpAddress& ipAddress,unsigned short port);

	void SocketListen();

	void SendBack(sf::Packet& packet);

	void ConnectToServer();

	void SendToAllClients(sf::Packet& packet);

	void Send(sf::Packet packet,sf::IpAddress ip,unsigned int port);

	void SendToClient(Client& client,sf::Packet& packet);

	void DelayedPacketReceiving(sf::Packet& packet);

	void ProcessDelayedPackets();

	void DelayedPacketSending(sf::Packet& packet, sf::IpAddress ip, unsigned int port);

	Client& GetCurrentSender();

	void UpdateClientTickCounters();
};