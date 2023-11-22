#pragma once
#include <SFML/Graphics.hpp>

class TickManager
{
	private:

	float m_tickRate = 30.0f;

	float m_tickInterval = 1 / m_tickRate;

	int m_currentTick;

	sf::Clock clock;

	public:

	TickManager();

	static TickManager* m_instance;

	void TickUpdate();

	bool DoTickUpdate();

	inline int GetCurrentTick(){return m_currentTick;}


	
};