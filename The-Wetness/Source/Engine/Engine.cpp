/// \file       Engine.cpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Engine.hpp"

/* static */ RenderingEngine * const Engine::pRendering    = new RenderingEngine();
/* static */ StateMachine    * const Engine::pStateMachine = new StateMachine();
/* static */ SoundEngine     * const Engine::pSoundEngine  = new SoundEngine();