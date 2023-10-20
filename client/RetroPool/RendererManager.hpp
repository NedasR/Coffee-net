#pragma once

#include <map>;
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

class RendererManager
{
	std::map<std::string, std::vector<std::shared_ptr<sf::Sprite>>> RenderList;

	public:

		static void AddToRenderer(sf::Sprite sprite);
};