/// \file       RenderingEngine.hpp
/// \date       08/10/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef _RENDERING_ENGINE_HPP
#define _RENDERING_ENGINE_HPP

#include <string>

#include "Timer.hpp"
#include "Window.hpp"
#include "Vector2.hpp"

/// \class  RenderingEngine
/// \brief  Handles rendering, FPS etc.
class RenderingEngine
{
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

	Window m_window;
	bool   m_debug;
};

#endif // _RENDERING_ENGINE_HPP
