/// \file       Node.hpp
/// \date       17/10/2017
/// \package    Engine
/// \author     Vincent STEHLY--CALISTO

#ifndef __AI_NODE_HPP
#define __AI_NODE_HPP

#include <memory>  ///< std::hash<T>
#include <cstdlib> ///< std::size_t

#include "TieHelper.hpp"

/// \namespace AI
namespace AI
{

/// \class  Node
/// \brief  Stores node
/// \tparam CoordinateType The type of the coordinates
/// \tparam PriorityType   The type of the priority
template <typename CoordinateType, typename PriorityType>
class Node
{
public:

    /// \brief  Typed enum to represent in native language
    ///         all masks to test neighbor directions
    ///
    enum EMask : unsigned char
    {
        NONE  = 0x0,        ///< 0b00000000
        NORTH = 0x1 << 3,   ///< 0b00001000
        EAST  = 0x1 << 2,   ///< 0b00000100
        SOUTH = 0x1 << 1,   ///< 0b00000010
        WEST  = 0x1 << 0,   ///< 0b00000001
        ALL   = 0xF         ///< 0b00001111
    };

    typedef Node<CoordinateType, PriorityType> TNode;

    /// \brief  Default constructor
    explicit /* inline */ Node() : xy(0), m_priority(0), m_neighbors(TNode::EMask::NONE)
    { /* None */ }

    /// \brief  Constructs a node from 2 coordinates
    /// \param  X The x coordinate
    /// \param  Y The y coordinate
    explicit /* inline */ Node(CoordinateType X, CoordinateType Y) : x(X), y(Y), m_priority(0), m_neighbors(TNode::EMask::NONE)
    { /* None */ }

    /// \brief  Constructs a node from the packed coordinates
    /// \param  XY The xy coordinate
    explicit /* inline */ Node(typename TieTypeHelper<CoordinateType>::TieType XY) : xy(XY), m_priority(0), m_neighbors(TNode::EMask::NONE)
    { /* None */ }

    /// \brief  Copy Constructor
    /// \param  other The node to copy
    /* inline */ Node(const TNode & other) : xy(other.xy), m_priority(other.m_priority), m_neighbors(other.m_neighbors)
    { /* None */ }

    /// \brief  Default destructor
    /* inline */ ~Node() = default;

    /// \brief  Returns the X coordinate of the node
    /// \return  The X coordinate
    /* inline */ CoordinateType X() const
    { return x; }

    /// \brief  Returns the Y coordinate of the node
    /// \return  The Y coordinate
    /* inline */ CoordinateType Y() const
    { return y; }

    /// \brief  Returns the XY coordinate of the node
    /// \return  The XY coordinate
    /* inline */ typename TieTypeHelper<CoordinateType>::TieType XY() const
    { return xy; }

    /// \brief  Sets the X coordinate
    /// \param  X The X coordinate
    /* inline */ void X(CoordinateType X)
    { x = X; }

    /// \brief  Sets the Y coordinate
    /// \param  Y The Y coordinate
    /* inline */ void Y(CoordinateType Y)
    { y = Y; }

    /// \brief  Sets the XY coordinate
    /// \param  XY The XY coordinate
    /* inline */ void XY(typename TieTypeHelper<CoordinateType>::TieType XY)
    { xy = XY; }

    /// \brief  Tells if the given node is equal of the current node
    /// \return Returns true or false
    /* inline */ bool operator==(const TNode & other) const
    { return xy == other.xy; }

    /// \brief  Tells if the given node is different of the current node
    /// \return True or false
    /* inline */ bool operator!=(const TNode & other) const
    { return xy != other.xy; }

    /// \brief  Sets the priority of the node
    /// \param  cost The new priority
    /* inline */ void SetPriority(PriorityType priority)
    { m_priority = priority; }

    /// \brief  Returns the priority of the node
    /// \return The priority of the node
    /* inline */ PriorityType GetPriority() const
    { return m_priority; }

    /// \brief  Overload of operator < for priority queue
    ///         Note : This operator makes sense only for queue
    /// \return True or false
    /* inline */ bool operator<(const TNode & other) const
    { return m_priority > other.m_priority; }

    /// \brief  Adds a neighbor to the current node
    /// \param  neighborMask The mask corresponding to the neighbor to add
    /* inline */ void AddNeighborMask(EMask neighborMask)
    { m_neighbors |= neighborMask; }

    /// \brief  Sets the neighbors from a mask
    /// \param  neighborMask The mask corresponding to neighbors
    /* inline */ void SetNeighborMask(unsigned char neighborMask)
    { m_neighbors = neighborMask; }

    /// \brief  Returns the neighbors mask
    /// \return The neighbors mask
    /* inline */ unsigned char GetNeighborMask() const
    { return m_neighbors; }

private:

    /// \brief  Coordinates aren't store in a Coordinate class anymore
    ///         to avoid automatic call to constructors
    union
    {
        struct
        {
            CoordinateType x;   ///< The X coordinate
            CoordinateType y;   ///< The Y coordinate
        };

        typename TieTypeHelper<CoordinateType>::TieType xy; ///< The XY coordinate
    };

    PriorityType m_priority; ///< The priority of the node

    /// \brief  Stores the positions of all neighbors
    ///         of the current node in binary
    unsigned char m_neighbors;
};

/// \brief  Functor to hash a node
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct NodeHash
{
    /* inline */ std::size_t operator() (const Node<CoordinateType, CostType> & current) const
    {
        return ((std::hash<CoordinateType>()(current.X()) ^
                (std::hash<CoordinateType>()(current.Y()) << 1)) >> 1);
    }
};

/// \brief  Functor to compare two nodes
/// \tparam CoordinateType The type used in the coordinate system
/// \tparam CostType The type used for cost
template <typename CoordinateType, typename CostType>
struct NodeCompare
{
    /* inline */ bool operator() (const Node<CoordinateType, CostType> & lhs,
                                  const Node<CoordinateType, CostType> & rhs) const
    {
        return (lhs.XY() == rhs.XY());
    }
};

} /// AI

#endif // __AI_NODE_HPP
