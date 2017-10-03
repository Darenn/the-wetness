/// \file       FrameBuffer.hpp
/// \date       03/10/2017
/// \package    ASCIIENgine
/// \author     Vincent STEHLY--CALISTO

#ifndef _FRAME_BUFFER_HPP
#define _FRAME_BUFFER_HPP

#include <cassert>
#include <Windows.h>

/// \class  FrameBuffer
/// \brief  Stores a frame 
class FrameBuffer
{
public:

	void Initialize(unsigned short WWidth, unsigned short WHeight);
	void Release   (void);
	void Clear	   (void);

	/// \brief	Returns the internal buffer of the frame buffer
	inline CHAR_INFO * GetInternalBuffer(void)
	{ return m_pInternalBuffer; }

private:

	unsigned short	m_width;
	unsigned short	m_height;
	unsigned int	m_bufferSize;
	CHAR_INFO *		m_pInternalBuffer;
};

#endif // _FRAME_BUFFER_HPP
