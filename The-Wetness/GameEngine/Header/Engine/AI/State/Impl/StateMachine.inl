/// \file       StateMachine.inl
/// \date       25/11/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

/// \brief	Adds at the end of the stack a new state
/// \tparam Tp The type of the state, must derived from IState
/// \param  key The key of the state
template <typename Tp>
void StateMachine::PushState(std::string const& key)
{
	// Compile time assertion to check if the user
	// is trying to deceive the PushState method
	static_assert(std::is_base_of<IState, Tp>::value);
	m_stateStack.push_back(Pair(m_stringHasher(key), new Tp()));
}

/// \brief	Update the last state on the stack
/// \param  dt The elapsed time since the last frame
inline void StateMachine::Update(float dt)
{
	if(m_stateStack.size())
	{
		m_stateStack.back().second->Update(dt);
	}
}