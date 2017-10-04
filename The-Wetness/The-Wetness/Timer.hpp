/// \file       Timer.hpp
/// \date       04/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <cassert>
#include <Windows.h>

/// \class  Timer
/// \brief  Manages time 
class Timer
{
public:

	explicit Timer(void);
	void	 Start(void);

	float	 GetElaspedTime(bool restart = false);

private:

	LONGLONG	  m_frequency;
	LARGE_INTEGER m_lastUpdateTime;
};

#endif // _TIMER_HPP
