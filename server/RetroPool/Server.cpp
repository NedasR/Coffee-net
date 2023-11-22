#include "Server.hpp"
#include "PacketProcessing.hpp"

Server::Server(sf::IpAddress& serverAddress, unsigned short serverPort)
{
	NetworkManager::m_instance->BindSocket(serverAddress, serverPort);
}

void Server::ServerLoop()
{
    while (m_window.isOpen())
    {
        if (m_tickManager.DoTickUpdate())
        {
            m_tickManager.TickUpdate();
        }

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
        }

        NetworkManager::m_instance->SocketListen();

        m_window.clear();
        //window.draw();
        m_window.display();
    }
}

void Server::ServerInit()
{
	std::srand(std::time(nullptr));

    m_window.create(sf::VideoMode(400, 400), "Coffee's Server");
}
