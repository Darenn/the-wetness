/// \file       GridDisplayer.hpp
/// \date       05/10/2017
/// \package    Test
/// \author     Vincent STEHLY--CALISTO

#ifndef _GRID_DISPLAYER_HPP
#define _GRID_DISPLAYER_HPP

#include <vector>
#include <sstream>
#include "Grid.hpp"
#include "Window.hpp"

/// \class  GridDisplayer
/// \brief  Utility class for test 
class GridDisplayer
{
public:

	GridDisplayer (void);
	void Update   (float dt);
	void Render   (Window & window);

private:

	Grid	grid;
};

#endif // _GRID_DISPLAYER_HPP
