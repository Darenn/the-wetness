#include "FitnessEvaluator.hpp"


FitnessEvaluator::FitnessEvaluator()
{
}


FitnessEvaluator::~FitnessEvaluator()
{
}

int FitnessEvaluator::evaluate(Grid& grid) const
{
	int numMustPass = grid.getDataCount(Grid::Data::MUST_PASS);
	//Node* start = grid.getStart();
	//Node* exit = grid.getExit();
	/*if (start == nullptr || exit == nullptr)
	{
		return -1000;
	}
	if (grid.getPaths(start, exit).size() == 0)
		return -2000;*/
	//int size = grid.getWidth() * grid.getHeight();
	return numMustPass;
}
