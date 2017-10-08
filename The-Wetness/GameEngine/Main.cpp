// Tests

#include <cmath>
#include <iostream>
#include <Windows.h>

#include "Timer.hpp"

// #include "Camera.hpp"
// #include "Vector2.hpp"
// #include "Vector3.hpp"

#define mapWidth 24
#define mapHeight 24
#define bufferWidth 500
#define bufferHeight 500


int worldMap[mapWidth][mapHeight] =
{
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1 },
	{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1 },
	{ 1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

CHAR_INFO buffer[bufferHeight][bufferWidth];

void Display(HANDLE pOutput, COORD size, COORD coord, SMALL_RECT rec)
{
	WriteConsoleOutput(pOutput, reinterpret_cast<CHAR_INFO *>(buffer), size,
		coord, &rec);
}

void Clear()
{
	for (int i = 0; i < bufferHeight; ++i)
	{
		for (int j = 0; j < bufferWidth; ++j)
		{
			buffer[i][j].Char.UnicodeChar = 0x0020;
			buffer[i][j].Char.AsciiChar   = ' ';
			buffer[i][j].Attributes       = 0x0;
		}
	}
}

void DrawLine(int x, int start, int end, WORD color)
{
	for(int i = start; i < end; ++i)
	{
		buffer[i][x].Char.AsciiChar = ' ';
		//buffer[i][x].Char.UnicodeChar = 0x2B1B;
		buffer[i][x].Attributes = color;
	}
}

void SetConsoleFontSize(WORD fontSize)
{
	HWND pConsole = GetConsoleWindow();
	HANDLE pHandle = GetStdHandle(STD_OUTPUT_HANDLE | GENERIC_READ | GENERIC_WRITE);

	
	CONSOLE_FONT_INFOEX font;
	GetCurrentConsoleFontEx(pHandle, false, &font);//PCONSOLE_FONT_INFOEX is the same as CONSOLE_FONT_INFOEX*
	DWORD err = GetLastError();


	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize           = sizeof(cfi);
	cfi.nFont            = 0;
	cfi.dwFontSize.X     = fontSize;                   // Width of each character in the font
	cfi.dwFontSize.Y     = fontSize;                  // Height
	cfi.FontFamily       = FF_DONTCARE;
	cfi.FontWeight       = FW_BOLD;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font

	font.dwFontSize.X = 1;
	font.dwFontSize.Y = 1;
	bool test = SetCurrentConsoleFontEx(pHandle, FALSE, &cfi);
	int a = 0;
	a++;
}

// Entry point
int main()
{
	double posX   = 22, posY   = 12;   // x and y start position
	double dirX   = -1, dirY   = 0;    // initial direction vector
	double planeX = 0,  planeY = 0.66; // the 2d raycaster version of camera plane

	double time    = 0; // time of current frame
	double oldTime = 0; // time of previous frame

	Timer timer;
	timer.Start();

	// Creation of the window here --
	HANDLE hOutput = static_cast<HANDLE>(GetStdHandle(STD_OUTPUT_HANDLE));

	COORD dwBufferSize  = { bufferWidth, bufferHeight };
	COORD dwBufferCoord = { 0, 0 };
	SMALL_RECT rcRegion = { 0, 0, bufferWidth - 1, bufferHeight - 1 };
	setlocale(LC_ALL, "");
	Clear();
	SetConsoleFontSize(3);

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//// you can loop k higher to see more color choices
	//for (int k = 1; k < 255; k++)
	//{
	//	// pick the colorattribute k you want
	//	SetConsoleTextAttribute(hConsole, k);
	//	std::cout << k << " I want to be nice today!" << std::endl;
	//}


	bool isRunning = true;
	while (isRunning)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			// Calculate ray position and direction
			double cameraX = 2 * x / double(mapWidth) - 1; // x - coordinate in camera space
			double rayPosX = posX;
			double rayPosY = posY;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			// Which box of the map we're in
			int mapX = int(rayPosX);
			int mapY = int(rayPosY);

			// Length of ray from current position to next x or y - side
			double sideDistX = 0;
			double sideDistY = 0;

			// Length of ray from one x or y - side to next x or y - side
			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			// what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; // Was there a wall hit?
			int side;    // Was a NS or a EW wall hit?
					     
			// Calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (rayPosX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (rayPosY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(mapHeight / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + mapHeight / 2;
			if (drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + mapHeight / 2;
			if (drawEnd >= mapHeight)drawEnd = mapHeight - 1;

			//choose wall color
			WORD color;
			switch (worldMap[mapX][mapY])
			{
				case 1:  color = 204;  break;
				case 2:  color = 238;  break; 
				case 3:  color = 17;  break; 
				case 4:  color = 34;  break; 
				default: color = 51;  break; 
			}

			//give x and y sides different brightness
			if (side == 1) { color = color / 2; }

			// Draw the pixels of the stripe as a vertical line
			DrawLine(x, drawStart, drawEnd, color);
		}

		// Timing for input and FPS counter
		oldTime = time;
		time = timer.GetElaspedTime();

		double frameTime = (time - oldTime);
		//std::cout << 1.0 / frameTime << std::endl;
		Display(hOutput, dwBufferSize, dwBufferCoord, rcRegion);
		Clear();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

		// Move forward if no wall in front of you
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
			{
				posX += dirX * moveSpeed;
			}
			if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
			{
				posY += dirY * moveSpeed;
			}
		}
		//move backwards if no wall behind you
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
			if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}
		//rotate to the right
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
			dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
			planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		//rotate to the left
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = dirX;
			dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
			dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
			double oldPlaneX = planeX;
			planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
			planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}

		Sleep(8);
	}

    return 0;
}