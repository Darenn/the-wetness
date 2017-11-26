/// \file       GameState.cpp
/// \date       25/11/2017
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "Engine/Engine.hpp"
#include "Game/State/GameState.hpp"
#include "Generation/PuzzleGenerator.hpp"

#include <sstream>
#include <fstream>

std::string GameState::GetStringGrid(Grid const& grid) const
{
	std::string formatedGrid = "";
	for (size_t i = 0; i < grid.getWidth(); i++)
	{
		for (size_t j = 0; j < grid.getHeight(); j++)
		{
			Grid::Coordinates node{ j, i };
			formatedGrid += static_cast<char>(grid.getData(node));
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::EAST))
			{
				formatedGrid += '=';
			}
			else
			{
				formatedGrid += ' ';
			}
		}
		formatedGrid += '\n';
		for (size_t j = 0; j < grid.getHeight(); j++)
		{
			Grid::Coordinates node{ j, i };
			if (grid.isLinkedWithNeighbor(node, Grid::Direction::SOUTH))
			{
				formatedGrid += "| ";
			}
			else
			{
				formatedGrid += "  ";
			}
		}
		formatedGrid += '\n';
	}

	return formatedGrid;
}

/// \brief	Destructor
/* virtual */ GameState::~GameState(void)
{
	// None
}

/// \brief	Called when the state is pushed
/* virtual */ void GameState::OnEnter(void)
{
	// PuzzleGenerator pg;
	// pg.generateNextPuzzle();
}

/// \brief	Called when the state is removed
/* virtual */ void GameState::OnExit(void)
{
	// None
}

/// \brief	Called each frame
/// \param  dt The elapsed time since the last frame
/* virtual */ void GameState::Update(float dt)
{
	PuzzleGenerator pg;
	Grid grid = pg.generateNextPuzzle();

	std::string formatedGrid(GetStringGrid(grid));
	Vector2u gridSize(grid.getWidth() * 2, grid.getHeight() * 2);

	Engine::pRendering->Draw(gridSize, formatedGrid);
	Engine::pRendering->Draw(gridSize, 6, 6);
}
