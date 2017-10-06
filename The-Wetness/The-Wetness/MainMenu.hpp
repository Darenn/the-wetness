/// \file       MainMenu.hpp
/// \date       05/10/2017
/// \package    GUI
/// \author     Vincent STEHLY--CALISTO

#ifndef _MAIN_MENU_HPP
#define _MAIN_MENU_HPP

#include "Window.hpp"

/// \class  MainMenu
/// \brief  Display the main menu
class MainMenu
{
public:

	explicit MainMenu(void);
	        ~MainMenu(void);

	void	 Update   (float dt);
	void	 Render   (Window & window);

private:

	void	SetCursorPosition(USHORT Y, USHORT X);

private:

	char      m_selectIndex;
	USHORT    m_menuPositionX;
	USHORT    m_menuPositionY;
	CHAR_INFO m_menuBuffer[7][12];
};

#endif // _MAIN_MENU_HPP
