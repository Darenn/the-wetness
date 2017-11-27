/// \file       SoundEngine.hpp
/// \date       27/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _SOUND_ENGINE_HPP
#define _SOUND_ENGINE_HPP

#include <string>
#include <windows.h>

/// \class	SoundEngine
/// \brief	Manages sound and music
class SoundEngine
{
public:

	void Play(char const* filename, USHORT mode = SND_ASYNC);

private:

	// The engine canno't be constructed
	// The engine canno't be copy-constructed
	explicit SoundEngine(void);
	SoundEngine(const SoundEngine & other);

	// But the game engine has an access to the rendering engine
	friend class Engine;
	friend class GameEngine;

	void Initialize(std::string const& resourceFolder);

private:

	std::string m_resourceFolder;
};

#endif // _SOUND_ENGINE_HPP