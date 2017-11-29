/// \file       GameEngine.cpp
/// \date       08/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/GameEngine.hpp"
#include "Engine/Utility/StringUtility.hpp"

/// \brief	Constructor
GameEngine::GameEngine(char const* env)
: m_pStateMachine(Engine::pStateMachine)
, m_pSoundEngine(Engine::pSoundEngine)
, m_pRenderingEngine(Engine::pRendering)
, m_pFrameAllocator(Engine::pFrameAllocator)
{
	m_debug   = false;
	m_running = false;
	m_fps     = 90.0f;

	m_granularity  = 60.0f;
	m_windowSize.x = 500;
	m_windowSize.y = 500;
	m_windowTitle  = "The Wetness";
	m_environment  = env;

	m_resourceFolder = GetResourcePath(m_environment);
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
	m_running = false;

	// Rendering configuration
	m_pSoundEngine->Initialize(m_resourceFolder);
	m_pRenderingEngine->Initialize(m_windowTitle, m_windowSize, m_fps, m_debug);
}

/// \brief	Stars the game engine 
///         by entering the game loop
void GameEngine::Start(void)
{
	Timer clock;
	float lag = 0.0f;
	float previous = clock.GetElaspedTime();

	m_running = true;
	while (m_running)
	{
		float current = clock.GetElaspedTime();
		float elapsed = current - previous;
		previous = current;

		lag += elapsed;
		while (lag >= m_granularity)
		{
			// Logic update
			m_pStateMachine->Update(m_granularity);

			// Retrieve elapsed time
			lag -= m_granularity;
			m_pRenderingEngine->Render(lag / m_granularity);

			// Clear the frame allocator for the next frame
			m_pFrameAllocator->Clear();
		}
	}
}