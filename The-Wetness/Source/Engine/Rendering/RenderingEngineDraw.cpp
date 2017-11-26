/// \file       RenderingEngineDraw.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Generation/Grid/Grid.hpp"
#include "Engine/Rendering/RectangleShape.hpp"
#include "Engine/Rendering/RenderingEngine.hpp"

/// \brief	Draws a wchar at the given position
/// \param  value The wchar to draw
/// \param  attribute The attribute of the wchar (color)
/// \param  x The x coordinate
/// \param  y The y coordinate
void RenderingEngine::Draw(WCHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_window.Draw(value, attribute, x, y);
}

/// \brief	Draws a char at the given position
/// \param  value The char to draw
/// \param  attribute The attribute of the char (color)
/// \param  x The x coordinate
/// \param  y The y coordinate
void RenderingEngine::Draw(CHAR  value, WORD attribute, USHORT x, USHORT y)
{
	m_window.Draw(value, attribute, x, y);
}

/// \brief	Draws a char info buffer a the given position
/// \param  pBuffer The char to draw
/// \param  h The height of the buffer
/// \param  w The width of the buffer
/// \param  x The x coordinate
/// \param  y The y coordinate
void RenderingEngine::Draw(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y)
{
	m_window.Draw(pBuffer, h, w, x, y);
}

/// \brief	Draws a string at the given position
/// \param  text The string to draw
/// \param  x The x coordinate
/// \param  y The y coordinate
void RenderingEngine::Draw(std::string const& text, USHORT x, USHORT y)
{
	Draw(text.c_str(), x, y);
}

/// \brief	Draws a string at the given position
/// \param  text The c string to draw
/// \param  x The x coordinate
/// \param  y The y coordinate
void RenderingEngine::Draw(char const * text, USHORT x, USHORT y)
{
	while (*text)
	{
		m_window.Draw(*text, 0x0F, x, y);
		++text; ++x;
	}
}

/// \brief	Draws a rectangle shape at the given position
/// \param  rect The rectangle shape to draw
void RenderingEngine::Draw(RectangleShape const& rect)
{
	for (USHORT h = 0; h < rect.h; ++h)
	{
		for (USHORT w = 0; w < rect.w; ++w)
		{
			m_window.Draw((WCHAR)0x2588, rect.c.attribute, (rect.x / 2) + w, ((rect.y / 2) + h) - 10);
		}
	}
}

/// \brief	Draws the grid at the center of the screen
/// \param  formatedGrid The grid as a string
/// \param  gridSize The size of the grid
void RenderingEngine::Draw(std::string const& formatedGrid, Vector2u const& gridSize)
{
	USHORT blockSize = 15;
	USHORT borderThickness = blockSize * 2;
	USHORT doubleBlockSize = blockSize * 2;
	USHORT playGroundThickness = borderThickness / 2;

	USHORT width  = gridSize.x * 2;
	USHORT height = gridSize.y * 2;
	USHORT puzzleWidth  = width  * blockSize;
	USHORT puzzleHeight = height * blockSize;

	USHORT centerX = m_window.GetWidth()  / 2;
	USHORT centerY = m_window.GetHeight() / 2;
	USHORT startX  = centerX - puzzleWidth;
	USHORT startY  = centerY - puzzleHeight;

	// Draws grey borders
    Draw(RectangleShape(startX - borderThickness, startY - borderThickness,
		puzzleHeight + borderThickness,
		puzzleWidth  + borderThickness,
		Color::Grey));

	// Draws puzzle background
	Draw(RectangleShape(startX - playGroundThickness, startY - playGroundThickness,
		puzzleHeight + playGroundThickness,
		puzzleWidth + playGroundThickness,
		Color::Green));

	// Draws grid
	startX += blockSize;
	startY += blockSize;
	USHORT posX = startX;
	USHORT posY = startY;

	for (char caseType : formatedGrid)
	{
		switch (caseType)
		{
			case '#': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Black));  break;
			case '=': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Black));  break;
			case '|': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Black));  break;
			case 'E': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Purple)); break;
			case 'S': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Red));    break;
			case 'X': Draw(RectangleShape(posX, posY, blockSize, blockSize, Color::Blue));   break;
			default: break;
		}

		posX += doubleBlockSize;

		if(caseType == '\n')
		{
			posX = startX;
			posY += doubleBlockSize;
		}
	}
}

/// \brief	Draws a rectangle on the grid
/// \param  formatedGrid The grid as a string
/// \param  gridSize The size of the grid
/// \param  X The x coordinate of the rectangle
/// \param  Y The y coordinate of the rectangle
void RenderingEngine::Draw(std::string const& formatedGrid, Vector2u const& gridSize, USHORT X, USHORT Y)
{
	// TODO
}