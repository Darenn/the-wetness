/// \file       Color.hpp
/// \date       26/11/2017
/// \package    Engine/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef __COLOR_HPP
#define __COLOR_HPP

#include <Windows.h>

/// \class Color
/// \brief Stores a color
class Color
{
public:

	enum class EColor : USHORT
	{
		GREY   = 0x0008,
		BLUE   = 0x0009,
		GREEN  = 0x000A,
		RED    = 0x000C,
		PURPLE = 0x000D,
		YELLOW = 0x000E,
		WHITE  = 0x000F,
	};

	Color();
	explicit Color(EColor color);
	explicit Color(USHORT attribute);

	USHORT attribute;
};

#endif // __COLOR_HPP