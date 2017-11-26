/// \file       Rectangle.hpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef __RECTANGLE_HPP
#define __RECTANGLE_HPP

#include <Windows.h>
#include "Color.hpp"

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
	Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W);

	/// \brief	Constructs a rectangle shape from parameters
	/// \param  X The x pos
	/// \param  Y The y pos
	/// \param  H The height of the rectangle
	/// \param  W The width  of the recrangle
	/// \param  C The color of the rectangle
	Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W, Color C);

	USHORT x;
	USHORT y;
	USHORT h;
	USHORT w;
	Color  c;
};

#endif // __RECTANGLE_HPP