#include "Server.hpp"
#include "PacketProcessing.hpp"

Server::Server(sf::IpAddress& serverAddress, unsigned short serverPort)
{
	NetworkManager::m_instance->BindSocket(serverAddress, serverPort);

    tickRateFont.loadFromFile("assets/arial.ttf");
    tickRate.setFont(tickRateFont);
    //tickRate.setCharacterSize(24);
}

void Server::ServerLoop()
{
    m_window.setFramerateLimit(60);
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
        tickRate.setString(std::to_string(TickManager::m_instance->GetCurrentTick()));
        m_window.draw(tickRate);
        m_window.display();
    }
}

void Server::ServerInit()
{
	std::srand(std::time(nullptr));

    m_window.create(sf::VideoMode(400, 400), "Coffee's Server");
}
