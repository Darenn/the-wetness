/// \file       Engine.hpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "Sound/SoundEngine.hpp"
#include "Memory/StackAllocator.hpp"
#include "AI/State/StateMachine.hpp"
#include "Rendering/RenderingEngine.hpp"

/// \brief	TODO
struct Engine
{
	static RenderingEngine * const pRendering;
	static StateMachine    * const pStateMachine;
	static SoundEngine     * const pSoundEngine;
	static FrameAllocator  * const pFrameAllocator;
};

#endif // _ENGINE_HPP
