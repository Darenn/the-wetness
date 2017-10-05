#include "Grid.hpp"
#include <cassert>
#include "Node.hpp"

using namespace std;


Grid::Grid(int width, int height) : _width(width), _height(height)
{
	// Create the nodes
	size_t nodeCount = width * height;
	m_nodesData = vector<Data>(nodeCount, Grid::Data::NOTHING);
	m_nodesLinks = vector<bool>(NEIGHBORS_COUNT * nodeCount, false);
}

Grid::~Grid()
{
}

Grid::Data Grid::getData(Coordinates coord) const
{
	return m_nodesData.at(coordToGridIndex(coord));
}

Grid::Data Grid::getData(int number) const
{
	return m_nodesData[number];
}

void Grid::setData(Coordinates coord, Data d)
{
	m_nodesData[coordToGridIndex(coord)] = d;
}

void Grid::setData(int number, Data d)
{
	m_nodesData[number] = d;
}

bool Grid::isLinkedWithNeighbor(Coordinates coord, Direction neighborDirection) const
{
	return m_nodesLinks[getLinkIndex(coord, neighborDirection)];
}

bool Grid::isLinkedWithNeighbor(size_t gridIndex, Direction neighborDirection) const
{
	return isLinkedWithNeighbor(gridIndexToCoord(gridIndex), neighborDirection);
}

void Grid::setLinkWithNeighbor(int gridIndex, Direction neighborDirection, bool linked)
{
	setLinkWithNeighbor(gridIndexToCoord(gridIndex), neighborDirection, linked);
}

void Grid::setLinkWithNeighbor(Coordinates coord, Direction neighborDirection, bool linked)
{
	assert(hasNeighbor(coord, neighborDirection));
	m_nodesLinks[getLinkIndex(coord, neighborDirection)] = linked;
	Coordinates Neighbor = getNeighbor(coord, neighborDirection);
	size_t linkIndex = getLinkIndex(Neighbor, getInverseDirection(neighborDirection));
	m_nodesLinks[linkIndex] = linked;
}

std::vector<Grid::Coordinates> Grid::getLinkedNeighbors(Coordinates coord) const
{
	std::vector<Coordinates> neighbors;
	if (isLinkedWithNeighbor(coord, Direction::NORTH)) neighbors.push_back(getNeighbor(coord, Direction::NORTH));
	if (isLinkedWithNeighbor(coord, Direction::EAST)) neighbors.push_back(getNeighbor(coord, Direction::EAST));
	if (isLinkedWithNeighbor(coord, Direction::SOUTH)) neighbors.push_back(getNeighbor(coord, Direction::SOUTH));
	if (isLinkedWithNeighbor(coord, Direction::WEST)) neighbors.push_back(getNeighbor(coord, Direction::WEST));
	return neighbors;
}

size_t Grid::getNodeCount() const
{
	return _width * _height;
}

unsigned Grid::getDataCount(Data d) const
{
	unsigned int dataCount = 0;
	for (int i = 0; i < m_nodesData.size(); ++i)
	{
		if (m_nodesData[i] == d)
			dataCount++;
	}
	return dataCount;
}

Grid::Coordinates Grid::getNeighbor(Coordinates coord, Direction neighborDirection)
{
	switch (neighborDirection)
	{
	case Direction::NORTH:
		return Coordinates{coord.x, coord.y - 1};
	case Direction::EAST:
		return Coordinates{coord.x + 1, coord.y};
	case Direction::SOUTH:
		return Coordinates{coord.x, coord.y + 1};
	case Direction::WEST:
		return Coordinates{coord.x - 1, coord.y};
	}
}

bool Grid::hasNeighbor(int gridIndex, Direction neighborDirection) const
{
	return hasNeighbor(gridIndexToCoord(gridIndex), neighborDirection);
}


bool Grid::hasNeighbor(Coordinates coord, Direction neighborDirection) const
{
	switch (neighborDirection)
	{
	case Direction::NORTH:
		return coord.y > 0;
	case Direction::EAST:
		return coord.x + 1 < _width;
	case Direction::SOUTH:
		return coord.y + 1 < _height;
	case Direction::WEST:
		return coord.x > 0;
	default:
		throw std::out_of_range("No direction.");
	}
}

size_t Grid::getWidth() const
{
	return _width;
}

size_t Grid::getHeight() const
{
	return _height;
}

size_t Grid::coordToGridIndex(Grid::Coordinates coord) const
{
	return (coord.x * _width + coord.y);
}

Grid::Coordinates Grid::gridIndexToCoord(size_t gridIndex) const
{
	return Coordinates{gridIndex % _width, gridIndex / _width};
}

size_t Grid::getLinkIndex(Coordinates coord, Direction neighborDirection) const
{
	size_t linkIndex = coordToGridIndex(coord);
	switch (neighborDirection)
	{
	case Direction::NORTH:
		break;
	case Direction::EAST:
		linkIndex += 1;
		break;
	case Direction::SOUTH:
		linkIndex += 2;
		break;
	case Direction::WEST:
		linkIndex += 3;
	}
	return linkIndex;
}

size_t Grid::getLinkIndex(size_t gridIndex, Direction neighborDirection) const
{
	size_t linkIndex = gridIndex;
	switch (neighborDirection)
	{
	case Direction::NORTH:
		break;
	case Direction::EAST:
		linkIndex += 1;
		break;
	case Direction::SOUTH:
		linkIndex += 2;
		break;
	case Direction::WEST:
		linkIndex += 3;
	}
	return linkIndex;
}

Grid::Direction Grid::getInverseDirection(Direction d)
{
	switch (d)
	{
	case Direction::NORTH:
		return Direction::SOUTH;
	case Direction::EAST:
		return Direction::WEST;
	case Direction::SOUTH:
		return Direction::NORTH;
	case Direction::WEST:
		return Direction::EAST;
	default:
		throw std::out_of_range("No direction corresponds.");
	}
}


std::vector<std::vector<Grid::Coordinates>> Grid::getPaths(Coordinates start, Coordinates end) const
{
	std::vector<std::vector<Coordinates>> paths;
	vector<vector<Coordinates>> toCheck;
	vector<vector<Coordinates>> nextToCheck;
	vector<Coordinates> firstPath;

	firstPath.push_back(start);
	toCheck.push_back(firstPath);

	while (toCheck.size() > 0)
	{
		for (vector<Coordinates> path : toCheck)
		{
			Coordinates lastNode = path.back();

			// If the last node is the end, add it to paths and continue with the next path
			if (lastNode == end)
			{
				paths.push_back(path);
				continue;
			}

			// Get the neighbors, remove the nodes already visited and create new paths
			vector<Coordinates> neighbors = getLinkedNeighbors(lastNode);
			for (std::vector<Coordinates>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
			{
				if (std::find(path.begin(), path.end(), *it) == path.end())
				{
					// Add new path to check next with the new neighbor
					vector<Coordinates> newPath(path);
					newPath.push_back(*it);
					nextToCheck.push_back(newPath);
				}
			}
		}

		// Clear toCheck and add to it the new paths to check
		toCheck.clear();
		toCheck.insert(toCheck.begin(), nextToCheck.begin(), nextToCheck.end());
		nextToCheck.clear();
	}
	
	return paths;
}

std::ostream & operator<<(std::ostream& output, const Grid& grid)
{
	for (size_t i = 0; i < grid._width; i++)
	{
		for (size_t j = 0; j < grid._height; j++)
		{
			Grid::Coordinates node{ i, j };
			output << static_cast<char>(grid.getData(node));
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::EAST))
				output << "==";
			else
				output << "  ";
		}
		output << std::endl;
		for (size_t j = 0; j < grid._height; j++)
		{
			Grid::Coordinates node{ i, j };
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::SOUTH))
				output << "|  ";
			else
				output << "   ";
		}
		output << std::endl;
	}
	return output;
}
