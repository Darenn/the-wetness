/// \file       MainMenu.cpp
/// \date       05/10/2017
/// \package    GUI
/// \author     Vincent STEHLY--CALISTO

#include "MainMenu.hpp"

#define SQ 0x25A0 ///< Square
#define FB 0x0001 ///< Blue
#define GR 0x0E   ///< Green
#define SP 0x0020 ///< Space
#define NL 0x0000 ///< Null
#define TR 0x003E ///< Triangle

/// \brief Constructor
MainMenu::MainMenu(void)
{
	/*
	 * * * * * * * * * * * *
	 *                     *
	 *      > PLAY         * ///< 0x0050 0x004C 0x0041 0x0059
	 *        EXIT         * ///< 0x0045 0x0058 0x0049 0x0054
	 *                     *
	 * * * * * * * * * * * *
	 */
	CHAR_INFO buffer[7][12] =
	{
		{{SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB},     {SQ, FB},     {SQ, FB},     {SQ, FB},     {SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB}},
		{{SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}},
		{{SP, NL}, {SP, NL}, {SP, NL}, {TR, GR}, {0x0050, GR}, {0x004C, GR}, {0x0041, GR}, {0x0059, GR}, {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}},
		{{SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}},
		{{SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}, {0x0045, GR}, {0x0058, GR}, {0x0049, GR}, {0x0054, GR}, {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}},
		{{SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL},     {SP, NL}, {SP, NL}, {SP, NL}, {SP, NL}},
		{{SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB},     {SQ, FB},     {SQ, FB},     {SQ, FB},     {SQ, FB}, {SQ, FB}, {SQ, FB}, {SQ, FB}}
	};

	// Copies all rows into the class member buffer
	for (int nRow = 0; nRow < 12; ++nRow)
	{
		memcpy(m_menuBuffer[nRow], buffer[nRow], sizeof(CHAR_INFO) * 12);
	}

	m_selectIndex   = 0;
	m_menuPositionX = 24;
	m_menuPositionY = 15;
}

/// \brief	Destructor
MainMenu::~MainMenu(void)
{
	// TODO
}

/// \brief	Updates the menu
/// \param  dt The elapsed time since the last frame
void MainMenu::Update(float dt)
{
	SHORT arrowUpState   = GetAsyncKeyState(VK_UP);
	SHORT arrowDownState = GetAsyncKeyState(VK_DOWN);
	SHORT enterState     = GetAsyncKeyState(VK_RETURN);

	if (arrowUpState & 0x8000 && m_selectIndex != 0)
	{
		m_selectIndex = 0;
		SetCursorPosition(2, 3);
	}
	else if (arrowDownState & 0x8000 && m_selectIndex != 1)
	{
		m_selectIndex = 1;
		SetCursorPosition(4, 3);
	}
	else if (enterState & 0x8000)
	{
		// TODO
	}
}

/// \brief	Renders the menu
/// \param  window The window where to draw
void MainMenu::Render(Window & window)
{
	window.Draw((CHAR_INFO *)m_menuBuffer, 7, 12, 
		m_menuPositionX, 
		m_menuPositionY);
}

/// \brief	Sets the cursor position
/// \param  Y The Y coordinate
/// \param  X The X coordinate
void MainMenu::SetCursorPosition(USHORT Y, USHORT X)
{
	m_menuBuffer[Y][X].Char.UnicodeChar = TR;
	m_menuBuffer[Y][X].Attributes       = GR;

	if (Y == 2)
	{
		m_menuBuffer[4][X].Char.UnicodeChar = SP;
		m_menuBuffer[4][X].Attributes       = NL;
	}
	else if (Y == 4)
	{
		m_menuBuffer[2][X].Char.UnicodeChar = SP;
		m_menuBuffer[2][X].Attributes       = NL;
	}
}
