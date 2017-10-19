#pragma once

class DifficultyManager {

public:
	int getTargetScore() {

	}

	void adjustDifficulty(int timeTaken) {

	}
private:
	int m_currentLevel;
	const int m_scoresByDifficultyLevel[] = {  0, 50, 70, 80, 100, 130, 150 };
	const int m_timesByDifficultyLevel[] =  { 15, 30, 30, 30,  30, 120, 140 };
};