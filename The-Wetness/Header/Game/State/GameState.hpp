/// \file       GameState.hpp
/// \date       25/11/2017
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#ifndef _GAME_STATE_HPP
#define _GAME_STATE_HPP

#include "Engine/AI/State/IState.hpp"

/// \class	GameState
/// \brief	Implements the game state
class GameState : public IState
{
public:

	virtual ~GameState();

	virtual void OnEnter(void)     override final;
	virtual void OnExit (void)     override final;
	virtual void Update (float dt) override final;
};

#endif // _GAME_STATE_HPP