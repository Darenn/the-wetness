/// \file       Color.cpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Rendering/Color.hpp"

/// \brief	Constructor, default color : WHITE
/* explicit */ Color::Color()
	: attribute(static_cast<USHORT>(EColor::WHITE))
{
	// None
}

/// \brief	Constructor
/// \param  color The color enum
/* explicit */ Color::Color(EColor color)
: attribute(static_cast<USHORT>(color))
{
	// None
}

/// \brief	Constructor
/// \param  attribute The color attribute
/* explicit */ Color::Color(USHORT attribute)
: attribute(attribute)
{
	// None
}