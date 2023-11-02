#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "ProcessPacket.hpp"
class NetSprite : public sf::Sprite , public std::enable_shared_from_this<NetSprite>
{
	private:

	protected:

	sf::Uint16 m_networkID = 0;

	static sf::Uint16 m_localIDCount;

	sf::Uint8 objectTypeID = 0;

	sf::Uint16 LocalID = 0;

	void RequastNetworkID(bool useLocalID);

	public:

	std::shared_ptr<NetSprite> m_itSelf;

	NetSprite();

	NetSprite(bool useLocalID);

	NetSprite(sf::Uint16 networkIdSync);

	void SyncNetworkID(sf::Uint16 networkedID);

	void SyncToNetwork();

	void SyncToNetwork(bool local);

	virtual void Update() = 0;

	inline sf::Uint16 GetNetworkID(){ return m_networkID; }

	inline sf::Uint16 GetLocalID() { return LocalID; }

	inline void SetNetworkID(sf::Uint16 id) { m_networkID = id; }

};