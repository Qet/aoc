#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <sstream>

using namespace std;


typedef pair<int, int> pt;

enum class Dir
{
	N, S, E, W
};

struct Cell
{
	Cell(char letter) : letter(letter)
	{}

	char letter;
	int regionID{ 0 };
	bool assignedToRegion{ false };
};

struct FenceGrid
{
	vector<vector<bool>> posts;

	pt gridSize;

	void setData(pt p, bool v)
	{
		posts[p.first][p.second] = v;
	}

	bool getData(pt p)
	{
		return posts[p.first][p.second];
	}

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

	vector<pt> surroundingPts(pt p, bool keepInvalids = false)
	{
		vector<pt> ret;
		vector<Dir> dirs{ Dir::N, Dir::E, Dir::S, Dir::W };
		for (Dir d : dirs)
		{
			pt next = nextPoint(p, d);
			if (keepInvalids || withinGrid(next))
			{
				ret.push_back(next);
			}
		}
		return ret;
	}

	void init(pt gridSize)
	{
		this->gridSize = gridSize;
		for (int i = 0; i < gridSize.first; i++)
		{
			posts.push_back({});
			for (int j = 0; j < gridSize.second; j++)
			{
				posts[i].push_back(false);
			}
		}
	}

	pt findFirst()
	{
		for (int i = 0; i < gridSize.first; i++)
		{
			for (int j = 0; j < gridSize.second; j++)
			{
				if (posts[i][j])
				{
					return { i, j };
				}
			}
		}
		throw new exception("Failed to find fence start");
	}

	int sides()
	{
		set<pt> visited;
		pt first = findFirst();
		pt curPt = first;
		vector<Dir> dirs{ Dir::N, Dir::E, Dir::S, Dir::W };
		Dir curDir = Dir::N;
		int sideCount = 0;
		visited.insert(curPt);

		while (true)
		{
			for (Dir d : dirs)
			{
				pt nextPt = nextPoint(curPt, d);
				if (withinGrid(nextPt) &&
					visited.count(nextPt) == 0 &&
					getData(nextPt))
				{
					curDir = d;
					curPt = nextPt;
					visited.insert(curPt);
					sideCount++;
					break;
				}
			}

			//keep going in the same direction until you can't anymore. 
			while (true)
			{
				pt nextPt = nextPoint(curPt, curDir);
				if (!withinGrid(nextPt) || !getData(nextPt))
					break;

				curPt = nextPt;
				visited.insert(curPt);
			}

			if (curPt == first)
				break;
		}

		return visited.size();
	}

};


struct Grid
{
	vector<vector<Cell>> data;
	pt gridSize;

	vector<FenceGrid> fences;

	void init(vector<string> inputData)
	{
		gridSize = { inputData[0].length(), inputData.size() };

		for (int i = 0; i < inputData.size(); i++)
		{
			data.push_back({});
			for (char c : inputData[i])
			{
				data[i].push_back(c);
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

	Cell& getData(pt p)
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

	vector<pt> surroundingPts(pt p, bool keepInvalids = false)
	{
		vector<pt> ret;
		vector<Dir> dirs{ Dir::N, Dir::E, Dir::S, Dir::W };
		for (Dir d : dirs)
		{
			pt next = nextPoint(p, d);
			if (keepInvalids || withinGrid(next))
			{
				ret.push_back(next);
			}
		}
		return ret;
	}

	vector<pair<pt, Dir>> surroundingPtsDirs(pt p, bool keepInvalids = false)
	{
		vector<pair<pt, Dir>> ret;
		vector<Dir> dirs{ Dir::N, Dir::E, Dir::S, Dir::W };
		for (Dir d : dirs)
		{
			pt next = nextPoint(p, d);
			if (keepInvalids || withinGrid(next))
			{
				ret.push_back({ next, d });
			}
		}
		return ret;
	}

	/*
	proposed algorithm:
	for all cells that haven't been processed
		flood fill the current unprocessed cell and mark all those cells as processed, and with a unique region ID
		continue until all cells are processed
	each region's area is the number of cells with that region ID
	each region's perimeter is the sum of, for all cells in the region, the number of cells N, S, E and W that exist and have a different region ID, and any that don't exist (i.e. map edges)
	*/

	void floodFill(pt start, int regionID)
	{
		auto& dstart = getData(start);
		dstart.assignedToRegion = true;
		dstart.regionID = regionID;
		vector<pt> pts = surroundingPts(start);
		for (pt p : pts)
		{
			auto& adj = getData(p);
			if (adj.letter == dstart.letter && adj.assignedToRegion == false)
				floodFill(p, regionID);
		}
	}

	void applyRegions()
	{
		int curRegionID = 0;

		for (int i = 0; i < gridSize.first; i++)
		{
			for (int j = 0; j < gridSize.second; j++)
			{
				if (!data[i][j].assignedToRegion)
				{
					floodFill({ i, j }, curRegionID);
					curRegionID++;
				}
			}
		}
	}

	map<int, int> perimeters;
	map<int, int> areas;
	map<int, int> sides;


	int price()
	{
		int totalPrice = 0;

		for (int i = 0; i < gridSize.first; i++)
		{
			for (int j = 0; j < gridSize.second; j++)
			{
				pt curPt{ i, j };
				vector<pt> surrPts = surroundingPts(curPt, true);
				for (pt p : surrPts)
				{
					if (withinGrid(p))
					{
						if (getData(p).regionID != getData(curPt).regionID)
							perimeters[getData(curPt).regionID]++;
					}
					else
					{
						perimeters[getData(curPt).regionID]++;
					}
				}

				areas[getData(curPt).regionID]++;
			}
		}

		for (auto [k, v] : perimeters)
		{
			totalPrice += v * areas[k];

			fences.push_back({});
			FenceGrid& fence = fences[k];
			fence.init({ gridSize.first + 1, gridSize.second + 1 });

			for (int i = 0; i < gridSize.first; i++)
			{
				for (int j = 0; j < gridSize.second; j++)
				{
					pt curPt{ i, j };
					Cell& c = getData(curPt);

					if (c.regionID == k)
					{
						vector<pair<pt, Dir>> surrPts = surroundingPtsDirs(curPt, true);
						for (pair<pt, Dir> curSurPt : surrPts)
						{
							pt p = curSurPt.first;
							Dir dir = curSurPt.second;
							if ((withinGrid(p) && getData(p).regionID != getData(curPt).regionID) ||
								(!withinGrid(p)))
							{
								//if I would normally mark this as a perimeter, that means there's 
								//two posts  (for a 
								//N: 0,0 and 0,1 
								switch (dir)
								{
								case Dir::N:
									fence.setData(curPt, true);
									fence.setData({ curPt.first, curPt.second + 1 }, true);
									break;
								case Dir::E:
									fence.setData({ curPt.first, curPt.second + 1 }, true);
									fence.setData({ curPt.first + 1, curPt.second + 1 }, true);
									break;
								case Dir::S:
									fence.setData({ curPt.first + 1, curPt.second }, true);
									fence.setData({ curPt.first + 1, curPt.second + 1 }, true);
									break;
								case Dir::W:
									fence.setData(curPt, true);
									fence.setData({ curPt.first + 1, curPt.second }, true);
									break;
								}
							}
						}
					}
				}
			}
		}

		for (auto [k, v] : perimeters)
		{
			sides[k] = fences[k].sides();
		}

		return totalPrice;
	}

	int discountPrice()
	{
		int total = 0;
		for (auto [k, v] : sides)
		{
			total += v * areas[k];
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

	grid.applyRegions();

	cout << "Part 1 total: " << grid.price() << endl;

	cout << "Part 2 total: " << grid.discountPrice() << endl;


	return 0;
}
