/// \file       Window.cpp
/// \date       03/10/2017
/// \package    ASCIIENgine
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
	m_pConsole       = nullptr;
	m_pSTDOutput     = nullptr;
	m_pCurrentBuffer = nullptr;

	// Gets descriptors
	m_pConsole   = GetConsoleWindow();
	m_pSTDOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	assert(nullptr != m_pConsole);
	assert(nullptr != m_pSTDOutput);

	// Buffering screen rect
	m_dwBufferCoord = { 0, 0 };
	m_dwBufferSize  = {       static_cast<SHORT>(m_width),     static_cast<SHORT>(m_height)     };
	m_recRegion     = { 0, 0, static_cast<SHORT>(m_width) - 1, static_cast<SHORT>(m_height) - 1 };

	SetConsoleTitle((LPCWSTR)pWTitle);

	RECT currentRect;
	GetWindowRect(m_pConsole, &currentRect);

	// Resize the window to fit the given dimensions
	MoveWindow(m_pConsole, currentRect.left, currentRect.top, m_width, m_height, TRUE);

	InitializeFrameBuffers();
}

/// \brief	Close the window, releases all frame buffers
void Window::Close(void)
{
	m_buffers[0].Release();
	m_buffers[1].Release();
}

/// \brief	Initializes all frame buffers
void Window::InitializeFrameBuffers(void)
{
	m_buffers[0].Initialize(m_width, m_height);
	m_buffers[1].Initialize(m_width, m_height);
}

/// \brief	Clear the current buffer
void Window::Clear(void)
{
	assert(nullptr != m_pCurrentBuffer);
	m_pCurrentBuffer->Clear();
}

/// \brief	Draws a shape into the current buffer
void Window::Draw(void)
{
	// TODO
}

/// \brief Displays the current buffer by swapping buffers
void Window::Display(void)
{
	// Sends the current buffer to the windows console's buffer
	WriteConsoleOutput(m_pSTDOutput, (CHAR_INFO *)m_pCurrentBuffer->GetInternalBuffer(), 
		m_dwBufferSize,
		m_dwBufferCoord, 
		&m_recRegion);

	// And then, swaps buffers
	if (m_pCurrentBuffer == &m_buffers[0])
	{
		m_pCurrentBuffer = &m_buffers[1];
	}
	else
	{
		m_pCurrentBuffer = &m_buffers[0];
	}
}
