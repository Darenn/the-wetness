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
/// \param  pWWidth  The console width
/// \param  pWHeight The onsole height
void Window::Open(const char * pWTitle, unsigned short WWidth, unsigned short WHeight)
{
	m_width          = WWidth;
	m_height         = WHeight;
	m_isOpen         = false;
	m_pConsole       = nullptr;
	m_pSTDOutput     = nullptr;

	// Gets descriptors
	//m_pConsole   = GetConsoleWindow();
	m_pSTDOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	//assert(nullptr != m_pConsole);
	assert(nullptr != m_pSTDOutput);
	assert(INVALID_HANDLE_VALUE != m_pSTDOutput);

	// Buffering screen rect
	m_dwBufferCoord = { 0, 0 };
	m_dwBufferSize  = {       static_cast<SHORT>(m_width),     static_cast<SHORT>(m_height)     };
	m_recRegion     = { 0, 0, static_cast<SHORT>(m_width) - 1, static_cast<SHORT>(m_height) - 1 };

	//SetConsoleTitle((LPCWSTR)pWTitle);

	//RECT currentRect;
	//GetWindowRect(m_pConsole, &currentRect);

	// Resize the window to fit the given dimensions
	//MoveWindow(m_pConsole, currentRect.left, currentRect.top, m_width, m_height, TRUE);

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
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			m_pFrameBuffer[i][j].Char.AsciiChar = ' ';
			m_pFrameBuffer[i][j].Attributes     = 0x0;
		}
	}
}

void Window::Draw(CHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_pFrameBuffer[y][x].Char.AsciiChar = value;
	m_pFrameBuffer[y][x].Attributes     = attribute;
}

/// \brief	Draws the given buffer at the given positions
/// \param  w The width of the buffer
/// \param  h The height of the buffer
/// \param  x The left position
/// \param  y The top position
void Window::Draw(CHAR_INFO * pBuffer, USHORT w, USHORT h, USHORT x, USHORT y)
{
	// TODO
}

/// \brief Displays the current buffer by swapping buffers
void Window::Display(void)
{
	// Sends the current buffer to the windows console's buffer
	WriteConsoleOutput(m_pSTDOutput, (CHAR_INFO *)m_pFrameBuffer,
		m_dwBufferSize,
		m_dwBufferCoord, 
		&m_recRegion);
}
