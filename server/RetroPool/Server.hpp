#pragma once
#include <SFML/Network.hpp>

#include "PacketProcessing.hpp"

class Server
{
	private:

	sf::IpAddress m_serverAddress;
	unsigned int m_serverPort;
	sf::UdpSocket m_socket;

	public:

	Server(sf::IpAddress serverAddress,unsigned int serverPort): m_serverAddress(serverAddress), m_serverPort(serverPort)
	{
		m_socket.bind(serverPort, serverAddress);
	};




};