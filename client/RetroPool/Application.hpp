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

	sf::RenderWindow window;
	std::string clientIP = "192.168.1.153";
	unsigned int serverPort = 60000;

	bool Binded = true;

	Scene* m_headScene;

	public:

	static sf::UdpSocket socket;

	void GameInit();

	void GameLoop();

	private:
	void Render();
};