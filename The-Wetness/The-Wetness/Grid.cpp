#include "Grid.hpp"
#include <cassert>

using namespace std;


Grid::Grid(int width, int height) : _width(width), _height(height)
{
	// Create the nodes
	size_t nodeCount = width * height;
	m_nodesData = vector<Data>(nodeCount, Grid::Data::NOTHING);
	m_nodesLinks = vector<bool>(NEIGHBORS_COUNT * nodeCount, false);
	for (size_t i = 0; i < nodeCount; i++)
	{
		setLinkToAllNeighbors(i, true);
	}
}

Grid::~Grid()
{
}

Grid::Data Grid::getData(Coordinates coord) const
{
	return m_nodesData[coordToGridIndex(coord)];
}

Grid::Data Grid::getData(int number) const
{
	return m_nodesData[number];
}

void Grid::setData(Coordinates coord, Data d)
{
	if (d == Data::MUST_PASS) m_numMustPass++;
	if (getData(coord) == Data::MUST_PASS) m_numMustPass--;
	m_nodesData[coordToGridIndex(coord)] = d;
}

void Grid::setData(int number, Data d)
{
	if (d == Data::MUST_PASS) m_numMustPass++;
	if (getData(number) == Data::MUST_PASS) m_numMustPass--;
	m_nodesData[number] = d;
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

void Grid::getLinkedNeighbors(Coordinates coord, std::vector<Coordinates>& neighbors) const
{
	if (isLinkedWithNeighbor(coord, Direction::NORTH)) neighbors.push_back(getNeighbor(coord, Direction::NORTH));
	if (isLinkedWithNeighbor(coord, Direction::EAST)) neighbors.push_back(getNeighbor(coord, Direction::EAST));
	if (isLinkedWithNeighbor(coord, Direction::SOUTH)) neighbors.push_back(getNeighbor(coord, Direction::SOUTH));
	if (isLinkedWithNeighbor(coord, Direction::WEST)) neighbors.push_back(getNeighbor(coord, Direction::WEST));
}

size_t Grid::getNodeCount() const
{
	return _width * _height;
}

unsigned int Grid::getDataCount(Data d) const
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
		return Coordinates{static_cast<unsigned char>(coord.x), static_cast<unsigned char>(coord.y - 1) };
	case Direction::EAST:
		return Coordinates{static_cast<unsigned char>(coord.x + 1), static_cast<unsigned char>(coord.y) };
	case Direction::SOUTH:
		return Coordinates{static_cast<unsigned char>(coord.x), static_cast<unsigned char>(coord.y + 1) };
	case Direction::WEST:
		return Coordinates{static_cast<unsigned char>(coord.x - 1), static_cast<unsigned char>(coord.y) };
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
	return (coord.y * _width + coord.x);
}

Grid::Coordinates Grid::gridIndexToCoord(size_t gridIndex) const
{
	return Coordinates{static_cast<unsigned char>(gridIndex % _width), static_cast<unsigned char>(gridIndex / _width)};
}

size_t Grid::getLinkIndex(Coordinates coord, Direction neighborDirection) const
{
	return getLinkIndex(coordToGridIndex(coord), neighborDirection);
}

size_t Grid::getLinkIndex(size_t gridIndex, Direction neighborDirection) const
{
	size_t linkIndex = gridIndex * 4;
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
	auto* pToCheck = new vector<vector<Coordinates>>();
	pToCheck->reserve(m_nodesData.size() * m_nodesData.size() * 4);
	auto* pNextToCheck = new vector<vector<Coordinates>>();
	pNextToCheck->reserve(m_nodesData.size() * m_nodesData.size() * 4);
	vector<Coordinates> firstPath;
	vector<Coordinates> neighbors;
	vector<Coordinates> newPath;
	neighbors.reserve(4);

	firstPath.push_back(start);
	pToCheck->push_back(firstPath);

	while (pToCheck->size() > 0)
	{
		for (vector<Coordinates>& path : *pToCheck)
		{
			Coordinates lastNode = path.back();

			// If the last node is the end, add it to paths and continue with the next path
			if (lastNode == end)
			{
				bool isWinning = isWinningPath(path) > 0;
				paths.push_back(std::move(path));
				 /*if (isWinning) return paths;*/
				continue;
			}

			// Get the neighbors and create new paths with them
			getLinkedNeighbors(lastNode, neighbors);
			for (std::vector<Coordinates>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
			{
				if (std::find(path.begin(), path.end(), *it) == path.end())
				{
					// Add new path to check next with the new neighbor
					newPath.insert(newPath.begin(), path.begin(), path.end());
					newPath.push_back(*it);
					pNextToCheck->push_back(newPath);
					newPath.clear();
				}
			}
			neighbors.clear();
		}
		// Clear toCheck and add to it the new paths to check
		assert(pNextToCheck->size() <= pToCheck->size() * 4);
		pToCheck->clear();
		auto* temp = pToCheck;
		pToCheck = pNextToCheck;
		pNextToCheck = temp;
	}
	delete pToCheck;
	delete pNextToCheck;
	return paths;
}

std::vector<std::vector<Grid::Coordinates>> Grid::getWinningPaths(const std::vector<std::vector<Coordinates>>& pathsToExit) const
{
	std::vector<std::vector<Grid::Coordinates>> winningPaths;
	int numMustPassInGrid = getDataCount(Grid::Data::MUST_PASS); // TODO optimiza by putting in member
	for (const auto& path : pathsToExit) {
		int numMustPassInPath = 0;
		for (const auto& node : path) {
			if (getData(node) == Grid::Data::MUST_PASS) {
				numMustPassInPath++;
			}
		}
		if (numMustPassInPath == numMustPassInGrid) {
			winningPaths.push_back(path);
		}
	}
	return winningPaths;
}

bool Grid::isWinningPath(const std::vector<Coordinates>& path) const
{
	int numMustPassInGrid = m_numMustPass;
	int numMustPassInPath = 0;
	for (const auto& node : path) {
		if (getData(node) == Grid::Data::MUST_PASS) {
			numMustPassInPath++;
		}
	}
	if (numMustPassInPath == numMustPassInGrid) {
		return true;
	}
	return false;
}

std::vector<Grid::Coordinates> Grid::getDatas(Data d)
{
	std::vector<Coordinates> datas;
	for (size_t i = 0; i < m_nodesData.size(); i++)
		if (m_nodesData[i] == d)
			datas.push_back(gridIndexToCoord(i));
	return datas;
}

void Grid::setLinkToAllNeighbors(Coordinates coord, bool linked)
{
	if (hasNeighbor(coord, Direction::EAST))
	{
		setLinkWithNeighbor(coord, Direction::EAST, linked);
	}
	if (hasNeighbor(coord, Direction::SOUTH))
	{
		setLinkWithNeighbor(coord, Direction::SOUTH, linked);
	}
	if (hasNeighbor(coord, Direction::NORTH))
	{
		setLinkWithNeighbor(coord, Direction::NORTH, linked);
	}
	if (hasNeighbor(coord, Direction::WEST))
	{
		setLinkWithNeighbor(coord, Direction::WEST, linked);
	}
}

void Grid::setLinkToAllNeighbors(int gridIndex, bool linked)
{
	setLinkToAllNeighbors(gridIndexToCoord(gridIndex), linked);
}

Grid& Grid::operator=(const Grid& grid)
{
	m_nodesData = grid.m_nodesData;
	m_nodesLinks = grid.m_nodesLinks;
	_width = grid._width;
	_height = grid._height;
	return *this;
}

std::ostream & operator<<(std::ostream& output, const Grid& grid)
{
	for (size_t i = 0; i < grid._width; i++)
	{
		for (size_t j = 0; j < grid._height; j++)
		{
			Grid::Coordinates node{ j, i };
			output << static_cast<char>(grid.getData(node));
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::EAST))
				output << "==";
			else
				output << "  ";
		}
		output << std::endl;
		for (size_t j = 0; j < grid._height; j++)
		{
			Grid::Coordinates node{ j, i };
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::SOUTH))
				output << "|  ";
			else
				output << "   ";
		}
		output << std::endl;
	}
	return output;
}
