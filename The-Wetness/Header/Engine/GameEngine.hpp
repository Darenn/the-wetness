/// \file       GameEngine.hpp
/// \date       08/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _GAME_ENGINE_HPP
#define _GAME_ENGINE_HPP

#include "Engine.hpp"

#define GAME_ENGINE_MIN_FPS 30
#define GAME_ENGINE_MAX_FPS 240
#define GAME_ENGINE_MIN_UPS 60
#define GAME_ENGINE_MAX_UPS 240

/// \class  GameEngine
/// \brief  Handles rendering, FPS etc.
class GameEngine
{
public:

	explicit GameEngine(char const* env);

	void SetInitDebug       (bool debug);
	void SetInitFrameRate	(float fps);
	void SetInitUpdateRate  (unsigned int ups);
	void SetInitWindowTitle	(const char * pTitle);
	void SetInitWindowSize	(const Vector2u & size);

	void Initialize	(void);
	void Start		(void);

private:

	bool			m_debug;
	bool			m_running;
	float			m_fps;
	float			m_granularity;
	Vector2u		m_windowSize;
	std::string		m_windowTitle;
	std::string     m_environment;
	std::string     m_resourceFolder;

	StateMachine    * const m_pStateMachine;
	SoundEngine     * const m_pSoundEngine;
	RenderingEngine * const m_pRenderingEngine;
	FrameAllocator  * const m_pFrameAllocator;
};

#endif // _GAME_ENGINE_HPP
