#include <cassert>
#include <cmath>

#include "Generation/Grid/Grid.hpp"

#include "Engine/AI/Navigation/SquareGrid.hpp"
#include "Engine/AI/Navigation/Pathfinding.hpp"

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
	m_nodesLinks[getLinkIndex(coord, neighborDirection)] = linked;
	if (hasNeighbor(coord, neighborDirection)) {
		Coordinates Neighbor = getNeighbor(coord, neighborDirection);
		size_t linkIndex = getLinkIndex(Neighbor, getInverseDirection(neighborDirection));
		m_nodesLinks[linkIndex] = linked;
	}
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

std::vector<Grid::Coordinates> Grid::getValidPath(Coordinates start, Coordinates end) const
{
	// alias helpers
	using CoordinateType = char;
	using PriorityType   = short;

	using TNode       = AI::Node<CoordinateType, PriorityType>;
	using TSquareGrid = AI::SquareGrid <CoordinateType, PriorityType>;
	
	TSquareGrid squareGrid;

	squareGrid.Initialize(_width, _height);

	// Fill the grid with links
	for (unsigned char x = 0; x < _width; x++)
	{
		for (unsigned char y = 0; y < _height; y++)
		{
			Coordinates coord{ x, y };
			unsigned char linkedToEast = isLinkedWithNeighbor(coord, Direction::EAST) ? TNode::EMask::EAST : 0;
			unsigned char linkedToWest = isLinkedWithNeighbor(coord, Direction::WEST) ? TNode::EMask::WEST : 0;
			unsigned char linkedToNorth = isLinkedWithNeighbor(coord, Direction::NORTH) ? TNode::EMask::NORTH : 0;
			unsigned char linkedToSouth = isLinkedWithNeighbor(coord, Direction::SOUTH) ? TNode::EMask::SOUTH : 0;
			squareGrid.SetNodeMask(x, y, linkedToEast | linkedToWest | linkedToSouth | linkedToNorth);
		}
	}

	// Checks to avoid useless calculations
	// check that there is a path between start and end 
	std::vector <TNode> pathTest;
	bool hasPath = AI::Pathfinding<TSquareGrid, CoordinateType, PriorityType>::GetPath(squareGrid, pathTest, 
		squareGrid.GetNode(start.x, start.y), 
		squareGrid.GetNode(end.x,   end.y));
	if (!hasPath) return std::vector<Grid::Coordinates>();
	// Check that there is a path between start and all must pass
	vector<Coordinates> mustPassNodes = getDatas(Data::MUST_PASS);
	for each (Coordinates coord in mustPassNodes)
	{
		if (!AI::Pathfinding<TSquareGrid, CoordinateType, PriorityType>::GetPath(squareGrid, pathTest,
			squareGrid.GetNode(coord.x, coord.y),
			squareGrid.GetNode(start.x, start.y)))
			return std::vector<Grid::Coordinates>();
	}
	
	// search a possible path passing by all must_pass in all possible orders
	std::sort(mustPassNodes.begin(), mustPassNodes.end());
	do {
		Coordinates prevNode = start;		
		std::vector <TNode> finalPath = { squareGrid.GetNode(prevNode.x, prevNode.y) };
		bool noValidPath = false;
		TSquareGrid squareGridCopy = TSquareGrid(squareGrid);
		// Add to finalPath the path to go on the ith must pass
		for (size_t i = 0; i < mustPassNodes.size(); i++)
		{
			Coordinates node = mustPassNodes[i];
			std::vector <TNode> path;
			bool hasPath = AI::Pathfinding<TSquareGrid, CoordinateType, PriorityType>::GetPath(squareGridCopy, path,
				squareGridCopy.GetNode(prevNode.x, prevNode.y),
				squareGridCopy.GetNode(node.x, node.y));

			if (!hasPath)
			{
				noValidPath = true;
				break;
			}
			std::reverse(path.begin(), path.end()); // The given path is reversed
			finalPath.insert(finalPath.end(), path.begin() + 1, path.end());
			prevNode = node;

			// Update the grid by removing links from the nodes from path (but the last) to avoid repetition
			for (size_t i = 0; i < finalPath.size() - 1; i++) {
				TNode node = finalPath[i];
				squareGridCopy.SetNodeMask(node.X(), node.Y(), TNode::NONE);
			}
		}
		// Handle the path to the exit
		Coordinates node = end;
		std::vector <TNode> path;
		bool hasPath = AI::Pathfinding<TSquareGrid, CoordinateType, PriorityType>::GetPath(squareGridCopy, path,
			squareGridCopy.GetNode(prevNode.x, prevNode.y),
			squareGridCopy.GetNode(node.x, node.y));
		if (hasPath) {
			std::reverse(path.begin(), path.end()); // The given path is reversed
			finalPath.insert(finalPath.end(), path.begin() + 1, path.end());
		}
		else noValidPath = true;

		if (!noValidPath) {
			std::vector<Grid::Coordinates> coordinatesPath;
			for each (TNode node in finalPath)
			{
				coordinatesPath.push_back(Grid::Coordinates{ static_cast<unsigned char>(node.X()), static_cast<unsigned char>(node.Y()) });
			}
			return coordinatesPath;
		}
			
	} while (std::next_permutation(mustPassNodes.begin(), mustPassNodes.end()));

	return std::vector<Grid::Coordinates>();
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

std::vector<Grid::Coordinates> Grid::getDatas(Data d) const
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
	for (size_t i = 0; i < grid._height; i++)
	{
		for (size_t j = 0; j < grid._width; j++)
		{
			Grid::Coordinates node{ j, i };
			output << static_cast<char>(grid.getData(node));
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::EAST))
				output << "==";
			else
				output << "  ";
		}
		output << std::endl;
		for (size_t j = 0; j < grid._width; j++)
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
