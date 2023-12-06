#include "RendererManager.hpp"
#include <iostream>
std::map<std::string, std::vector<std::shared_ptr<NetSprite>>> RendererManager::RenderList;

sf::Texture RendererManager::texture;

sf::Image RendererManager::image;

void RendererManager::Render(std::shared_ptr<NetSprite> sprite)
{
	RenderList["default"].push_back(sprite);
}

RendererManager::RendererManager()
{
	image.create(20, 20, sf::Color::Blue);
	texture.loadFromImage(image);
}

void RendererManager::AddToRenderer(std::shared_ptr<NetSprite> sprite)
{
	RenderList["default"].push_back(sprite);
}

void RendererManager::RenderTheList(sf::RenderWindow& window)
{
	for (auto it : RenderList["default"])
	{
		window.draw(*it.get());
	}
}

void RendererManager::UpdateTheList()
{
	for (auto it : RenderList["default"])
	{
		it.get()->Update();
	}
}
