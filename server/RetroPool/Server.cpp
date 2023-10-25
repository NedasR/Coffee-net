#include "Server.hpp"
#include "PacketProcessing.hpp"
#include <SFML/Graphics.hpp>

Server::Server(sf::IpAddress& serverAddress, unsigned short serverPort)
{
	NetworkManager::m_instance->BindSocket(serverAddress, serverPort);
}

void Server::ServerLoop()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Coffee's Server");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        NetworkManager::m_instance->SocketListen();

        window.clear();
        //window.draw();
        window.display();
    }
}

void Server::ServerInit()
{
	std::srand(std::time(nullptr));
}
