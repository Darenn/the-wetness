/// \file       TieHelper.hpp
/// \date       17/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef __AI_TIE_HELPER_HPP
#define __AI_TIE_HELPER_HPP

/// \namespace AI
namespace AI
{

/// \brief  Deduces the type of coordinates pack
/// \tparam CoordinateType The type of the coordinates
///         Should be char, short or int
template<typename CoordinateType>
struct TieTypeHelper
{
    // Should generate an error
};

template</* Specialized for type char */>
struct TieTypeHelper<char>
{
    typedef short TieType;
    static constexpr unsigned char TypeShift = 8;
};

template</* Specialized for type short */>
struct TieTypeHelper<short>
{
    typedef int TieType;
    static constexpr unsigned char TypeShift = 16;
};

template</* Specialized for type int */>
struct TieTypeHelper<int>
{
    typedef long long TieType;
    static constexpr unsigned char TypeShift = 32;
};

} // AI

#endif // __AI_TIE_HELPER_HPP