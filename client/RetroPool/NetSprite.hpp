#pragma once
#include <SFML/Graphics/Sprite.hpp>
class NetSprite : public sf::Sprite
{
	private:
	sf::Uint16 m_networkID;


	void RequastNetworkID();

	public:

	virtual void Update();

};