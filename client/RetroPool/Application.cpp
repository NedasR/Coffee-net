#include "Application.hpp"

void Application::GameInit()
{
    window.create(sf::VideoMode(400, 400), "Coffee's Client");

	m_currentScene = std::make_shared<Scene>();

	m_headScene = m_currentScene.get();

	m_headScene->LoadScene();
}

void Application::GameLoop()
{
    while (window.isOpen())
    {
        //change from here to
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
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

                    socket.send(words.c_str(), words.size(), "192.168.1.153", serverPort);
                }
            }
        }
        //here

        if (m_headScene)
        {
            m_headScene->Update();
        }

        window.clear();
        //window.draw();
        window.display();
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