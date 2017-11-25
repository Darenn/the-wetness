/// \file       StateMachine.hpp
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _STATE_MACHINE_HPP
#define _STATE_MACHINE_HPP

#include <string>
#include <vector>

#include "IState.hpp"

/// \class  StateMachine
/// \brief  State manager
class StateMachine
{
public:

	// User interface
	template <typename Tp>
	void PushState(std::string const& key);
	void PopState ();

private:

	friend class GameEngine;

	// The update method must only be accessed by the game engine
	inline void Update(float dt);

	StateMachine()                           = default;
	StateMachine (StateMachine const& other) = default;
	~StateMachine();

private:

	using Pair = std::pair<size_t, IState *>;

	std::vector<Pair>      m_stateStack;
	std::hash<std::string> m_stringHasher;
};

#include "Impl/StateMachine.inl"

#endif // _STATE_MACHINE_HPP