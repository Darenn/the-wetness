/// \file       RenderingEngineDraw.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Generation/Grid/Grid.hpp"
#include "Engine/Rendering/RectangleShape.hpp"
#include "Engine/Rendering/RenderingEngine.hpp"

void RenderingEngine::Draw(WCHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_window.Draw(value, attribute, x, y);
}

void RenderingEngine::Draw(CHAR  value, WORD attribute, USHORT x, USHORT y)
{
	m_window.Draw(value, attribute, x, y);
}

void RenderingEngine::Draw(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y)
{
	m_window.Draw(pBuffer, h, w, x, y);
}

// Other draw methods
void RenderingEngine::Draw(std::string const& text, USHORT x, USHORT y)
{
	Draw(text.c_str(), x, y);
}

void RenderingEngine::Draw(char const * text, USHORT x, USHORT y)
{
	while (*text)
	{
		m_window.Draw(*text, 0x0F, x, y);
		++x;
		++text;
	}
}

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

void RenderingEngine::Draw(Grid const& grid)
{
	USHORT offsetX = 0;
	USHORT offsetY = 0;
	
	USHORT blockSize = 15;
	USHORT borderThickness = blockSize * 2;
	USHORT doubleBlockSize = blockSize * 2;
	USHORT playGroundThickness = borderThickness / 2;

	USHORT width  = grid.getWidth()  * 2;
	USHORT height = grid.getHeight() * 2;
	USHORT puzzleWidth  = width * blockSize;
	USHORT puzzleHeight = height * blockSize;

	USHORT centerX = m_window.GetWidth()  / 2;
	USHORT centerY = m_window.GetHeight() / 2;

	USHORT startX = centerX - puzzleWidth;
	USHORT startY = centerY - puzzleHeight;

	// Draws grey borders
    Draw(RectangleShape(
		startX - borderThickness,
		startY - borderThickness,
		puzzleHeight + borderThickness,
		puzzleWidth  + borderThickness,
		Color(Color::EColor::GREY)));

	// Draws puzzle background
	Draw(RectangleShape(
		startX - playGroundThickness,
		startY - playGroundThickness,
		puzzleHeight + playGroundThickness,
		puzzleWidth + playGroundThickness,
		Color(Color::EColor::GREEN)));

	// Draws path
	startX += blockSize;
	startY += blockSize;
	USHORT posX = startX;
	USHORT posY = startY;

	std::string formatedGrid = "";
	for (size_t i = 0; i < grid.getWidth(); i++)
	{
		for (size_t j = 0; j < grid.getHeight(); j++)
		{
			Grid::Coordinates node{ j, i };
			formatedGrid += static_cast<char>(grid.getData(node));
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::EAST))
			{
				formatedGrid += '=';
			}	
			else
			{
				formatedGrid += ' ';
			}
		}
		formatedGrid += '\n';
		for (size_t j = 0; j < grid.getHeight(); j++)
		{
			Grid::Coordinates node{ j, i };
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::SOUTH))
			{
				formatedGrid += "| ";
			}
			else
			{
				formatedGrid += ' ';
			}
		}
		formatedGrid += '\n';
	}

	for (char caseType : formatedGrid)
	{
		switch (caseType)
		{
		case '#':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::BLACK)));
			posX += doubleBlockSize;
			break;

		case '=':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::BLACK)));
			posX += doubleBlockSize;
			break;

		case '|':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::BLACK)));
			posX += doubleBlockSize;
			break;

		case 'E':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::PURPLE)));
			posX += doubleBlockSize;
			break;

		case 'S':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::RED)));
			posX += doubleBlockSize;
			break;

		case '\n':
			posX = startX;
			posY += doubleBlockSize;
			break;

		case 'X':
			Draw(RectangleShape(posX, posY, blockSize, blockSize, Color(Color::EColor::BLUE)));
			posX += doubleBlockSize;
			break;

		case ' ':
			posX += doubleBlockSize;
			break;

		default:
			break;
		}
	}
}