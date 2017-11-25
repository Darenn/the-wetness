/// \file       StateMachine.cpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Engine/AI/State/StateMachine.hpp"

/// \brief	Destructor, frees all allocate memory
StateMachine::~StateMachine()
{
	for(Pair & currentPair : m_stateStack)
	{
		delete currentPair.second;
	}
}

/// \brief	Removes the last state
void StateMachine::PopState()
{
	if(m_stateStack.size() > 0)
	{
		delete m_stateStack.back().second;
		m_stateStack.pop_back();
	}
}