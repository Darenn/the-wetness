/// \file       Node.hpp
/// \date       17/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef __NODE_HPP
#define __NODE_HPP

#include "Coordinate.hpp"

/// \class  Node
/// \brief  Stores node
/// \tparam CoordinateType The type of the coordinates
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class Node
{
public :

    typedef Node<CoordinateType, PriorityType> TNode;

    /// \brief  Default constructor
    explicit /* inline */ Node(void) : m_isPassable(true), m_priority(0), m_coordinate(Tie<CoordinateType>(0, 0))
    { /* None */ }

    /// \brief  Constructs a node from 2 coordinates
    /// \param  X The x coordinate
    /// \param  Y The y coordinate
    explicit /* inline */ Node(CoordinateType X, CoordinateType Y) :  m_isPassable(true), m_priority(0), m_coordinate(X, Y)
    { /* None */ }

    /// \brief  Constructs a node from the packed coordinates
    /// \param  XY The xy coordinate
    explicit /* inline */ Node(typename TieTypeHelper<CoordinateType>::TieType XY) :  m_isPassable(true), m_priority(0), m_coordinate(XY)
    { /* None */ }

    /// \brief  Copy Constructor
    /// \param  other The node to copy
    /* inline */ Node(const TNode & other) :  m_isPassable(other.m_isPassable), m_priority(other.m_priority), m_coordinate(other.m_coordinate.XY), m_neighbors(other.m_neighbors)
    { /* None */ }

    /// \brief  Default destructor
    /* inline */ ~Node(void) = default;

    /// \brief  Returns the X coordinate of the node
    /// \return  The X coordinate
    /* inline */ CoordinateType X(void) const
    { return m_coordinate.X; }

    /// \brief  Returns the Y coordinate of the node
    /// \return  The Y coordinate
    /* inline */ CoordinateType Y(void) const
    { return m_coordinate.Y; }

    /// \brief  Returns the XY coordinate of the node
    /// \return  The XY coordinate
    /* inline */ typename TieTypeHelper<CoordinateType>::TieType XY(void) const
    { return m_coordinate.XY; }

    /// \brief  Sets the X coordinate
    /// \param  X The X coordinate
    /* inline */ void X(CoordinateType X)
    { m_coordinate.X = X; }

    /// \brief  Sets the Y coordinate
    /// \param  Y The Y coordinate
    /* inline */ void Y(CoordinateType Y)
    { m_coordinate.Y = Y; }

    /// \brief  Sets the XY coordinate
    /// \param  XY The XY coordinate
    /* inline */ void XY(typename TieTypeHelper<CoordinateType>::TieType XY)
    { m_coordinate.XY = XY; }

    /// \brief  Tells if the given node is equal of the current node
    /// \return Returns true or false
    /* inline */ bool operator==(const TNode & other) const
    { return m_coordinate == other.m_coordinate; }

    /// \brief  Tells if the given node is different of the current node
    /// \return True or false
    /* inline */ bool operator!=(const TNode & other) const
    { return m_coordinate != other.m_coordinate; }

    /// \brief  Sets the priority of the node
    /// \param  cost The new priority
    /* inline */ void SetPriority(PriorityType priority)
    { m_priority = priority; }

    /// \brief  Returns the priority of the node
    /// \return The priority of the node
    /* inline */ PriorityType GetPriority(void) const
    { return m_priority; }

    /// \brief  Tells if the node is passable
    /// \return True or false
    /* inline */ bool IsPassable(void) const
    { return m_isPassable; }

    /// \brief  Sets the type of the node
    /// \param  passable True or false
    /* inline */ void SetPassable(bool passable)
    { m_isPassable = passable; }

    /// \brief  Overload of operator < for priority queue
    /// \return True or false
    /* inline */ bool operator<(const TNode & other) const
    { return m_priority > other.m_priority; }

    /// \brief  Adds a neighbor to the current node
    /// \param  neighbor A const reference on the neighbor to add
    /* inline */ void AddNeighbor(TNode * neighbor)
    { m_neighbors.push_back(neighbor); }

    /// \brief  Returns the list of neighbors of the current node
    /// \return A vector of nodes
    /* inline */ const std::vector < TNode * > & GetNeighbors(void) const
    { return m_neighbors; }

    /// \brief  Reserves the order of the neighbors
    /* inline */ void ReverseNeighbors(void)
    { std::reverse(m_neighbors.begin(), m_neighbors.end()); }

private:

    Coordinate<CoordinateType> m_coordinate;
    PriorityType               m_priority;
    bool                       m_isPassable;

    // Optimization for static grids
    std::vector < TNode * >     m_neighbors;
};

/// \brief  Functor to hash a node
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct NodeHash
{
    //typedef Node<CoordinateType, CostType> TNode;

    /* inline */ std::size_t operator() (const Node<CoordinateType, CostType> & current) const
    {
        return ((std::hash<int>()(current.X()) ^
                (std::hash<int>()(current.Y()) << 1)) >> 1);
    }
};

/// \brief  Functor to compare two nodes
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct NodeCompare
{
    //typedef Node<CoordinateType, CostType> TNode;

    /* inline */ bool operator() (const Node<CoordinateType, CostType> & lhs, const Node<CoordinateType, CostType> & rhs) const
    {
        return (lhs.XY() == rhs.XY());
    }
};

#endif // __NODE_HPP