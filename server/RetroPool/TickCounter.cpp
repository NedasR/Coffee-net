#include "TickCounter.hpp"
#include <iostream>

TickCounter::TickCounter()
{
	m_startTickCount = false;
	m_tickCount = 0;
}

void TickCounter::StartCounter()
{
	m_startTickCount = true;
	ResetCount();
}

void TickCounter::StopCounter()
{
	m_startTickCount = false;
}

void TickCounter::ResetCount()
{
	m_tickCount = 0;
}

void TickCounter::UpdateTickCount()
{
	if (m_startTickCount)
	{
		m_tickCount += 1;
	}
}
