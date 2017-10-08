/// \file       GameEngine.cpp
/// \date       08/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "GameEngine.hpp"

/// \brief	Constructor
GameEngine::GameEngine(void)
{
	m_debug = false;
	m_fps   = 90.0f;

	m_granularity  = 60.0f;
	m_windowSize.x = 500;
	m_windowSize.y = 500;
	m_windowTitle  = "The Wetness";
}

/// \brief	Tells if the engine is in debug mode or not
/// \param  debug The debug mode (active if true)
void GameEngine::SetInitDebug(bool debug)
{
	m_debug = true;
}

/// \brief	Sets the frame rate
/// \param  fps The fps to set
void GameEngine::SetInitFrameRate(float fps)
{
	assert(fps >= GAME_ENGINE_MIN_FPS);
	assert(fps <= GAME_ENGINE_MAX_FPS);

	// This is the frame rate of the rendering engine
	m_fps = fps;
}

/// \brief	the count of update per seconds
/// \param  
void GameEngine::SetInitUpdateRate(unsigned int ups)
{
	assert(ups >= GAME_ENGINE_MIN_UPS);
	assert(ups <= GAME_ENGINE_MAX_UPS);

	// The UPS represents the update granularity
	// If UPS = 60, the game logic will be updated
	// every 16 ms.
	m_granularity = 1.0f / ups;
}

/// \brief	Sets the window title
/// \param  pTitle the title to set
void GameEngine::SetInitWindowTitle(const char* pTitle)
{
	m_windowTitle = pTitle;
}

/// \brief	Sets the window size
/// \param  size The size of the window
void GameEngine::SetInitWindowSize(const Vector2u& size)
{
	m_windowSize = size;
}

/// \brief	Initializes the game engine
void GameEngine::Initialize(void)
{
	// TODO
}

/// \brief	Stars the game engine 
///         by entering the game loop
void GameEngine::Start(void)
{
	/// TODO
}