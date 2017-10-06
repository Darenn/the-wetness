/// \file       Window.cpp
/// \date       03/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#include "Window.hpp"

/// \brief Default constructor
Window::Window(void)
{
	// None
}

/// \brief Ensures to deallocate all memory
Window::~Window(void)
{
	Close();
}

/// \brief	Initializes the console with a title and with the given dimensions
/// \param  pWTitle  A c-string to set the title
/// \param  WWidth  The console width
/// \param  WHeight The console height
void Window::Open(const char * pTitle, USHORT WWidth, USHORT WHeight)
{
	m_width           = WWidth;
	m_height          = WHeight;
	m_bufferHeight    = 70;
	m_bufferWidth     = 70;
	m_isOpen          = false;
	m_pConsole        = nullptr;
	m_pSTDOutput      = nullptr;
	m_currentFrame    = 0;
	m_frameCounter    = 0;
	m_fpsCounter      = 0;
	m_lastTime        = 0.0f;
	m_drawCallCounter = 0;

	// Gets descriptors
	m_pConsole   = GetConsoleWindow();
	m_pSTDOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	assert(nullptr != m_pConsole);
	assert(nullptr != m_pSTDOutput);
	assert(INVALID_HANDLE_VALUE != m_pSTDOutput);

	// Initializes
	SetTitle(pTitle);
	SetWindowSize(m_height, m_width);

	// FPS Timer
	m_timer.Start();

	// Buffering screen rect
	m_dwBufferCoord = { 0, 0 };
	m_dwBufferSize  = {       static_cast<SHORT>(m_bufferWidth),     static_cast<SHORT>(m_bufferHeight)     };
	m_recRegion     = { 0, 0, static_cast<SHORT>(m_bufferWidth) - 1, static_cast<SHORT>(m_bufferHeight) - 1 };

	InitializeFrameBuffers();

	// The window is now open
	m_isOpen = true;
}

/// \brief	Close the window, releases all frame buffers
void Window::Close(void)
{
	m_isOpen = false;
}

/// \brief	Initializes all frame buffers
void Window::InitializeFrameBuffers(void)
{
	// TODO
	Clear();
}

/// \brief	Clear the current buffer
void Window::Clear(void)
{
	for (int i = 0; i < m_bufferHeight; ++i)
	{
		for (int j = 0; j < m_bufferWidth; ++j)
		{
			m_pFrameBuffer[i][j].Char.UnicodeChar = 0x0020;
			m_pFrameBuffer[i][j].Char.AsciiChar   = ' ';
			m_pFrameBuffer[i][j].Attributes       = 0x0;
		}
	}
}

/// \brief	Draws a char at the given position
/// \param  value The char to draw
/// \param  attribute The value of the char to draw
/// \param  x The x coordinate
/// \param  y The y coordinate
void Window::Draw(CHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_pFrameBuffer[y][x].Char.AsciiChar = value;
	m_pFrameBuffer[y][x].Attributes     = attribute;

	m_drawCallCounter++;
}

/// \brief	Draws a wchar at the given position
/// \param  value The char to draw
/// \param  attribute The value of the char to draw
/// \param  x The x coordinate
/// \param  y The y coordinate
void Window::Draw(WCHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_pFrameBuffer[y][x].Char.UnicodeChar = value;
	m_pFrameBuffer[y][x].Attributes       = attribute;

	m_drawCallCounter++;
}

/// \brief	Draws the given buffer at the given positions
/// \param  w The width of the buffer
/// \param  h The height of the buffer
/// \param  x The left position
/// \param  y The top position
void Window::Draw(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y)
{
	for (int nRow = 0; nRow < h; ++nRow)
	{
		CHAR_INFO * nBuffer = pBuffer + nRow * w;
		for (int nCol = 0; nCol < w; ++nCol)
		{
			if (y + nRow < m_bufferHeight && x + nCol < m_bufferHeight)
			{
				m_pFrameBuffer[y + nRow][x + nCol] = nBuffer[nCol];
			}
		}
	}

	m_drawCallCounter++;
}

/// \brief Displays the current buffer by swapping buffers
void Window::Display(void)
{
	// Sends the current buffer to the windows console's buffer
	WriteConsoleOutput(m_pSTDOutput, (CHAR_INFO *)m_pFrameBuffer,
		m_dwBufferSize,
		m_dwBufferCoord, 
		&m_recRegion);

	m_frameCounter++;
	m_fpsCounter++;

	float currentTime = m_timer.GetElaspedTime();
	if (currentTime - m_lastTime >= 1.0f)
	{
		m_currentFrame = m_fpsCounter;
		m_fpsCounter = 0;
		m_lastTime   = currentTime;	
	}

	DrawFPS();
}

/// \brief	Sets the console title
/// \param  pTitle a pointer on the new title
void Window::SetTitle(const char * pTitle)
{
	assert(64 > strlen(pTitle));
	assert(nullptr != m_pConsole);

	wchar_t wTitle[64];
	swprintf(wTitle, 64, L"%hs", pTitle);

	SetConsoleTitle(wTitle);
}

/// \brief	Sets the window size
/// \param  H The height of the window
/// \param  W The width of the window
void Window::SetWindowSize(USHORT H, USHORT W)
{
	RECT currentRect;
	GetWindowRect(m_pConsole, &currentRect);

	// Resize the window to fit the given dimensions
	MoveWindow(m_pConsole, currentRect.left, currentRect.top, m_width, m_height, TRUE);
}

void Window::DrawFPS(void)
{
	std::string frames   = "Frames    : " + std::to_string(m_frameCounter);
	std::string fps      = "FPS       : " + std::to_string(m_currentFrame);
	std::string drawCall = "Draw call : " + std::to_string(m_drawCallCounter);

	for (int nChar = 0; nChar < fps.size(); ++nChar)
	{
		m_pFrameBuffer[0][0 + nChar].Char.AsciiChar = fps[nChar];
		m_pFrameBuffer[0][0 + nChar].Attributes     = 0x0E;
	}

	for (int nChar = 0; nChar < frames.size(); ++nChar)
	{
		m_pFrameBuffer[1][0 + nChar].Char.AsciiChar = frames[nChar];
		m_pFrameBuffer[1][0 + nChar].Attributes     = 0x0F;
	}

	for (int nChar = 0; nChar < drawCall.size(); ++nChar)
	{
		m_pFrameBuffer[2][0 + nChar].Char.AsciiChar = drawCall[nChar];
		m_pFrameBuffer[2][0 + nChar].Attributes = 0x0F;
	}
}
