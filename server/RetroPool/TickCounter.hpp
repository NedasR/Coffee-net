#pragma once
class TickCounter
{
	private:

	bool m_startTickCount;

	int m_tickCount;

	public:

	TickCounter();

	void StartCounter();

	void StopCounter();

	void ResetCount();

	inline int GetCount(){return m_tickCount;}

	void UpdateTickCount();

};