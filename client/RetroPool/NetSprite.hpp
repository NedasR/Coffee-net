#pragma once
#include <SFML/Graphics.hpp>
class NetSprite : public sf::Sprite
{
	private:

	protected:
	sf::Uint16 m_networkID = 0;


	void RequastNetworkID();

	public:

	NetSprite();

	virtual void Update(sf::Event& event) = 0;

	virtual inline sf::Uint16 GetNetworkID(){ return m_networkID; }

	virtual inline void SetNetworkID(sf::Uint16 id) { m_networkID = id; }

};