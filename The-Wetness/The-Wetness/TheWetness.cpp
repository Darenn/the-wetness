#include "PuzzleGenerator.hpp"
#include <vector>
#include "ASCIITest.hpp"

using namespace std;

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}



int main()
{
	PuzzleGenerator pg;
	pg.generateNextPuzzle();
	TestAscii();
    return 0;
}