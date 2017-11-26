/// \file       Rectangle.hpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef __RECTANGLE_HPP
#define __RECTANGLE_HPP

#include <Windows.h>

/// \class Rectangle
/// \brief Store the drawable Rectangle
class Rectangle
{
public:

	/// \brief	Constructs a rectangle shape from parameters
	/// \param  X The x pos
	/// \param  Y The y pos
	/// \param  H The height of the rectangle
	/// \param  W The width  of the recrangle
	explicit Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W);

	USHORT x;
	USHORT y;
	USHORT h;
	USHORT w;
};

#endif // __RECTANGLE_HPP