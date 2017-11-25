/// \file       RenderingEngine.hpp
/// \date       08/10/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef _RENDERING_ENGINE_HPP
#define _RENDERING_ENGINE_HPP

#include <string>

#include "Engine/Platform/Time/Timer.hpp"
#include "Engine/Platform/Window/Window.hpp"

/// \class  RenderingEngine
/// \brief  Handles rendering, FPS etc.
class RenderingEngine
{
public:


private:

	// The engine canno't be constructed
	// The engine canno't be copy-constructed
	explicit RenderingEngine(void);
			 RenderingEngine(const RenderingEngine & other);
	
	// But the game engine has an access to the rendering engine
	friend class GameEngine;

	void Initialize(const std::string & title, const Vector2u & size, float fps, bool debug);
	void Render    (float interpolate);
	void Release   (void);

private:

	Window   m_window;
	bool     m_debug;

	Timer    m_timer;
	float    m_fpsTimer;
	float    m_frameTime;
	float    m_elapsedTime;
	unsigned m_frameCount;
};

#endif // _RENDERING_ENGINE_HPP
