/// \file       Coordinate.hpp
/// \date       17/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef __COORDINATE_HPP
#define __COORDINATE_HPP

#include "TieHelper.hpp"

/// \struct Coordinate
/// \brief  Stores a 2D coordinate
/// \tparam CoordinateType The type of the coordinate system
template <typename CoordinateType>
struct Coordinate
{
    /// \brief  Default constructor
    explicit /* inline */ Coordinate(void) : XY(0)
    { /* None */ }

    /// \brief  Initializes from two coordinates
    /// \param  x The X coordinate
    /// \param  y The Y coordinate
    explicit /* inline */ Coordinate(CoordinateType x, CoordinateType y) : X(x), Y(y)
    { /* None */ }

    /// \brief  Initializes from two coordinates packed into a large data type
    /// \param  xy The XY coordinate
    explicit /* inline */ Coordinate(typename TieTypeHelper<CoordinateType>::TieType xy) : XY(xy)
    { /* None */ }

    /// \brief  Initializes from another coordinate of same type
    /// \param  other The other coordinate
    /* inline */ Coordinate(const Coordinate<CoordinateType> & other) : XY(other.XY)
    { /* None */ }

    /// \brief  Default destructor
    /* inline */ ~Coordinate(void) = default;

    /// \brief  Tells if the given coordinate is equal to the current coordinate
    ///         Optimized : Makes only one operation instead of 3
    /// \return True or false
    /* inline */ bool operator==(const Coordinate<CoordinateType> & other) const
    { return XY == other.XY; }

    /// \brief  Tells if the given coordinate is different of the current coordinate
    ///         Optimized : Makes only one operation instead of 3
    /// \return True or false
    /* inline */ bool operator!=(const Coordinate<CoordinateType> & other) const
    { return XY != other.XY; }

    union
    {
        struct
        {
            CoordinateType X;   ///< The X coordinate
            CoordinateType Y;   ///< The Y coordinate
        };

        typename TieTypeHelper<CoordinateType>::TieType XY;
    };
};

#endif // __COORDINATE_HPP