/// \file       RenderingEngine.hpp
/// \date       08/10/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef _RENDERING_ENGINE_HPP
#define _RENDERING_ENGINE_HPP

#include <string>

#include "Engine/Platform/Time/Timer.hpp"
#include "Engine/Platform/Window/Window.hpp"

#include "RectangleShape.hpp"
#include <vector>

/// \class  RenderingEngine
/// \brief  Handles rendering, FPS etc.
class RenderingEngine
{
public:

	// Primitive draw methods
	void Draw(WCHAR value, WORD attribute, USHORT x, USHORT y);
	void Draw(CHAR  value, WORD attribute, USHORT x, USHORT y);
	void Draw(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y);

	// Other draw methods
	void Draw(RectangleShape const& rect);
	void Draw(std::string const& text, USHORT x, USHORT y);
	void Draw(char        const* text, USHORT x, USHORT y);
	
	// Grid draw methods
	void Draw(Vector2u const& gridSize, USHORT const size, USHORT x, USHORT y);
	void Draw(Vector2u const& gridSize, USHORT const size, std::string const& formatedGrid);
	void Draw(Vector2u const& gridSize, USHORT const size, std::vector<Vector2u> const& path, Color const& color);
	
private:

	// The engine canno't be constructed
	// The engine canno't be copy-constructed
	explicit RenderingEngine(void);
			 RenderingEngine(const RenderingEngine & other);
	
	// But the game engine has an access to the rendering engine
	friend class Engine;
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
