/// \file       RectangleShape.hpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef __RECTANGLE_SHAPE_HPP
#define __RECTANGLE_SHAPE_HPP

#include <Windows.h>
#include "Color.hpp"

/// \class RectangleShape
/// \brief Store the drawable Rectangle
class RectangleShape
{
public:

	/// \brief	Constructs a rectangle shape from parameters
	/// \param  X The x pos
	/// \param  Y The y pos
	/// \param  H The height of the rectangle
	/// \param  W The width  of the recrangle
	RectangleShape(USHORT X, USHORT Y, USHORT H, USHORT W);

	/// \brief	Constructs a rectangle shape from parameters
	/// \param  X The x pos
	/// \param  Y The y pos
	/// \param  H The height of the rectangle
	/// \param  W The width  of the recrangle
	/// \param  C The color of the rectangle
	RectangleShape(USHORT X, USHORT Y, USHORT H, USHORT W, Color C);

	USHORT x;
	USHORT y;
	USHORT h;
	USHORT w;
	Color  c;
};

#endif // __RECTANGLE_SHAPE_HPP