/// \file       RenderingEngineDraw.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

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
/// \param  gridSize The size of the grid
/// \param  size The size of the blocks
/// \param  formatedGrid The grid as a string
void RenderingEngine::Draw(Vector2u const& gridSize, USHORT const size, std::string const& formatedGrid)
{
	USHORT borderThickness = size * 2;
	USHORT doubleBlockSize = size * 2;
	USHORT playGroundThickness = borderThickness / 2;

	USHORT puzzleWidth  = gridSize.x * size;
	USHORT puzzleHeight = gridSize.y * size;

	USHORT startX = m_window.GetWidth() / 2 - puzzleWidth;
	USHORT startY = m_window.GetHeight() / 2 - puzzleHeight;

	// Draws grey borders
	Draw(RectangleShape(startX - borderThickness, startY - borderThickness,
		puzzleHeight + borderThickness,
		puzzleWidth + borderThickness,
		Color::Grey));

	// Draws puzzle background
	Draw(RectangleShape(startX - playGroundThickness, startY - playGroundThickness,
		puzzleHeight + playGroundThickness,
		puzzleWidth + playGroundThickness,
		Color::Blue));

	// Draws grid
	startX += size;
	startY += size;
	USHORT posX = startX;
	USHORT posY = startY;

	for (char caseType : formatedGrid)
	{
		switch (caseType)
		{
		case '#': Draw(RectangleShape(posX, posY, size, size, Color::Black));  break;
		case '=': Draw(RectangleShape(posX, posY, size, size, Color::Black));  break;
		case '|': Draw(RectangleShape(posX, posY, size, size, Color::Black));  break;
		case 'S': Draw(RectangleShape(posX, posY, size, size, Color::Black));  break;
		case 'E': Draw(RectangleShape(posX, posY, size, size, Color::Green));  break;
		case 'X': Draw(RectangleShape(posX, posY, size, size, Color::Yellow)); break;
		default: break;
		}

		posX += doubleBlockSize;

		if (caseType == '\n')
		{
			posX = startX;
			posY += doubleBlockSize;
		}
	}
}

/// \brief	Draws a rectangle on the grid
/// \param  gridSize The size of the grid
/// \param  size The size of the blocks
/// \param  X The x coordinate of the rectangle
/// \param  Y The y coordinate of the rectangle
void RenderingEngine::Draw(Vector2u const& gridSize, USHORT const size, USHORT X, USHORT Y)
{
	USHORT doubleBlockSize = size * 2;

	USHORT startX = m_window.GetWidth() / 2  - gridSize.x * size + size;
	USHORT startY = m_window.GetHeight() / 2 - gridSize.y * size + size;

	Draw(RectangleShape(startX + X * doubleBlockSize, startY + Y * doubleBlockSize, size, size, Color::White));
}

/// \brief	Draws a rectangle on the grid
/// \param  gridSize The size of the grid
/// \param  size The size of the blocks
/// \param  path The path to draw
/// \param  color The color of the path
void RenderingEngine::Draw(Vector2u const& gridSize, USHORT const size, std::vector<Vector2u> const& path, Color const& color)
{
	if (path.size() == 0)
	{
		return;
	}

	USHORT doubleBlockSize = size * 2;

	USHORT startX = m_window.GetWidth()  / 2 - gridSize.x * size + size;
	USHORT startY = m_window.GetHeight() / 2 - gridSize.y * size + size;

	Vector2u previous = path.front();
	for(Vector2u const& current : path)
	{
		Draw(RectangleShape(startX + current.x * doubleBlockSize, 
							startY + current.y * doubleBlockSize, size, size, color));

		if (previous != current)
		{
			if (previous.y < current.y)
			{
				Draw(RectangleShape(startX +  current.x      * doubleBlockSize,
									startY + (current.y - 1) * doubleBlockSize, size, size, color));
			}
			else if (previous.y > current.y)
			{
				Draw(RectangleShape(startX +  current.x      * doubleBlockSize,
									startY + (current.y + 1) * doubleBlockSize, size, size, color));
			}
			else if (previous.x < current.x)
			{
				Draw(RectangleShape(startX + (current.x - 1) * doubleBlockSize,
									startY +  current.y      * doubleBlockSize, size, size, color));
			}
			else
			{
				Draw(RectangleShape(startX + (current.x + 1) * doubleBlockSize,
									startY +  current.y      * doubleBlockSize, size, size, color));
			}
		}

		previous = current;
	}
}