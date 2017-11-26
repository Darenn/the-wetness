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
/* explicit */ Rectangle::Rectangle(USHORT X, USHORT Y, USHORT H, USHORT W)
: x(X)
, y(Y)
, h(H)
, w(W)
{
	// None
}