#pragma once
#include <SFML/Graphics.hpp>

class Scene
{
	private:


	public:

	virtual void LoadScene() = 0;

	virtual void Update() = 0;
};