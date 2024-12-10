#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef pair<int, int> pt;

enum class Dir
{
	N, S, E, W
};

struct Grid
{
	vector<vector<int>> data;
	pt gridSize;

	void init(vector<string> inputData)
	{
		gridSize = { inputData[0].length(), inputData.size() };

		for (int i = 0; i < inputData.size(); i++)
		{
			data.push_back({});
			for (char c : inputData[i])
			{
				string s{ c };
				int ci = stoi(s);
				data[i].push_back(ci);
			}
		}
	}

	bool withinGrid(pt point)
	{
		return
			point.first >= 0 &&
			point.first < gridSize.first &&
			point.second >= 0 &&
			point.second < gridSize.second;
	}

	int getData(pt p)
	{
		return data[p.first][p.second];
	}

	pt nextPoint(pt point, Dir dir)
	{
		switch (dir)
		{
		case Dir::N:
			return { point.first - 1, point.second };
		case Dir::S:
			return { point.first + 1, point.second };
		case Dir::E:
			return { point.first, point.second + 1 };
		case Dir::W:
			return { point.first, point.second - 1 };
		}
	}

	vector<pt> surroundingPts(pt p, int targetVal)
	{
		vector<pt> ret;
		vector<Dir> dirs{ Dir::N, Dir::E, Dir::S, Dir::W };
		for (Dir d : dirs)
		{
			pt next = nextPoint(p, d);
			if (withinGrid(next) && getData(next) == targetVal)
			{
				ret.push_back(next);
			}
		}
		return ret;
	}

	void followTrail(pt curPt, set<pt> &reachedPeaks)
	{
		int curVal = getData(curPt);

		if (curVal == 9)
		{
			reachedPeaks.insert(curPt);
			return;
		}

		vector<pt> surrPts = surroundingPts(curPt, curVal + 1);

		for (pt p : surrPts)
		{
			followTrail(p, reachedPeaks);
		}

	}

	int scoreTrailheads()
	{
		map<pt, int> trailheadScores;

		for (int r = 0; r < data.size(); r++)
		{
			for (int c = 0; c < data[r].size(); c++)
			{
				pt curPt{ r, c };
				if (getData(curPt) == 0)
				{
					set<pt> reachedPeaks;
					followTrail(curPt, reachedPeaks);
					trailheadScores[curPt] = reachedPeaks.size();
				}
			}
		}

		int total = 0;
		for (auto& [p, score] : trailheadScores)
		{
			total += score;
		}
		return total;
	}

};

int main()
{
	string line;
	vector<string> lines;
	while (getline(cin, line))
	{
		lines.push_back(line);
	}
	Grid grid;
	grid.init(lines);

	cout << "Part 1: " << grid.scoreTrailheads() << endl;

}

