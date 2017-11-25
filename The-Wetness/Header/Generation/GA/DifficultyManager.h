#pragma once

#include "DifficultyAnalyzer.hpp"

class DifficultyManager {

public:

	DifficultyManager(string difficultyDataFile) : m_currentScore(0), m_difficultyAnalyzer(difficultyDataFile) {

	}

	int getTargetScore() {
		int timeToAchieve = m_difficultyAnalyzer.getTimeForScore(m_currentScore);
		int remainingTime = timeToAchieve - m_timeTaken;
		m_currentScore += remainingTime;
	}

	void adjustDifficulty(int timeTaken) {
		m_timeTaken = timeTaken;
	}

private:
	int m_currentScore;
	bool m_timeTaken;
	DifficultyAnalyzer m_difficultyAnalyzer;
};