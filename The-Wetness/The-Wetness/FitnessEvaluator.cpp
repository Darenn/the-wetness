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
	std::vector<Grid::Coordinates> start = grid.getDatas(Grid::Data::START);
	std::vector<Grid::Coordinates> exit = grid.getDatas(Grid::Data::EXIT);
	if (start.size() == 0 || exit.size() == 0)
	{
		return -1000;
	}
	std::vector<std::vector<Grid::Coordinates>> paths = grid.getPaths(start[0], exit[0]);
	/*for (std::vector<Grid::Coordinates> p : paths) {
		std::cout << "[ ";
			for (auto node : p) {
				std::cout << "{" << node.x << ", " << node.y << "}";
			}
			std::cout << "]" << std::endl;
	}
	//std::cout << grid << std::endl;*/
	int nbPath = paths.size();
	if (nbPath == 0)
		return -1000;
	return nbPath;
}
