#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cmath>

#include "LinearRegression.h"

using namespace std;

class DifficultyAnalyzer {

public:
	DifficultyAnalyzer() : m_filename("difficultyAnalyzerDefault.data"), m_linearRegression(nullptr, nullptr, 0) {
		loadData();
	}

	DifficultyAnalyzer(string filename) : m_filename(filename), m_linearRegression(nullptr, nullptr, 0) {
		loadData();
		computeData();
	}

	void computeData() {
		vector<double> scoresDouble;
		vector<double> timesDouble;

		for each (auto& scoreAndTimes in m_timesPerScore)
		{
			int score = scoreAndTimes.first;
			vector<int> times = scoreAndTimes.second;
			for each (int time in times) {
				scoresDouble.push_back(score);
				timesDouble.push_back(time);
				cout << "score : " << score << ", time : " << time << endl;
			}
		}

		m_linearRegression.init(scoresDouble.data(), timesDouble.data(), scoresDouble.size());
		m_linearRegression.train(0.01, 1500);
	}

	unsigned int getTimeForScore(int score) {
		return m_linearRegression.predict(score);
	}

	void saveData() const {
		ofstream file;

		file.open(m_filename);

		for each (auto& scoreAndTimes in m_timesPerScore)
		{
			int score = scoreAndTimes.first;
			vector<int> times = scoreAndTimes.second;
			file << score << ':';
			for each (int time in times)
			{
				file << time << ',';
			}
			file << endl; // Add an end line for readabilty
		}

		file.close();
	}

private:
	string m_filename;
	unordered_map<int, vector<int>> m_timesPerScore;
	LinearRegression m_linearRegression;

	void loadData() {
		ifstream file;
		string line;

		file.open(m_filename);

		while (getline(file, line))
		{
			istringstream lineStream(line);
			string buffer;
			getline(lineStream, buffer, ':');
			int score = stoi(buffer);
			if (m_timesPerScore.find(score) == m_timesPerScore.end())
			{
				m_timesPerScore[score] = vector<int>();
			}
			while (getline(lineStream, buffer, ','))
			{
				int time = stoi(buffer);
				m_timesPerScore[score].push_back(time);
			}
		}

		file.close();
	}

};