/// \file       Window.inl
/// \date       09/10/2017
/// \package    Engine/Platform/Window
/// \author     Vincent STEHLY--CALISTO

/// \brief	Tells if the window is open or not
/// \return True or false
inline bool Window::IsOpen(void) const
{
	return m_isOpen;
}

/// \brief	Returns the width of the window
/// \note	Moves the function into a .inl file
/// \return The width of the window
inline unsigned short Window::GetWidth(void) const
{
	return m_windowSize.x;
}

/// \brief	Returns the height of the window
/// \note	Moves the function into a .inl file
/// \return The height of the window
inline unsigned short Window::GetHeight(void) const
{
	return m_windowSize.y;
}