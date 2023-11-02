#pragma once
#include "Scene.hpp"
#include <memory>
#include "Character.hpp"
#include <SFML/Graphics.hpp>
class CircleScene : public Scene
{
	private:
		sf::Texture texture;
		sf::Image image;
	public:

	void LoadScene();

	void Update();
};