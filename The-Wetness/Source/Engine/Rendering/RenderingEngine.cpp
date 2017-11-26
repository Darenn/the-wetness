/// \file       RenderingEngine.hpp
/// \date       08/10/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Rendering/RenderingEngine.hpp"

/// \brief	Constructor (private)
RenderingEngine::RenderingEngine(void)
{
	// None
}

/// \brief	Copy constructor (private)
/// \param  other The engine to copy
RenderingEngine::RenderingEngine(const RenderingEngine& other)
{
	// None
}


/// \brief	Initializes the rendering engine from parameters
/// \param  title The title of the window
/// \param  size The size of the window
/// \param  fps The frame rate
void RenderingEngine::Initialize(const std::string & title, const Vector2u & size, float fps, bool debug)
{
	// Configuring window
	m_debug = debug;
	m_window.Open(title, size, m_debug);

	m_timer.Start();
	m_frameTime   = 1.0f / fps;

	m_fpsTimer    = 0.0f;
	m_elapsedTime = 0.0f;
	m_frameCount  = 0;
}

/// \brief	Renders the screen buffer on the screen
/// \param  interpolate The current position 
///         of the engine in the frame
void RenderingEngine::Render(float interpolate)
{
	float current = m_timer.GetElaspedTime();
	if(current - m_fpsTimer >= 1.0f)
	{
		m_window.SetFPS(m_frameCount);

		m_frameCount = 0;
		m_fpsTimer = current;
	}

	if(current - m_elapsedTime >= m_frameTime)
	{
		m_elapsedTime = current;
		m_window.Display();
		m_window.Clear();

		m_frameCount++;
	}
}

/// \brief	Releases the rendering engine
void RenderingEngine::Release(void)
{
	m_window.Close();
}