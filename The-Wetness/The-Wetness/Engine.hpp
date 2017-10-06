/// \file       Engine.hpp
/// \date       04/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "Timer.hpp"
#include "MainMenu.hpp"
#include "GridDisplayer.hpp"

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

	MainMenu      m_menu;
	GridDisplayer m_displayer;

	bool	m_isRunning;
	Window	m_window;

	///  \brief  Fixed update
	const float SECONDS_PER_UPDATE = 1.0f / 60.0f;
};

#endif // _ENGINE_HPP
