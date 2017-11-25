/// \file       Engine.hpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ENGINE_HPP
#define _ENGINE_HPP

#include "AI\State\StateMachine.hpp"
#include "Rendering\RenderingEngine.hpp"

/// \brief	TODO
struct Engine
{
	static RenderingEngine * const pRendering;
	static StateMachine    * const pStateMachine;
};

#endif // _ENGINE_HPP
