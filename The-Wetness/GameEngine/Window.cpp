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
/// \param  title  The title of the window
/// \param  size   The dimension of the window
/// \param  debug  The debug mode
void Window::Open(const std::string & title, const Vector2u & size, bool debug)
{
	assert(size.x >= 100  && size.y >= 100);
	assert(size.x <= MAX_BUFFER_X && size.y <= MAX_BUFFER_Y);

	m_debug  = debug;
	m_isOpen = false;

	m_windowSize = size;
	m_bufferSize = size;

	m_pConsole     = nullptr;
	m_pSTDOutput   = nullptr;
	
	m_pConsole   = GetConsoleHandle();
	m_pSTDOutput = GetOutputHandle();

	assert(nullptr != m_pConsole);
	assert(INVALID_HANDLE_VALUE != m_pSTDOutput);

	SetTitle(m_title);
	SetCharacterSize(1);
	SetWindowSize(m_windowSize);

	// Buffering screen rect
	m_dwBufferCoord = { 0, 0 };
	m_dwBufferSize  = {       static_cast<SHORT>(m_bufferSize.x),     static_cast<SHORT>(m_bufferSize.y)     };
	m_recRegion     = { 0, 0, static_cast<SHORT>(m_bufferSize.x) - 1, static_cast<SHORT>(m_bufferSize.y) - 1 };

	// Handles ok, initializing frame buffer
	InitializeFrameBuffers();

	// The window is now open
	m_isOpen = true;
}

/// \brief	Close the window, releases all frame buffers
void Window::Close(void)
{
	m_isOpen = false;
	
	m_pConsole     = nullptr;
	m_pSTDOutput   = nullptr;
}

/// \brief	Initializes all frame buffers
void Window::InitializeFrameBuffers(void)
{
	Clear();
}

/// \brief	Returns the window console
/// \return A handle on the window
/* static */ HWND Window::GetConsoleHandle()
{
	return GetConsoleWindow();
}

/// \brief	Returns the handle on the standard output
///			with a read write access
/// \return An handle on the std output
/* static */ HANDLE Window::GetOutputHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE | GENERIC_READ | GENERIC_WRITE);
}

/// \brief	Sets the character size of the console
/// \param  size The size to set
void Window::SetCharacterSize(unsigned short size)
{
	CONSOLE_FONT_INFOEX consoleFontInfo;

	// Filling the structure with the new font size
	consoleFontInfo.nFont        = 0;
	consoleFontInfo.cbSize		 = sizeof(consoleFontInfo);
	consoleFontInfo.FontFamily   = FF_DONTCARE;
	consoleFontInfo.FontWeight   = FW_DEMIBOLD;
	consoleFontInfo.dwFontSize.X = static_cast<short>(size);
	consoleFontInfo.dwFontSize.Y = static_cast<short>(size);
	
	// Font name copy
	std::wcscpy(consoleFontInfo.FaceName, L"Consolas");

	// Updates the console info ...
	SetCurrentConsoleFontEx(m_pSTDOutput, FALSE, &consoleFontInfo);
}

/// \brief	Sets the window title
/// \param  title The title to set
void Window::SetTitle(const std::string& title)
{
	m_title = title;

	assert(64 > m_title.size());
	assert(nullptr != m_pConsole);
	
	wchar_t wTitle[64];
	swprintf(wTitle, 64, L"%hs", m_title.c_str());
	
	SetConsoleTitle(wTitle);
}

/// \brief	Sets the window size
/// \param  size The new size of the window
void Window::SetWindowSize(const Vector2u& size)
{
	RECT currentRect;
	GetWindowRect(m_pConsole, &currentRect);

	// Resize the window to fit the given dimensions
	MoveWindow(m_pConsole, 
		currentRect.left, 
		currentRect.top,
		m_windowSize.x, 
		m_windowSize.y, TRUE);
}

/// \brief	Clear the current frame buffer
void Window::Clear(void)
{
	for (int nBufferY = 0; nBufferY < m_bufferSize.y; ++nBufferY)
	{
		CHAR_INFO * nBuffer = m_pFrameBuffer[nBufferY];
		for (int nBufferX = 0; nBufferX < m_bufferSize.x; ++nBufferX)
		{
			nBuffer[nBufferX].Attributes       = 0x0;
			nBuffer[nBufferX].Char.AsciiChar   = ' ';
			nBuffer[nBufferX].Char.UnicodeChar = 0x0020;
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
}

/// \brief	Draws a wchar at the given position
/// \param  value The char to draw
/// \param  attribute The value of the char to draw
/// \param  x The x coordinate
/// \param  y The y coordinate
void Window::Draw(WCHAR value, WORD attribute, USHORT x, USHORT y)
{
	m_pFrameBuffer[y][x].Char.UnicodeChar = value;
	m_pFrameBuffer[y][x].Attributes = attribute;
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
			if (y + nRow < m_bufferSize.y && x + nCol < m_bufferSize.x)
			{
				m_pFrameBuffer[y + nRow][x + nCol] = nBuffer[nCol];
			}
		}
	}
}

/// \brief Displays the current buffer by swapping buffers
/// \see   https://docs.microsoft.com/en-us/windows/console/writeconsoleoutput
///		   "The storage for this buffer is allocated from a shared heap for 
///			  the process that is 64 KB in size. The maximum size of the buffer 
///			  will depend on heap usage."
///		   So, I have increase the stack size to 4 MB
void Window::Display(void)
{
	// Sends the current buffer to the windows console's buffer
	WriteConsoleOutput(m_pSTDOutput, m_pFrameBuffer[0],
		m_dwBufferSize,
		m_dwBufferCoord,
		&m_recRegion);
}

/// \brief	Draws debug informations
void Window::DrawDebugInformations()
{
	// TODO
}
