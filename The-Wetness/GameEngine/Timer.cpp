/// \file       Timer.cpp
/// \date       07/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Timer.hpp"

/// \brief Constructor of the timer
///		   Initializes frequency
Timer::Timer(void)
{
	QueryPerformanceCounter(&m_lastUpdateTime);

	LARGE_INTEGER li_freq;
	QueryPerformanceFrequency(&li_freq);

	m_frequency = li_freq.QuadPart;
	m_frequency /= 1000;
}

/// \brief Start the timer
void Timer::Start(void)
{
	QueryPerformanceCounter(&m_lastUpdateTime);
}

/// \brief	Returns the elapsed time
/// \param  restart (false by default), reset the elapsed time if true
/// \return The elapsed time
float Timer::GetElaspedTime(bool restart)
{
	LARGE_INTEGER timeNow;
	QueryPerformanceCounter(&timeNow);
	LONGLONG elapsedLong = timeNow.QuadPart - m_lastUpdateTime.QuadPart;

	float elapsed = static_cast<float>(
		static_cast<float>(elapsedLong) / 
		static_cast<float>(m_frequency));

	elapsed /= 1000.0f;

	if (restart)
	{
		m_lastUpdateTime = timeNow;
	}

	return elapsed;
}