#pragma once
#include <SFML/Network.hpp>

class ConnectionHandler
{
	private:
	sf::TcpSocket m_tcpSocket;
	sf::Clock m_timer;
	sf::Time m_timeOut = sf::seconds(2);
	sf::Packet packet;

	public:
	
	void PingListener();

};