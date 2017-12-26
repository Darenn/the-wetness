#include "Generation/GA/FitnessEvaluator.hpp"


FitnessEvaluator::FitnessEvaluator()
{
}


FitnessEvaluator::~FitnessEvaluator()
{
}

int FitnessEvaluator::evaluate(Grid& grid) const
{
	int numMustPass = grid.getDataCount(Grid::Data::MUST_PASS);
	std::vector<Grid::Coordinates> start = grid.getDatas(Grid::Data::START);
	std::vector<Grid::Coordinates> exit = grid.getDatas(Grid::Data::EXIT);
	int numberNodes = grid.getWidth() * grid.getHeight();
	if (start.size() == 0 || exit.size() == 0)
	{
		return -1000;
	}

	std::vector<Grid::Coordinates> path = grid.getValidPath(start[0], exit[0]);
	if (path.size() <= 0) {
		return -2000;
	}
	return numMustPass * 4 + path.size() * 1 + grid.getNumberUnlinks() * 4 + numberNodes * 1;
}
