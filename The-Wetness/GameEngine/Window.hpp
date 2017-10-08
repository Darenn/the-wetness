/// \file       Window.hpp
/// \date       08/10/2017
/// \package    Engine/Window
/// \author     Vincent STEHLY--CALISTO

#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include "Timer.hpp"

/// \class  Window
/// \brief  Manages window console output
class Window
{
public:

	explicit Window	(void);
			~Window	(void);

	void Open	(const char * pTitle, USHORT width, USHORT height);
	void Close	(void);

	// Rendering
	void Clear	(void);
	void Draw	(WCHAR value, WORD attribute, USHORT x, USHORT y);
	void Draw	(CHAR  value, WORD attribute, USHORT x, USHORT y);
	void Draw	(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y);
	void Display(void);

	// Utility
	void SetTitle(const char * pTitle);
	void SetWindowSize(USHORT H, USHORT W);

	/// \brief	Tells if the window is open or not
	/// \return True or false
	inline bool IsOpen(void) const
	{
		return m_isOpen;
	}

	/// \brief	Returns the width of the window
	/// \note	Moves the function into a .inl file
	/// \return The width of the window
	inline unsigned short GetWidth(void) const
	{
		return m_width;
	}

	/// \brief	Returns the height of the window
	/// \note	Moves the function into a .inl file
	/// \return The height of the window
	inline unsigned short GetHeight(void) const
	{
		return m_height;
	}

private:

	void InitializeFrameBuffers(void);
	void DrawFPS(void);

private:

	CHAR_INFO		m_pFrameBuffer[70][70];

	HWND			m_pConsole;		   ///< A pointer on the console
	HANDLE			m_pSTDOutput;	   ///< A pointer on the STD output

	COORD			m_dwBufferSize;
	COORD			m_dwBufferCoord;
	SMALL_RECT		m_recRegion;

	Timer			m_timer;

	bool			m_isOpen;
	float			m_lastTime;
	unsigned short  m_width;
	unsigned short  m_height;
	unsigned short  m_bufferWidth;
	unsigned short  m_bufferHeight;
	unsigned int    m_currentFrame;
	unsigned int    m_fpsCounter;
	unsigned int    m_frameCounter;
	unsigned int    m_drawCallCounter;
};

#endif // _WINDOW_HPP
