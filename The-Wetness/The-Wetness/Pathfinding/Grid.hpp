/// \file       Grid.hpp
/// \date       12/07/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef __GRID_HPP
#define __GRID_HPP

#include <vector>
#include <algorithm>

#include "Node.hpp"

/// \class  Grid
/// \brief  Stores a 2D squared grid
///         /!\ This class must implements the following methods
/// \tparam CoordinateType The type of the coordinate system
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class Grid
{
public:

    typedef Node<CoordinateType, PriorityType> TNode;

    /// \brief  Initializes a grid width x height
    /// \param  width The width of the grid
    /// \param  height The height of the grid
    void Initialize(CoordinateType width, CoordinateType height);

    /// \brief  Precomputes all neighbors and cost
    void Precompute(void);

    /// \brief  Puts into neighbors all direct neighbors of the given node
    /// \param  current The node to check
    /// \param  neighbors The vector where to store all neighbors
    inline void GetNeighbors(const TNode & current, std::vector <TNode> & neighbors) const;

    /// \brief  Returns all the neighbors of the given node
    /// \param  current The node to check
    /// \return The list of the neighbors of the given node
    inline void GetComputedNeighbors(const TNode & current, std::vector <TNode> & neighbors) const;

    /// \brief  Returns a read only reference on a node
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    /// \return A reference on a node
    inline const TNode & GetNode (CoordinateType x, CoordinateType y) const;

    /// \brief  The node will be considered as a wall
    /// \param  x The X coordinate of the node
    /// \param  y The Y coordinate of the node
    inline void SetNodeNonPassable(CoordinateType x, CoordinateType y);

private:

    CoordinateType m_width;  ///< The width of the grid
    CoordinateType m_height; ///< The Heigth of the height

    std::vector <TNode> m_grid; ///< The squared grid
};

#include "Grid.inl"

#endif // __GRID_HPP