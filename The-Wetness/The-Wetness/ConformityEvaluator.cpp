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
	// Check that there are only one entry and one exit
	if (grid.getNumData(Node::Data::EXIT) != 1) return false;
	if (grid.getNumData(Node::Data::START) != 1) return false;

	// Check that there is a possible path

	return true;
}

void ConformityEvaluator::fixGrid(Grid & grid) const
{
	// Take entries and exits and make them into nothing if there are too much
	int numExits = grid.getNumData(Node::Data::EXIT);
	int numEntries = grid.getNumData(Node::Data::START);
	if (numExits > 1) {
		std::vector<Node*> exits;
		for (Node& node : grid.getNodes())
			if (node.data == Node::Data::EXIT)
			{
				exits.push_back(&node);
				node.data = Node::Data::NOTHING;
			}
		exits.at(rand() % exits.size())->data = Node::Data::EXIT;
	}
	if (numEntries > 1) {
		std::vector<Node*> entries;
		for (Node& node : grid.getNodes())
			if (node.data == Node::Data::START)
			{
				entries.push_back(&node);
				node.data = Node::Data::NOTHING;
			}
		entries.at(rand() % entries.size())->data = Node::Data::START;
	}
	
	/// If they are'nt any entry or exit, create ones
	if (numExits == 0) {
		grid.getNodes().at(rand() % grid.getNodes().size()).data = Node::Data::EXIT;
	}
	if (numEntries == 0) {
		grid.getNodes().at(rand() % grid.getNodes().size()).data = Node::Data::START;
	}
}

