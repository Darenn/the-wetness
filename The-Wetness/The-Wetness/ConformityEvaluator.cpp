#include "ConformityEvaluator.hpp"


ConformityEvaluator::ConformityEvaluator()
{
}


ConformityEvaluator::~ConformityEvaluator()
{
}

bool ConformityEvaluator::evaluate(Grid& grid)
{
	// Check that there are only one entry and one exit
	if (grid.getNumData(Node::Data::EXIT) != 1) return false;
	if (grid.getNumData(Node::Data::START) != 1) return false;

	// Check that there is a possible path

	return true;
}
