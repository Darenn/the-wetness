#include "Grid.h"
#include <iostream>
#include "GridEncoder.h"
#include <iterator>
#include "GridDecoder.h"

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

	vector<bool> encodedGrid = ge.encode(grid);
	cout << "Grid :" << std::endl << grid << std::endl;
	cout << "Encoded grid : " << std::endl;
	display_vector(encodedGrid);
	GridDecoder gd{};
	Grid decodedGrid = gd.decode(encodedGrid);
	cout << std::endl << "Decoded grid : " << std::endl << decodedGrid;
    return 0;
}



