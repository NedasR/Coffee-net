#include "RendererManager.hpp"
#include <string>
std::map<std::string, std::vector<std::shared_ptr<NetSprite>>> RendererManager::RenderList;

void RendererManager::Render(std::shared_ptr<NetSprite> sprite)
{
	RenderList["default"].push_back(sprite);
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

void RendererManager::UpdateTheList(sf::Event& event)
{
	for (auto it : RenderList["default"])
	{
		it.get()->Update(event);
	}
}
