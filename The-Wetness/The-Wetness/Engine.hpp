/// \file       Engine.hpp
/// \date       04/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "Timer.hpp"
#include "Window.hpp"

/// \class  Engine
/// \brief  Manages time 
class Engine
{
public:

	explicit Engine (void);
	        ~Engine (void);

	void	 Start  (void);
	void	 Stop   (void);

private:

	void	GameLoop(void);
	void	OnExit  (void);

private:

	bool	m_isRunning;
	Window	m_window;

	///  \brief  Fixed update (ups = update per second)
	///          16.67 =  60 ups
	///          11.11 =  90 ups
	///           8.33 = 120 ups
	///           4.16 = 240 ups
	///
	const float SECONDS_PER_UPDATE = 1.0f / 120.0f;

};

#endif // _ENGINE_HPP
