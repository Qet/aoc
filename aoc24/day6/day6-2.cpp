
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <thread>

using namespace std;

typedef pair<int, int> pt;

enum class Dir
{
	N, S, E, W
};

struct VisitedOrientation
{
	VisitedOrientation(pt point, Dir dir) :
		point(point), dir(dir)
	{}
	pt point;
	Dir dir;

public:
	bool operator==(const VisitedOrientation& other) const
	{
		return point == other.point && dir == other.dir;
	}

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

	bool inLoop = false;


private:
	vector<string> data;
	pt guardPos;
	Dir guardDir;
	pt gridSize;

	set<pt> visitedPoints;
	vector<VisitedOrientation> visitedOrientations;

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
		else
		{
			stepGuardForward();
			if (!guardIsGone())
			{
				visitedPoints.insert(guardPos);
				
				VisitedOrientation newOrientation = { guardPos, guardDir };
				
				auto it = find(visitedOrientations.begin(), visitedOrientations.end(),
					newOrientation);
				if (it != visitedOrientations.end())
				{
					inLoop = true;
				}
				else
				{
					visitedOrientations.push_back(newOrientation);
				}
			}

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

	void setObstacle(pt obsPt)
	{
		data[obsPt.first][obsPt.second] = '#';
	}

	vector<pt> getPoints()
	{
		vector<pt> ret;
		for (auto p : visitedPoints)
			ret.push_back(p);
		return ret;
	}

};

class GridRunner
{
	vector<pt> testPoints;
	Grid baseGrid;
	vector<Grid> sims;
public:
	GridRunner(vector<pt> points, Grid grid) : 
		testPoints(points), 
		baseGrid(grid)
	{
		init();
	}

	void init()
	{
		for (pt p : testPoints)
		{
			sims.push_back(baseGrid);
			sims.back().setObstacle(p);
		}
	}

	int run()
	{
		int numGridsWithLoops = 0;
		for (Grid& g : sims)
		{
			int loops = 0;
			while (true)
			{
				g.moveGuard();
				loops++;

				if (g.guardIsGone())
				{
					cout << "Guard is gone" << endl;
					break;
				}
				else if (g.inLoop)
				{
					cout << "##Stuck in loop" << endl;
					numGridsWithLoops++;
					break;
				}
			}
		}
		return numGridsWithLoops;
	}
};


int main()
{
	string line;
	vector<string> data;
	while (getline(cin, line))
	{
		data.push_back(line);
	}

	Grid grid(data);
	Grid originalGrid{ grid };

	cout << "Init complete." << endl;

	while (!grid.guardIsGone())
	{
		grid.moveGuard();
	}

	GridRunner gr(grid.getPoints(), originalGrid);
	int loops = gr.run();
	
	cout << "Part 2: num loops: " << loops << endl;

	return 0;
}
