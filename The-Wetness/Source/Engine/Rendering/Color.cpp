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

/// \brief	Copy constructor
/* explicit */ Color::Color(Color const& other)
: attribute(other.attribute)
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

/* static */ Color const Color::Black  = Color(Color::EColor::BLACK);
/* static */ Color const Color::Grey   = Color(Color::EColor::GREY);;
/* static */ Color const Color::Blue   = Color(Color::EColor::BLUE);
/* static */ Color const Color::Green  = Color(Color::EColor::GREEN);
/* static */ Color const Color::Red    = Color(Color::EColor::RED);
/* static */ Color const Color::Purple = Color(Color::EColor::PURPLE);
/* static */ Color const Color::Yellow = Color(Color::EColor::YELLOW);
/* static */ Color const Color::White  = Color(Color::EColor::WHITE);