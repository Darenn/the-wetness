#pragma once
#include "Node.hpp"
#include <list>
#include <vector>
#include <hash_set>
#include <math.h>

class Graph
{
public:
	Graph(unsigned char width, unsigned char height) : m_nodes(), m_width(width), m_height(height)
	{
		m_nodes.reserve(height);
		for (auto nodes : m_nodes) nodes.reserve(width);
	}

	Node& getNode(Vector2uc position)
	{
		return m_nodes[position.x][position.y];
	}

	void getNeighbors(Vector2uc position, std::vector<Node*>& neighbors)
	{
		if (position.x - 1 >= 0) neighbors.push_back(&m_nodes[position.x - 1][position.y]);
		if (position.x + 1 < m_width) neighbors.push_back(&m_nodes[position.x + 1][position.y]);
		if (position.y - 1 >= 0) neighbors.push_back(&m_nodes[position.x][position.y - 1]);
		if (position.y + 1 < m_height) neighbors.push_back(&m_nodes[position.x][position.y + 1]);
	}

	std::vector<Node> getPath(Vector2uc start, Vector2uc end)
	{
		std::hash_set<Node*> closed;
		std::list<Node*> open;
		open.push_back(&getNode(start));

		while (open.size() > 0)
		{
			Node* current = open.front();
			open.pop_front();
			closed.insert(current);

			if (current->position == end)
			{
				// return path
			}

			std::vector<Node*> neighbors;
			getNeighbors(current->position, neighbors);
			for(Node* pneighbor : neighbors)
			{
				if (!pneighbor->isTraversable || std::find(closed.begin(), closed.end(), pneighbor) != closed.end())
				{
					continue;
				}

				unsigned short newCostToNeighbor = current->g_cost + getDistance(current->position, pneighbor->position);
				bool openContainsNeighbor = std::find(open.begin(), open.end(), pneighbor) != open.end();
				if (newCostToNeighbor < pneighbor->g_cost || !openContainsNeighbor)
				{
					pneighbor->g_cost = newCostToNeighbor;
					pneighbor->h_cost = getDistance(pneighbor->position, end);
					pneighbor->parent = pneighbor;

					if (!openContainsNeighbor)
					{
						open.push_back(pneighbor);
					}
				}
			}
		}
	}

private:
	std::vector<std::vector<Node>> m_nodes;
	unsigned char m_width;
	unsigned char m_height;

	unsigned short getDistance(Vector2uc u, Vector2uc v)
	{
		unsigned short distX = abs(u.x - v.x);
		unsigned short distY = abs(u.y - v.y);
		return distX + distY;
	}
};
