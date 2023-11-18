#pragma once
#include "NetSprite.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Character : public NetSprite
{
	private:

	void Controls();

	float speed;

	public:

	Character();

	Character(bool useLocalID);

	Character(sf::Uint16 networkIdSync);

	bool isMain = false;

	void Update() override;
};
