/// \file       Window.hpp
/// \date       08/10/2017
/// \package    Engine/Window
/// \author     Vincent STEHLY--CALISTO

#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <string>
#include <Windows.h>

#include "Timer.hpp"
#include "Vector2.hpp"

#define	MAX_BUFFER_X 1024
#define MAX_BUFFER_Y 768

/// \class  Window
/// \brief  Manages window console output
class Window
{
public:

	Window	(void);
	~Window	(void);

	void Open	(const std::string & title, const Vector2u & size, bool debug);
	void Close	(void);

	void Clear	(void);
	void Display(void);

	void Draw	(WCHAR value, WORD attribute, USHORT x, USHORT y);
	void Draw	(CHAR  value, WORD attribute, USHORT x, USHORT y);
	void Draw	(CHAR_INFO * pBuffer, USHORT h, USHORT w, USHORT x, USHORT y);
	
	void SetTitle		(const std::string & title);

	inline bool			  IsOpen   (void) const;
	inline unsigned short GetWidth (void) const;
	inline unsigned short GetHeight(void) const;

	inline void SetDrawCall (float draw);
	inline void SetFPS      (unsigned fps);

private:

	void	InitializeFrameBuffers	(void);
	void	DrawDebugInformations	(void);
	void    SetWindowSize           (const Vector2u & size);
	void	SetCharacterSize        (unsigned short size);
	void    DrawDebugString         (const std::string & debug, const Vector2u & size);

	static HWND	  GetConsoleHandle(void);
	static HANDLE GetOutputHandle (void);

private:

	CHAR_INFO       m_pFrameBuffer[MAX_BUFFER_Y][MAX_BUFFER_X];

	HWND			m_pConsole;
	HANDLE			m_pSTDOutput;

	SMALL_RECT		m_recRegion;
	COORD			m_dwBufferSize;
	COORD			m_dwBufferCoord;
	
	bool			m_debug;
	bool			m_isOpen;
	
	Vector2u		m_windowSize;
	Vector2u		m_bufferSize;

	std::string     m_title;

	// Debug informations
	unsigned int 	m_fps;
	unsigned int	m_frameCounter;
	unsigned int    m_drawCall;
};

#include "Window.inl"

#endif // _WINDOW_HPP
