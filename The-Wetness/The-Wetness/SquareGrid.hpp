/// \file       SquareGrid.hpp
/// \date       17/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef _AI_SQUARE_GRID_HPP
#define _AI_SQUARE_GRID_HPP

#include <vector>
#include <algorithm>
#include "Node.hpp"

/// \namespace AI
namespace AI
{

/// \class  SquareGrid
/// \brief  Stores a 2D square grid
/// \tparam CoordinateType The type of the coordinate system
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class SquareGrid
{
public:

    typedef Node<CoordinateType, PriorityType> TNode;

    /// \brief  Initializes a grid width x height
    /// \param  width The width of the grid
    /// \param  height The height of the grid
    void Initialize(CoordinateType width, CoordinateType height);

    /// \brief  Puts into neighbors all direct neighbors of the given node
    /// \param  current The node to check
    /// \param  neighbors The vector of neighbors
    inline void GetNeighbors(const TNode & current, std::vector < TNode > & neighbors) const;

    /// \brief  Returns a read only reference on a node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \return A reference on a node
    inline const TNode & GetNode (CoordinateType x, CoordinateType y) const;

    /// \brief  Sets the mask of a node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \param  mask The mask to apply
    inline void SetNodeMask(CoordinateType x, CoordinateType y, unsigned char mask);

    /// \brief  Tells if the node is valid or node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \return True or false
    inline bool IsValidNode(CoordinateType x, CoordinateType y) const;

private:

    CoordinateType m_width;
    CoordinateType m_height;

    std::vector < TNode >  m_grid; ///< The 2D grid
};

} // AI

#include "SquareGrid.inl"

#endif // _AI_SQUARE_GRID_HPP