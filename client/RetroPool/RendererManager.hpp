#pragma once

#include <map>;
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "NetSprite.hpp"
#include "Character.hpp"

class RendererManager
{
	static std::map<std::string, std::vector<std::shared_ptr<NetSprite>>> RenderList;

	void Render(std::shared_ptr<NetSprite> sprite);

	public:

	static void AddToRenderer(std::shared_ptr<NetSprite> sprite);

	void RenderTheList(sf::RenderWindow& window);

	void UpdateTheList(sf::Event& event);
};