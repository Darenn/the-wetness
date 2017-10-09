/// \file       Test.hpp
/// \date       04/10/2017
/// \package    Test
/// \author     Vincent STEHLY--CALISTO

#ifndef _TEST_HPP
#define _TEST_HPP

#include <vector>
#include "Grid.hpp"
#include "Window.hpp"

/// \class  Test
/// \brief  Utility class for test 
class Test
{
public:

	Test         (void);
	void Update  (float dt, Window & w);
	void TestGA  (void);

private:

	Grid grid;
	float speed;
	float posX;
	int step;
};

#endif // _TEST_HPP
