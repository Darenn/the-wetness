/// \file       Window.hpp
/// \date       03/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <cassert>
#include <Windows.h>

/// \class  Window
/// \brief  Manages frames 
class Window
{
public:

	 Window				    (void);
	~Window				    (void);

	void Open				(const char * pWTitle, unsigned short WWidth, unsigned short WHeight);
	void Close				(void);

	void Clear				(void);
	void Draw				(CHAR value, WORD attribute,  USHORT x, USHORT y);
	void Draw				(CHAR_INFO * pBuffer,		  USHORT w, USHORT h, USHORT x, USHORT y);
	void Display			(void);

	/// \brief	Tells if the window is open or not
	/// \return True or false
	inline bool IsOpen(void) const
	{ return m_isOpen; }

	/// \brief	Returns the width of the window
	/// \note	Moves the function into a .inl file
	/// \return The width of the window
	inline unsigned short GetWidth(void) const
	{ return m_width; }

	/// \brief	Returns the height of the window
	/// \note	Moves the function into a .inl file
	/// \return The height of the window
	inline unsigned short GetHeight(void) const
	{ return m_height; }

private:

	void InitializeFrameBuffers	(void);

private:

	CHAR_INFO		m_pFrameBuffer[200][200];

	HWND			m_pConsole;		   ///< A pointer on the console
	HANDLE			m_pSTDOutput;	   ///< A pointer on the STD output

	COORD			m_dwBufferSize;	
	COORD			m_dwBufferCoord;
	SMALL_RECT		m_recRegion;	

	bool			m_isOpen;
	unsigned short  m_width;
	unsigned short  m_height;
};

#endif // _WINDOW_HPP
