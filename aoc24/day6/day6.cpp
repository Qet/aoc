
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

typedef pair<int, int> pt;

enum class Dir
{
	N, S, E, W
};

class Grid
{
public: 
	Grid(vector<string> data) : 
		data(data), 
		guardPos({ 0, 0 }),
		guardDir(Dir::N)
	{
		init();
	}

private: 
	vector<string> data;
	pt guardPos;
	Dir guardDir;
	pt gridSize;

	set<pt> visitedPoints;

	void init()
	{
		gridSize = { data[0].length(), data.size() };

		for (int i = 0; i < data.size(); i++)
		{
			auto pos = data[i].find('^');
			if (pos != string::npos)
			{
				guardPos = { i, pos };
				data[i][pos] = '.';
			}
		}
	}

private: 
	bool withinGrid(pt point)
	{
		return
			point.first >= 0 &&
			point.first < gridSize.first &&
			point.second >= 0 &&
			point.second < gridSize.second;
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

	bool isObstacle(pt point)
	{
		return data[point.first][point.second] == '#';
	}

	bool guardIsFacingObstacle()
	{
		pt nextPt = nextPoint(guardPos, guardDir);
		if (withinGrid(nextPt))
		{
			return isObstacle(nextPt);
		}
		return false; //all squares outside the grid are obstacle free. 
	}

	void turnGuard()
	{
		switch (guardDir)
		{
		case Dir::N: 
			guardDir = Dir::E;
			break;
		case Dir::E:
			guardDir = Dir::S;
			break;
		case Dir::S:
			guardDir = Dir::W;
			break;
		case Dir::W:
			guardDir = Dir::N;
			break;
		}
	}

	void stepGuardForward()
	{
		guardPos = nextPoint(guardPos, guardDir);
	}

public:
	void moveGuard()
	{
		if (guardIsFacingObstacle())
		{
			turnGuard();
		}
		else {
			stepGuardForward();
			if (!guardIsGone())
				visitedPoints.insert(guardPos);
		}
	}
	
	bool guardIsGone()
	{
		return !withinGrid(guardPos);
	}

	int numGuardPositions()
	{
		return visitedPoints.size();
	}

};


int main1()
{
	string line;
	vector<string> data;
	while (getline(cin, line))
	{
		data.push_back(line);
	}

	Grid grid(data);

	while (!grid.guardIsGone())
	{
		grid.moveGuard();
	}

	cout << "Part 1, guard positions: " << grid.numGuardPositions() << endl;
	
	return 0;
}
