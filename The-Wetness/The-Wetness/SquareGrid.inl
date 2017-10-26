/// \file       SquareGrid.inl
/// \date       17/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

/// \namespace AI
namespace AI
{

/// \brief  Initializes a n x m grid
/// \param  width The width of the grid
/// \param  height The height of the grid
template <typename CoordinateType, typename PriorityType>
void SquareGrid<CoordinateType, PriorityType>::Initialize(CoordinateType width, CoordinateType height)
{
    // Clear old grid
    m_grid.clear();

    m_width  = width;
    m_height = height;

    m_grid.reserve(m_width * m_height);
    for(CoordinateType nRow = 0; nRow < m_height; ++nRow)
    {
        for(CoordinateType nCol = 0; nCol < m_width; ++nCol)
        {
            m_grid.push_back(TNode(nCol, nRow));
        }
    }
}

/// \brief  Puts into neighbors all direct neighbors of the given node
/// \param  current The node to check
/// \param  neighbors The vector of neighbors
template <typename CoordinateType, typename PriorityType>
void SquareGrid<CoordinateType, PriorityType>::GetNeighbors(const TNode & current, std::vector < TNode > & neighbors) const
{
    // Getting neighbors mask
    CoordinateType x = current.X();
    CoordinateType y = current.Y();
    unsigned char neighborMask = current.GetNeighborMask();

    for(unsigned char nShift = 0; nShift < 4; ++nShift)
    {
        unsigned char currentMask = static_cast<unsigned char>(1 << nShift);
        if(neighborMask & currentMask)
        {
            // There is a neighbor in this direction
            switch(currentMask)
            {
                case TNode::EMask ::NORTH: neighbors.push_back(GetNode(x,     y - 1)); break;
                case TNode::EMask ::EAST:  neighbors.push_back(GetNode(x + 1, y    )); break;
                case TNode::EMask ::SOUTH: neighbors.push_back(GetNode(x,     y + 1)); break;
                case TNode::EMask ::WEST:  neighbors.push_back(GetNode(x - 1, y    )); break;
                default: break;
            }
        }
    }

    // See with and without
    // Small optimization for squared grid
    if ((x + y) % 2 == 0)
    {
        std::reverse(neighbors.begin(), neighbors.end());
    }
}

/// \brief  Returns a read only reference on a node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \return A read only reference on the wanted node
template <typename CoordinateType, typename PriorityType>
inline const Node<CoordinateType, PriorityType> & SquareGrid<CoordinateType, PriorityType>::GetNode(CoordinateType x, CoordinateType y) const
{
    return m_grid[y * m_width + x];
};

/// \brief  Sets the mask of a node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \param  mask The mask to apply
template <typename CoordinateType, typename PriorityType>
inline void SquareGrid<CoordinateType, PriorityType>::SetNodeMask(CoordinateType x, CoordinateType y, unsigned char mask)
{
    m_grid[y * m_width + x].SetNeighborMask(mask);
}

}


