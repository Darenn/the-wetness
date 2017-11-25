/// \file       IState.hpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _ISTATE_HPP
#define _ISTATE_HPP

/// \class  IState
/// \brief  Interface for game states
class IState
{
public:

	virtual void OnEnter()         = 0;
	virtual void OnExit ()         = 0;
	virtual void Update (float dt) = 0;
};

#endif // _ISTATE_HPP
