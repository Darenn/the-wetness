/// \file       GridDisplayer.cpp
/// \date       05/10/2017
/// \package    Test
/// \author     Vincent STEHLY--CALISTO

#include "GridDisplayer.hpp"

#include <vector>
#include "GridDecoder.hpp"
#include "GridEncoder.hpp"
#include "PuzzleGenerator.hpp"

using namespace std;

GridDisplayer::GridDisplayer() : grid(0, 0)
{
	PuzzleGenerator pg;
	grid = pg.generateNextPuzzle();
}

void GridDisplayer::Update(float dt)
{
	// None
}

void GridDisplayer::Render(Window & window)
{
	/*std::ostringstream stream;
	stream << grid;
	std::string strGrid = stream.str();
	//std::cout << strGrid << std::endl;

	USHORT posX = 15;
	USHORT posY = 10;

	USHORT currentX = 0;
	USHORT currentY = 0;

	for (int nChar = 0; nChar < strGrid.size(); ++nChar)
	{
		char caseType = strGrid[nChar];
		switch(caseType)
		{
			case '#':
				window.Draw((WCHAR)0x25A0, 0x0E, posX + currentX, posY + currentY);
				currentX++;
				break;

			case '=':
				window.Draw((CHAR)'=', 0x0E, posX + currentX, posY + currentY);
				currentX++;
				break;

			case '|':
				window.Draw((CHAR)'|', 0x0E, posX + currentX, posY + currentY);
				currentX++;
				break;

			case 'E':
				window.Draw((CHAR)'E', 0x0B, posX + currentX, posY + currentY);
				currentX++;
				break;

			case 'S':
				window.Draw((CHAR)'S', 0x0B, posX + currentX, posY + currentY);
				currentX++;
				break;
	
			case '\n':
				currentY++;
				currentX = 0;
				break;
	
			default:
				window.Draw((WCHAR)0x0020, 0x0, posX + currentX, posY + currentY);
				currentX++;
				break;
		}
	}*/
}