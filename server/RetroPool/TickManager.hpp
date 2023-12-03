#pragma once
#include <SFML/Graphics.hpp>

class TickManager
{
	private:

	int m_tickRate = 10;

	float m_tickInterval = 1.0f / m_tickRate;

	int m_currentTick;

	bool m_startTickCount = false;

	sf::Clock clock;

	public:

	TickManager();

	static TickManager* m_instance;

	void TickUpdate();

	bool DoTickUpdate();

	inline int GetCurrentTick(){return m_currentTick;}

	void InitialClientTickSync();

};