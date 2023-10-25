#pragma once
#include "NetSprite.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class Character : public NetSprite
{
	private:

	void Controls(sf::Event& event);

	public:

	Character();

	bool isMain = false;

	void Update(sf::Event& event) override;

	inline sf::Uint16 GetNetworkID() {return m_networkID;}

	inline void SetNetworkID(sf::Uint16 id) { m_networkID = id; }
};
