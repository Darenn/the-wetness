/// \file       GameState.cpp
/// \date       25/11/2017
/// \package    Game
/// \author     Darenn KELLER

#include "Engine/Engine.hpp"
#include "Game/State/GameState.hpp"
#include "Generation/PuzzleGenerator.hpp"

#include <sstream>
#include <fstream>


/// \brief	Destructor
/* virtual */ GameState::~GameState(void)
{
	// None
}

/// \brief	Called when the state is pushed
/* virtual */ void GameState::OnEnter(void)
{
	m_currentGrid = m_puzzleGenerator.generateNextPuzzle();
	m_playerPosition = Vector2u(m_currentGrid.getDatas(Grid::Data::START)[0].x * 2, m_currentGrid.getDatas(Grid::Data::START)[0].y * 2);
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
	if (hasWon() || GetAsyncKeyState(VK_F2) & 0x8000) {
		Engine::pSoundEngine->Play("win.wav", SND_ASYNC);
		m_currentGrid = m_puzzleGenerator.generateNextPuzzle();
		m_playerPath.clear();
		m_playerPosition = Vector2u(m_currentGrid.getDatas(Grid::Data::START)[0].x * 2, m_currentGrid.getDatas(Grid::Data::START)[0].y * 2);
	}
	handleInput();
	render();
}

void GameState::render() {
	std::string formatedGrid(m_currentGrid.toString());
	Vector2u gridDisplayedSize(m_currentGrid.getWidth() * 2, m_currentGrid.getHeight() * 2);
	Engine::pRendering->Draw(gridDisplayedSize, NODE_SIZE, formatedGrid); // draw grid
	Engine::pRendering->Draw(gridDisplayedSize, NODE_SIZE, m_playerPath, Color::Red); // draw the path
	Engine::pRendering->Draw(gridDisplayedSize, NODE_SIZE, m_playerPosition.x, m_playerPosition.y); // draw player

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		Grid::Coordinates start = m_currentGrid.getDatas(Grid::Data::START)[0];
		Grid::Coordinates exit = m_currentGrid.getDatas(Grid::Data::EXIT)[0];
		std::vector<Grid::Coordinates> path = m_currentGrid.getValidPath(start, exit);

		for (Grid::Coordinates& coord : path) { coord.x *= 2; coord.y *= 2; }
		std::vector<Vector2u> pathRendering;
		for (Grid::Coordinates& coord : path)
		{
			pathRendering.push_back(Vector2u(coord.x, coord.y));
		}
		Vector2u gridDisplayedSize(m_currentGrid.getWidth() * 2, m_currentGrid.getHeight() * 2);
		Engine::pRendering->Draw(gridDisplayedSize, NODE_SIZE, pathRendering, Color::Purple); // draw the path
	}
}

void GameState::handleInput() {
	if (m_inputTimer.GetElaspedTime() < 0.1) return;
	m_inputTimer.Start();
	Grid::Coordinates newPlayerPos{ static_cast<unsigned char>(m_playerPosition.x / 2), static_cast<unsigned char>(m_playerPosition.y / 2) };
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (m_currentGrid.isLinkedWithNeighbor(newPlayerPos, Grid::Direction::NORTH))
			newPlayerPos.y--;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (m_currentGrid.isLinkedWithNeighbor(newPlayerPos, Grid::Direction::SOUTH))
			newPlayerPos.y++;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (m_currentGrid.isLinkedWithNeighbor(newPlayerPos, Grid::Direction::WEST))
			newPlayerPos.x--;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (m_currentGrid.isLinkedWithNeighbor(newPlayerPos, Grid::Direction::EAST))
			newPlayerPos.x++;
	}
	Vector2u pos = Vector2u(newPlayerPos.x * 2, newPlayerPos.y * 2);
	if (m_currentGrid.isInBounds(newPlayerPos)) {
		if (m_playerPath.size() > 1 && pos == m_playerPath[m_playerPath.size() - 2]) {
			m_playerPath.pop_back();
			m_playerPosition = pos;
		}
		else if (!(std::find(m_playerPath.begin(), m_playerPath.end(), pos) != m_playerPath.end())) {
			m_playerPath.push_back(pos);
			m_playerPosition = pos;
		}	
	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		Grid::Coordinates start = m_currentGrid.getDatas(Grid::Data::START)[0];
		Grid::Coordinates exit = m_currentGrid.getDatas(Grid::Data::EXIT)[0];
		std::vector<Grid::Coordinates> path = m_currentGrid.getValidPath(start, exit);
		for (Grid::Coordinates& coord : path) { coord.x *= 2; coord.y *= 2; }
		std::vector<Vector2u> pathRendering;
		for (Grid::Coordinates& coord : path) 
		{ pathRendering.push_back(Vector2u(coord.x, coord.y)); }
		Vector2u gridDisplayedSize(m_currentGrid.getWidth() * 2, m_currentGrid.getHeight() * 2);
		Engine::pRendering->Draw(gridDisplayedSize, NODE_SIZE, pathRendering, Color::Purple); // draw the path
	}

}

bool GameState::hasWon() {
	std::vector<Grid::Coordinates> mustPassPath = m_currentGrid.getDatas(Grid::Data::MUST_PASS);
	for (size_t i = 0; i < mustPassPath.size(); i++)
	{
		Vector2u coord = Vector2u(mustPassPath[i].x * 2, mustPassPath[i].y * 2);
		if (!(std::find(m_playerPath.begin(), m_playerPath.end(), coord) != m_playerPath.end()))
			return false;
	}
	Vector2u exit = Vector2u(m_currentGrid.getDatas(Grid::Data::EXIT)[0].x * 2, m_currentGrid.getDatas(Grid::Data::EXIT)[0].y * 2);
	if (!m_playerPath.empty() && m_playerPath.back() != exit)
		return false;
	return true;
}
