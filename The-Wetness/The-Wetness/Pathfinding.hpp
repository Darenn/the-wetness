/// \file       Pathfinding.hpp
/// \date       18/10/2017
/// \package    Pathfinding
/// \author     Vincent STEHLY--CALISTO

#ifndef _PATHFINDING_HPP
#define _PATHFINDING_HPP

#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "Node.hpp"

/// \namespace AI
namespace AI
{

/// \brief Computes the manhattan distance between two nodes
template<typename CoordinateType, typename PriorityType>
/* inline */ PriorityType Heuristic(const Node<CoordinateType, PriorityType> &lhs,
                                    const Node<CoordinateType, PriorityType> &rhs)
{
    return abs(lhs.X() - rhs.X()) + abs(lhs.Y() - rhs.Y());
}

/// \class  Pathfinding
/// \brief  Helper class to compute the shortest path between two points
/// \tparam Graph The graph class
/// \tparam CoordinateType The type of coordinates
/// \tparam PriorityType The type of the priority
template<typename Graph, typename CoordinateType, typename PriorityType>
class Pathfinding
{
public:

    typedef Node        <CoordinateType, PriorityType> TNode;
    typedef NodeHash    <CoordinateType, PriorityType> TNodeHash;
    typedef NodeCompare <CoordinateType, PriorityType> TNodeCompare;

    /// \brief  Finds one of the shortest path between start and end node.
    /// \param  graph The graph to perform the search on
    /// \param  path The vector to store the result (in reverse order)
    /// \param  start The start node
    /// \param  end The end node
    static void GetPath(const Graph & graph, std::vector<TNode> & path, const TNode & start, const TNode & end)
    {
        std::vector         <TNode> neighbors;
        std::priority_queue <TNode> frontier;
        std::unordered_map  <TNode, TNode,        TNodeHash, TNodeCompare> cameFrom;
        std::unordered_map  <TNode, PriorityType, TNodeHash, TNodeCompare> costSoFar;

        frontier.emplace (TNode(start));
        costSoFar.emplace(TNode(start), 0);
        cameFrom.emplace (TNode(start), start);

        while (!frontier.empty())
        {
            TNode current(frontier.top());
            frontier.pop();

            // Early exit, the pathfinding has found
            // the exit for the first time
            if (current == end)
            {
                break;
            }

            neighbors.clear();
            graph.GetNeighbors(current, neighbors);

            for (TNode & next : neighbors)
            {
                int new_cost = costSoFar[current];

                if (!costSoFar.count(next) || new_cost < costSoFar[next])
                {
                    costSoFar[next] = new_cost;
                    PriorityType priority = new_cost + Heuristic<CoordinateType, PriorityType>(next, end);

                    next.SetPriority(priority);
                    frontier.push(next);

                    cameFrom[next] = current;
                }
            }
        }

        TNode current = end;
        path.push_back(end);
        while (current != start)
        {
            current = cameFrom[current];
            path.push_back(current);
        }
    }
};

}
#endif // _PATHFINDING_HPP