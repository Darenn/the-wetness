#include "ConformityEvaluator.hpp"
#include "Grid.hpp"
#include "Node.hpp"


ConformityEvaluator::ConformityEvaluator()
{
}


ConformityEvaluator::~ConformityEvaluator()
{
}

bool ConformityEvaluator::evaluate(Grid& grid) const
{
	/*// Check that there are only one entry and one exit
	if (grid.getNumData(Node::Data::EXIT) != 1) return false;
	if (grid.getNumData(Node::Data::START) != 1) return false;

	// Check that there is a possible path
	*/
	return true;
}

void ConformityEvaluator::fixGrid(Grid & grid) const
{
	// Take entries and exits and make them into nothing if there are too much
	int numExits = grid.getDataCount(Grid::Data::EXIT);
	int numEntries = grid.getDataCount(Grid::Data::START);
	if (numExits > 1) {
		std::vector<Grid::Coordinates> exits;
		for (int x = 0; x < grid.getWidth(); ++x)
		{
			for (int y = 0; y < grid.getHeight(); ++y)
			{
				Grid::Coordinates node{ x, y };
				if (grid.getData(node) == Grid::Data::EXIT)
				{
					exits.push_back(node);
					grid.setData(node, Grid::Data::NOTHING);
				}
			}
		}
		Grid::Coordinates chosenExit = exits.at(rand() % exits.size());
		grid.setData(chosenExit, Grid::Data::EXIT);
	}
	if (numEntries > 1) {
		std::vector<Grid::Coordinates> entries;
		for (int x = 0; x < grid.getWidth(); ++x)
		{
			for (int y = 0; y < grid.getHeight(); ++y)
			{
				Grid::Coordinates node{ x, y };
				if (grid.getData(node) == Grid::Data::START)
				{
					entries.push_back(node);
					grid.setData(node, Grid::Data::NOTHING);
				}
			}
		}
		Grid::Coordinates chosenEntry= entries.at(rand() % entries.size());
		grid.setData(chosenEntry, Grid::Data::START);
	}
	
	/// If they are'nt any entry or exit, create ones
	if (numExits == 0) {
		size_t randomIndex = rand() % grid.getNodeCount();
		grid.setData(randomIndex, Grid::Data::EXIT);
	}
	if (numEntries == 0) {
		size_t randomIndex = rand() % grid.getNodeCount();
		grid.setData(randomIndex, Grid::Data::START);
	}
}

