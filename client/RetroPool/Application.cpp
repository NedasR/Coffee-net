#include "Application.hpp"
#include "ProcessPacket.hpp"

void Application::GameInit()
{
    m_window.create(sf::VideoMode(400, 400), "Coffee's Client");

	m_currentScene = std::make_shared<Scene>();

	m_headScene = m_currentScene.get();

    if (socket.bind(m_clientPort, m_clientIP) == sf::Socket::Error) {std::cout << "failed to connect"<<std::endl;}

    socket.setBlocking(false);

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
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S && !Binded)
                {
                    std::cout << "please put in the port" << std::endl;
                    //std::cin >> serverPort;

                    Binded = true;
                }

                if (event.key.code == sf::Keyboard::D && Binded)
                {
                    std::string words;

                    std::cout << "write something" << std::endl;

                    std::getline(std::cin, words);

                    socket.send(words.c_str(), words.size(), "192.168.1.153", m_serverPort);
                }
            }
        }

        sf::Packet packet;
        packet << (sf::Uint8)PacketIDs::RequastNetworkID;

        socket.send(packet,m_serverIP,m_serverPort);

        //here
        sf::IpAddress ip;
        unsigned short port = 0;
        m_receivedPacket.clear();
        if (socket.receive(m_receivedPacket, ip, port) == sf::Socket::Done);
        {
        ProcessPacket::ReceiveUdpPackets(m_receivedPacket);
        }

        if (m_headScene)
        {
            m_headScene->Update();
        }

        m_window.clear();
        //window.draw();
        m_window.display();
    }

	Render();
}

void Application::Render()
{

}

/*
TODO LIST
-Implement network id's so each netSprite is Networked    <-- test this since it is very important it will be the core of the game

-make a scene that has a player that is a circle and multiple client support so to players can move there respective character

*/