#include "Delta.hpp"


sf::Clock Delta::clock;

float Delta::m_Time;

float Delta::Time()
{
    return m_Time;
}

void Delta::ResetDeltaTime()
{
    m_Time = clock.restart().asSeconds();
}
