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

	//inline sf::Uint16 GetNetworkID() {return m_networkID;}

	//inline void SetNetworkID(sf::Uint16 id) { m_networkID = id; }
};
