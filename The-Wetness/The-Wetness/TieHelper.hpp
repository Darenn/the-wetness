/// \file       TieHelper.hpp
/// \date       17/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef __TIE_HELPER_HPP
#define __TIE_HELPER_HPP

/// \brief  Deduces the type of coordinates pack
/// \tparam CoordinateType The type of the coordinates
///         Should be char, short or int
template <typename CoordinateType>
struct TieTypeHelper
{
    // Should generate an error
};

template </* Specialized for type char */>
struct TieTypeHelper <char>
{
    typedef short TieType;
    static constexpr unsigned char TypeShift = 8;
};

template </* Specialized for type short */>
struct TieTypeHelper <short>
{
    typedef int TieType;
    static constexpr unsigned char TypeShift = 16;
};

template </* Specialized for type int */>
struct TieTypeHelper <int>
{
    typedef long long TieType;
    static constexpr unsigned char TypeShift = 32;
};

/// \brief  Ties two coordinates into one larger
///         Two chars coords gives a short
///         Two short coords gives an int
///         Two int   coords gives a long long
/// \tparam CoordinateType The type of the coordinates
///         Should be char, short or int
/// \return The pack of coordinates
template <typename CoordinateType>
static constexpr inline typename TieTypeHelper<CoordinateType>::TieType Tie(CoordinateType X, CoordinateType Y)
{
    return (X | ((typename TieTypeHelper<CoordinateType>::TieType) Y << TieTypeHelper<CoordinateType>::TypeShift));
}

#endif // __TIE_HELPER_HPP