#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <hash_map>

using namespace std;

class DifficultyAnalyzer {

public:
	DifficultyAnalyzer(string filename) {

	}

private:
	string m_filename;
	hash_map<int, vector<int>> m_timesPerScore;

	void loadData() {
		ifstream file;
		string line;
		file.open(m_filename);

		while (getline(file, line, ':'))
		{
			int score = stoi(line);
			if (m_timesPerScore.find(score) == m_timesPerScore.end())
			{
				m_timesPerScore[score] = vector<int>();
			}
			while (getline(file, line, ','))
			{
				int time = stoi(line);
				m_timesPerScore[score].push_back(time);
			}
			getline(file, line); // Jump to the next line
		}

		file.close();
	}
};