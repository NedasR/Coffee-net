#pragma once
#include <SFML/Network.hpp>
#include "NetSprite.hpp"
#include <unordered_map>
#include <queue>
#include <memory>

class NetworkManager
{
	private:

	sf::IpAddress m_serverIP = sf::IpAddress("192.168.1.162");
	unsigned short m_serverPort = 60000;

	sf::IpAddress m_clientIP = sf::IpAddress("192.168.1.162");
	unsigned short m_clientPort = sf::Socket::AnyPort;

	sf::IpAddress m_recivedIP;
	unsigned short m_recivedPort = 0;

	sf::UdpSocket m_socket;
	sf::Packet m_receivedPacket;

	std::unordered_map<sf::Uint16, std::shared_ptr<NetSprite>> m_networkId;

	std::queue<std::shared_ptr<NetSprite>> m_netIDAssignmentQueue;

	std::vector<std::shared_ptr<NetSprite>> m_LocalToNetAssignmentQueue;

	bool m_lateJoinerSynced = false;

	public:

	static NetworkManager* m_instance;

	NetworkManager();

	void SyncNetID(sf::Uint16 id, std::shared_ptr<NetSprite>& sprite);

	void AssignNetID(sf::Uint16 id);

	void AssignNetID(sf::Uint16 id, sf::Uint16 localID);

	void AddToNetwork(std::shared_ptr<NetSprite> sprite);

	void AddToNetwork(std::shared_ptr<NetSprite> sprite,bool local);

	void SocketListen();

	void SendBack(sf::Packet& packet);

	void SendPacketServer(sf::Packet& packet);

	void ConnectToServer(sf::IpAddress ipaddress,unsigned short port); 

	bool NetworkIDExists(sf::Uint16 networkID);

	void SyncLateJoiner();

	std::shared_ptr<NetSprite> GetNetworkedObject(sf::Uint16 networkID);

};