#pragma once
#include <SFML/Network.hpp>

#include "PacketProcessing.hpp"
#include "NetworkManager.hpp"

class Server
{
	private:

	public:

	Server(sf::IpAddress& serverAddress,unsigned short serverPort);

	void ServerLoop();

	void ServerInit();


};