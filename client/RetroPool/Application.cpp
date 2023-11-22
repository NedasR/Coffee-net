
#include "Application.hpp"
#include "ProcessPacket.hpp"

void Application::GameInit()
{
    Delta::ResetDeltaTime();

    m_window.create(sf::VideoMode(400, 400), "Coffee's Client");

    m_window.setFramerateLimit(30);

    NetworkManager::m_instance->ConnectToServer(sf::IpAddress("192.168.1.153"),(unsigned short)60000);

	m_headScene = &Cscene;

	m_headScene->LoadScene();

}

void Application::GameLoop()
{
    while (m_window.isOpen())
    {

        //change from here to

        if (m_tickManager.DoTickUdpate())
        {
            m_tickManager.TickUdpate();
        }
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                m_window.hasFocus();
            }
        }
        if (m_window.hasFocus())
        {
        m_renderMag.UpdateTheList();
        }


        networkManager.SocketListen();

        networkManager.SyncLateJoiner(); // will need to be moved to like a application update client 

        if (m_headScene)
        {
            m_headScene->Update();
        }

        Render();
        Delta::ResetDeltaTime();
    }
}

void Application::Render()
{
    m_window.clear();
    m_renderMag.RenderTheList(m_window);
    m_window.display();
}

/*
TODO LIST
update positions of sprites when the late joiner joins since right now i it only updates when a sprite moves 

*/