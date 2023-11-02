#pragma once
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "NetSprite.hpp"
#include "Character.hpp"

class RendererManager
{
	void Render(std::shared_ptr<NetSprite> sprite);

	public:
	//move to private at some point
	static std::map<std::string, std::vector<std::shared_ptr<NetSprite>>> RenderList;

	RendererManager();

	//to be removed and a list of textures should exist
	static sf::Texture texture;

	static sf::Image image;

	static void AddToRenderer(std::shared_ptr<NetSprite> sprite);

	void RenderTheList(sf::RenderWindow& window);

	void UpdateTheList();
};