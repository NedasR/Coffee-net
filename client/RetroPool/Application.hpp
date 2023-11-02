#pragma once

#include <memory>
#include "Scene.hpp"
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "NetworkManager.hpp"
#include "CircleScene.hpp"
#include "RendererManager.hpp"
#include "Character.hpp"
class Application
{
	private:

	std::shared_ptr<Scene> m_currentScene;

	Scene* m_headScene = nullptr;

	sf::RenderWindow m_window;

	NetworkManager networkManager;

	CircleScene Cscene;

	RendererManager m_renderMag;

	public:

	inline sf::RenderWindow& GetWindow(){return m_window;}

	void GameInit();

	void GameLoop();

	private:

	void Render();
};