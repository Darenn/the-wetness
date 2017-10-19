/// \file       Grid.inl
/// \date       12/07/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

/// \brief  Contains all node directions
struct s_dir
{
    int dx;
    int dy;
} directions[] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

/// \brief  Initializes a n x m grid
/// \param  width The width of the grid
/// \param  height The height of the grid
template <typename CoordinateType, typename PriorityType>
void Grid<CoordinateType, PriorityType>::Initialize(CoordinateType width, CoordinateType height)
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

/// \brief Precomputes all neighbors and cost
template <typename CoordinateType, typename PriorityType>
void Grid<CoordinateType, PriorityType>::Precompute(void)
{
    int nodeCount = m_width * m_height;
    for(int nNode = 0; nNode < nodeCount; ++nNode)
    {
        TNode & current = m_grid[nNode];
        for (int nDir = 0; nDir < 4; nDir++)
        {
             int aX = current.X() + directions[nDir].dx;
             int aY = current.Y() + directions[nDir].dy;

             if((aX >= 0 && aX < m_width) && (aY >= 0 && aY < m_height))
             {
                 TNode * neighbor = &m_grid[aY * m_width + aX];
                 if(neighbor->IsPassable())
                 {
                     current.AddNeighbor(neighbor);
                 }
             }
         }

        // Small optimization for squared grid
        if ((current.X() + current.Y()) % 2 == 0)
        {
            current.ReverseNeighbors();
        }
    }
}

/// \brief  Puts into neighbors all direct neighbors of the given node
/// \param  current The node to check
/// \param  neighbors The vector where to store all neighbors
template <typename CoordinateType, typename PriorityType>
void Grid<CoordinateType, PriorityType>::GetNeighbors(const TNode & current, std::vector <TNode> & neighbors) const
{
    for (int nDir = 0; nDir < 4; nDir++)
    {
        int aX = current.X() + directions[nDir].dx;
        int aY = current.Y() + directions[nDir].dy;

        if((aX >= 0 && aX < m_width) && (aY >= 0 && aY < m_height))
        {
            const TNode & neighbour = GetNode(aX, aY);
            if(neighbour.IsPassable())
            {
                neighbors.push_back(neighbour);
            }
        }
    }

    // Small optimization for squared grid
    if ((current.X() + current.Y()) % 2 == 0)
    {
        std::reverse(neighbors.begin(), neighbors.end());
    }
}

/// \brief  Puts into neighbors all direct neighbors of the given node
/// \param  current The node to check
/// \param  neighbors The vector where to store all neighbors
template <typename CoordinateType, typename PriorityType>
void Grid<CoordinateType, PriorityType>::GetComputedNeighbors(const TNode & current, std::vector < TNode > & neighbors) const
{
    const std::vector < TNode * > & currentNeighbors = current.GetNeighbors();
    for(const TNode * node : currentNeighbors)
    {
        neighbors.push_back(*node);
    }
}

/// \brief  Returns a read only reference on a node
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
/// \return A reference on a node
template <typename CoordinateType, typename PriorityType>
inline const Node<CoordinateType, PriorityType> & Grid<CoordinateType, PriorityType>::GetNode(CoordinateType x, CoordinateType y) const
{
    return m_grid[y * m_width + x];
};

/// \brief  The node will be considered as a wall
/// \param  x The X coordinate of the node
/// \param  y The Y coordinate of the node
template <typename CoordinateType, typename PriorityType>
inline void Grid<CoordinateType, PriorityType>::SetNodeNonPassable(CoordinateType x, CoordinateType y)
{ m_grid[y * m_width + x].SetPassable(false); }