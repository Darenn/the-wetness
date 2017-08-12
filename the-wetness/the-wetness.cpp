#include "Grid.h"
#include <iostream>
#include "GridEncoder.h"
#include <iterator>

using namespace std;

void display_vector(const vector<bool> &v)
{
	std::copy(v.begin(), v.end(),
		ostream_iterator<bool>(std::cout, " "));
}

int main()
{
	Grid grid(4, 4);
	GridEncoder ge{};
	display_vector(ge.encode(grid));
    return 0;
}



