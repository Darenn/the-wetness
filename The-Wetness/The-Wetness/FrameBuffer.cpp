/// \file       FrameBuffer.cpp
/// \date       03/10/2017
/// \package    ASCIIENgine
/// \author     Vincent STEHLY--CALISTO

#include "FrameBuffer.hpp"

/// \brief	Initializes the frame buffer with a width and a height.
///			Allocates a 2D array fetched into one big 1D array.
/// \param  WWidth  The width of the window
/// \param  WHeight The height of the window
void FrameBuffer::Initialize(unsigned short WWidth, unsigned short WHeight)
{
	m_width           = WWidth;
	m_height          = WHeight;
	m_bufferSize      = m_width * m_height;
	m_pInternalBuffer = nullptr;
	m_pInternalBuffer = new CHAR_INFO[m_bufferSize];

	assert(nullptr != m_pInternalBuffer);

	Clear();
}

/// \brief	Releases the frame buffer. Releases the array.
void FrameBuffer::Release(void)
{
	if (nullptr != m_pInternalBuffer)
	{
		delete[] m_pInternalBuffer;
		m_pInternalBuffer = nullptr;
	}
}

/// \brief	Resets the frame buffer
void FrameBuffer::Clear(void)
{
	assert(nullptr != m_pInternalBuffer);

	for (unsigned int nBuffer = 0; nBuffer < m_bufferSize; ++nBuffer)
	{
		m_pInternalBuffer[nBuffer].Char.AsciiChar = 0x0;
		m_pInternalBuffer[nBuffer].Attributes     = 0x0;
	}
}
