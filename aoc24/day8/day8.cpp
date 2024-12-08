
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

typedef pair<int, int> pt;

struct Grid
{
	Grid(pt gridSize) :
		gridSize(gridSize)
	{}

	pt gridSize;

	bool withinGrid(pt point)
	{
		return
			point.first >= 0 &&
			point.first < gridSize.first &&
			point.second >= 0 &&
			point.second < gridSize.second;
	}
};


int main1()
{
	
	map<char, set<pt>> antennaSets;
	set<pt> combinedAntinodeSet;
	int rows = 0, cols = 0;
	{
		string line;
		int row = 0;
		while (getline(cin, line))
		{
			if (cols == 0) cols = line.length();
			for (int col = 0; col < line.length(); col++)
			{
				char c = line[col];
				if (c != '.')
				{
					antennaSets[c].insert({ row, col });
				}
			}

			row++;
		}
		rows = row;
	}
	Grid grid({ rows, cols });

	/*
	for each set of the same letter value
	for every combination of two points (a,b) (ordering matters)
		double the vector (2x a->b = a->b2)
			mark this point
			only if its on the map
	*/


	for (auto& [c, s] : antennaSets)
	{
		if (s.size() > 1)
		{
			for (auto it_a = s.begin(); it_a != s.end(); ++it_a)
			{
				for (auto it_b = s.begin(); it_b != s.end(); ++it_b)
				{
					if (*it_a != *it_b)
					{
						pt pt_c = { 2 * (it_b->first) - it_a->first,
									2 * (it_b->second) - it_a->second };
						
						if (grid.withinGrid(pt_c))	combinedAntinodeSet.insert(pt_c);
					}
				}
			}
		}
	}

	int total = combinedAntinodeSet.size();

	cout << "Part 1 total: " << total << endl;
	return 0;

}
