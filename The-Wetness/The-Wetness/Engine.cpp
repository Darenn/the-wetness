/// \file       Engine.cpp
/// \date       04/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine.hpp"

/// \brief	Default constructor
Engine::Engine(void)
{
	// None
}

/// \brief	Default destructor
Engine::~Engine(void)
{
	// None
}

/// \brief	Starts the engine
void Engine::Start(void)
{
	m_window.Open("A", 200, 200);
	GameLoop();
}

/// \brief	Stops the engine
void Engine::Stop(void)
{
	m_isRunning = false;
}

/// \brief	Main method of the game
void Engine::GameLoop(void)
{
	Timer clock;
	float lag = 0.0f;
	float previous = clock.GetElaspedTime();

	m_isRunning = true;
	while (m_isRunning)
	{
		float current = clock.GetElaspedTime();
		float elapsed = current - previous;
		previous = current;

		lag += elapsed;
		while (lag >= SECONDS_PER_UPDATE)
		{
			// Retrieve elapsed time
			lag -= SECONDS_PER_UPDATE;
		}

		// Rendering
		m_window.Display();
	}
}

/// \brief	Called when the game is exiting
void Engine::OnExit(void)
{
	m_window.Close();
}
