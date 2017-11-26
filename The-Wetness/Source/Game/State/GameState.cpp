/// \file       GameState.cpp
/// \date       25/11/2017
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Engine.hpp"
#include "Game/State/GameState.hpp"
#include "Generation/PuzzleGenerator.hpp"

/// \brief	Destructor
/* virtual */ GameState::~GameState(void)
{
	// None
}

/// \brief	Called when the state is pushed
/* virtual */ void GameState::OnEnter(void)
{
	// PuzzleGenerator pg;
	// pg.generateNextPuzzle();
}

/// \brief	Called when the state is removed
/* virtual */ void GameState::OnExit(void)
{
	// None
}

/// \brief	Called each frame
/// \param  dt The elapsed time since the last frame
/* virtual */ void GameState::Update(float dt)
{
	Engine::pRendering->Draw('X', 0x0F, 10, 6);
	Engine::pRendering->Draw(std::string("Game Engine !"), 10, 6);
}