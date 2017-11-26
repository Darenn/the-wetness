/// \file       RectangleShape.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Rendering/RectangleShape.hpp"

/// \brief	Constructs a rectangle shape from parameters
/// \param  X The x pos
/// \param  Y The y pos
/// \param  H The height of the rectangle
/// \param  W The width  of the recrangle
RectangleShape::RectangleShape(USHORT X, USHORT Y, USHORT H, USHORT W)
: RectangleShape(X, Y, H, W, Color())
{
	// Delegated constructor
}

/// \brief	Constructs a rectangle shape from parameters
/// \param  X The x pos
/// \param  Y The y pos
/// \param  H The height of the rectangle
/// \param  W The width  of the recrangle
/// \param  C The color  of the rectangle
RectangleShape::RectangleShape(USHORT X, USHORT Y, USHORT H, USHORT W, Color C)
: x(X)
, y(Y)
, h(H)
, w(W)
, c(C)
{
	// None
}