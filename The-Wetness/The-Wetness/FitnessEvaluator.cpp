#include "FitnessEvaluator.hpp"


FitnessEvaluator::FitnessEvaluator()
{
}


FitnessEvaluator::~FitnessEvaluator()
{
}

int FitnessEvaluator::evaluate(Grid& grid) const
{
	int numMustPass = grid.getNumData(Node::Data::MUST_PASS);
	//int size = grid.getWidth() * grid.getHeight();
	return numMustPass;
}
