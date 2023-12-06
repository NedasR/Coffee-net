#pragma once
#include <SFML/System/Clock.hpp>

class Delta
{
	public:

	static sf::Clock clock;

	static float m_Time;


	static float Time();

	static void ResetDeltaTime();
};