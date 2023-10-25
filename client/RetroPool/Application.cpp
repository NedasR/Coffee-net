#include "Application.hpp"
#include "ProcessPacket.hpp"

void Application::GameInit()
{
    m_window.create(sf::VideoMode(400, 400), "Coffee's Client");

    NetworkManager::m_instance->ConnectToServer(sf::IpAddress("192.168.1.153"),(unsigned short)60000);

	m_headScene = &Cscene;

	m_headScene->LoadScene();

}

void Application::GameLoop()
{
    while (m_window.isOpen())
    {
        //change from here to
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            m_renderMag.UpdateTheList(event);
        }
        //here
        //sf::Packet packet;
        //packet << (sf::Uint8)PacketIDs::RequastNetworkID;            

        //networkManager.SendPacketServer(packet);

        networkManager.SocketListen();

        if (m_headScene)
        {
            m_headScene->Update();
        }

        m_window.clear();
        m_renderMag.RenderTheList(m_window);
        m_window.display();
    }
}

void Application::Render()
{

}

/*
TODO LIST
-Implement network id's so each netSprite is Networked    <-- test this since it is very important it will be the core of the game

-make a scene that has a player that is a circle and multiple client support so to players can move there respective character

*/