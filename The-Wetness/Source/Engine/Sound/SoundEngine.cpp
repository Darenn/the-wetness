/// \file       SoundEngine.cpp
/// \date       27/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Sound/SoundEngine.hpp"
#include "Engine/Utility/StringUtility.hpp"

/// \brief	Constructor
/* explicit */ SoundEngine::SoundEngine(void)
{
	// None
}

/// \brief	Copy constructor
/// \param  other The sound engine to copy
SoundEngine::SoundEngine(const SoundEngine & other)
{
	// None
}

/// \brief	Initializes the sound engine
/// \param  resourceFolder The path to the resource folder
void SoundEngine::Initialize(std::string const& resourceFolder)
{
	m_resourceFolder = resourceFolder;
}

/// \brief	Plays a sound
/// \param  filename The filename ...
/// \param  mode The reading mode : SND_SYNC, SND_ASYNC by default 
void SoundEngine::Play(char const* filename, USHORT mode /* SND_ASYNC */)
{
	std::wstring fullPath = StringToWString(m_resourceFolder) + 
						    StringToWString(std::string(filename));

	PlaySound((LPCWSTR)fullPath.c_str(), nullptr, mode | SND_FILENAME);
}

