#pragma once
#include <SFML/Network.hpp>

#include "PacketProcessing.hpp"
#include "NetworkManager.hpp"
#include <SFML/Graphics.hpp>
#include "TickManager.hpp"

class Server
{
	private:

	sf::RenderWindow m_window;

	TickManager m_tickManager;

	public:

	Server(sf::IpAddress& serverAddress,unsigned short serverPort);

	void ServerLoop();

	void ServerInit();


};