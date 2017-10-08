/// \file       GameEngine.hpp
/// \date       08/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _GAME_ENGINE_HPP
#define _GAME_ENGINE_HPP

#include "Timer.hpp"

/// \class  GameEngine
/// \brief  Handles rendering, FPS etc.
class GameEngine
{
public:

	explicit GameEngine(void);

	void Initialize();
	void Start();

private:

	// TODO
};

#endif // _GAME_ENGINE_HPP
