/// \file       SquareGrid.inl
/// \date       17/10/2017
/// \package    Engine
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
                case TNode::NORTH:
                    if(IsValidNode(x, y - 1) && (GetNode(x, y - 1).GetNeighborMask() & TNode::SOUTH))
                    {
                        neighbors.push_back(GetNode(x, y - 1));
                    }
                    break;

                case TNode::EAST:
                    if(IsValidNode(x + 1, y) && (GetNode(x + 1, y).GetNeighborMask() & TNode::WEST))
                    {
                        neighbors.push_back(GetNode(x + 1, y    ));
                    }
                    break;

                case TNode::SOUTH:
                    if(IsValidNode(x, y + 1) && (GetNode(x, y + 1).GetNeighborMask() & TNode::NORTH))
                    {
                        neighbors.push_back(GetNode(x, y + 1));
                    }
                    break;

                case TNode::WEST:
                    if(IsValidNode(x - 1, y) && (GetNode(x - 1, y).GetNeighborMask() & TNode::EAST))
                    {
                        neighbors.push_back(GetNode(x - 1, y));
                    }
                    break;

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

/// \brief  Tells if the node is valid or node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \return True or false
template <typename CoordinateType, typename PriorityType>
inline bool SquareGrid<CoordinateType, PriorityType>::IsValidNode(CoordinateType x, CoordinateType y) const
{
    return (x >= 0 && x < m_width && y >= 0 && y < m_height);
}

}