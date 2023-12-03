#pragma once

#include <SFML/Network.hpp>
#include <map>
#include <vector>

class TickManager
{
	private:

	int m_tickRate = 10;

	float m_tickInterval = 1.0f / m_tickRate;

	int m_currentTick = 0;

	sf::Clock m_clock;

	public:

	static TickManager* m_instance;

	static std::map<int,std::vector<sf::Packet>> tickCache;

	TickManager();

	void TickUdpate();

	bool DoTickUdpate();

	bool IsTickPacket(sf::Packet packet);

	inline void SetCurrentTick(unsigned int currentTick) { m_currentTick = currentTick; }

	inline int getCurrentTick(){return m_currentTick;}

	//pass by reference in the near future
	void SaveTickPacket(sf::Packet packet);

};