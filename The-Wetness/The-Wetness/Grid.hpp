#pragma once

#include <vector>
#include <iostream>
#include <exception>

class Grid
{
public:
	struct Coordinates
	{
		unsigned char x;
		unsigned char y;
		friend bool operator==(const Coordinates& l, const Coordinates& r)
		{
			return l.x == r.x && l.y == r.y;
		}

		friend bool operator<(const Coordinates& l, const Coordinates& r)
		{
			return l.x < r.x && l.y < r.y;
		}
	};

	enum Data { NOTHING = '#', START = 'S', EXIT = 'E', MUST_PASS = 'X' };
	enum Direction {NORTH, EAST, SOUTH, WEST};

	const size_t NEIGHBORS_COUNT = 4;

	Grid(int width, int height);
	~Grid();


	Data getData(Coordinates coord) const;
	Data getData(int number) const;
	void setData(Coordinates coord, Data d);
	void setData(int number, Data d);
	inline bool Grid::isLinkedWithNeighbor(Coordinates coord, Direction neighborDirection) const
	{
		if (!hasNeighbor(coord, neighborDirection)) return false;
		return m_nodesLinks[getLinkIndex(coord, neighborDirection)];
	}
	bool isLinkedWithNeighbor(size_t gridIndex, Direction neighborDirection) const;
	void setLinkWithNeighbor(int gridIndex, Direction neighborDirection, bool linked);
	void setLinkWithNeighbor(Coordinates coord, Direction neighborDirection, bool linked);
	std::vector<Coordinates> getLinkedNeighbors(Coordinates coord) const;
	void getLinkedNeighbors(Coordinates coord, std::vector<Coordinates>& neighbors) const;
	size_t getNodeCount() const;
	unsigned int getDataCount(Data d) const;
	static Coordinates getNeighbor(Coordinates coord, Direction neighborDirection);
	bool hasNeighbor(int gridIndex, Direction neighborDirection) const;
	bool hasNeighbor(Coordinates coord, Direction neighborDirection) const;
	size_t getWidth() const;
	size_t getHeight() const;
	bool hasValidPath(Coordinates start, Coordinates end) const;
	std::vector<std::vector<Coordinates>> getWinningPaths(const std::vector<std::vector<Coordinates>>&) const;
	bool isWinningPath(const std::vector<Coordinates>&) const;
	std::vector<Coordinates> getDatas(Data d) const;

	void setLinkToAllNeighbors(Coordinates coord, bool linked);

	void setLinkToAllNeighbors(int gridIndex, bool linked);

	friend std::ostream &operator<<(std::ostream &output, const Grid &D);

	Grid& operator=(const Grid& grid);

private:
	/// <summary>
	/// Contains each data for each node of the grid.
	/// The first data correspond to the top left node, the second to the top left + 1
	/// </summary>
	std::vector<Data> m_nodesData;

	/// <summary>
	///	Contains links between nodes.
	/// The four first bools correspond to the links of the top left node.
	/// Each bool correspond to the link with the neihbor on one direction.
	/// Order : NESW
	/// </summary>
	std::vector<bool> m_nodesLinks;
	size_t _width;
	size_t _height;
	size_t m_numMustPass;

	size_t coordToGridIndex(Grid::Coordinates coord) const;
	Coordinates gridIndexToCoord(size_t gridIndex) const;
	size_t getLinkIndex(Coordinates coord, Direction neighborDirection) const;
	size_t getLinkIndex(size_t gridIndex, Direction neighborDirection) const;

	static Direction getInverseDirection(Direction d);
};


