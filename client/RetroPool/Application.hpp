#pragma once

#include <memory>
#include "Scene.hpp"
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class Application
{
	private:

	std::shared_ptr<Scene> m_currentScene;

	sf::RenderWindow m_window;
	sf::IpAddress m_serverIP = sf::IpAddress("192.168.1.153");
	unsigned short m_serverPort = 60000;

	sf::IpAddress m_clientIP = sf::IpAddress("192.168.1.153");
	unsigned short m_clientPort = 60001;

	bool Binded = true;

	Scene* m_headScene;

	public:

	sf::UdpSocket socket;

	sf::Packet m_receivedPacket;

	void GameInit();

	void GameLoop();

	private:
	void Render();
};