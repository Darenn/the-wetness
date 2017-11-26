/// \file       Rectangle.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Rendering/Rectangle.hpp"

/// \brief	Constructs a rectangle shape from parameters
/// \param  X The x pos
/// \param  Y The y pos
/// \param  H The height of the rectangle
/// \param  W The width  of the recrangle
Rectangle::Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W)
: Rectangle(X, Y, H, W, Color()) 
{
	// Delegated constructor
}

/// \brief	Constructs a rectangle shape from parameters
/// \param  X The x pos
/// \param  Y The y pos
/// \param  H The height of the rectangle
/// \param  W The width  of the recrangle
/// \param  C The color  of the rectangle
Rectangle::Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W, Color C)
: x(X)
, y(Y)
, h(H)
, w(W)
, c(C)
{
	// None
}