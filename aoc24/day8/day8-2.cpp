
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


int main()
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
						for (int step = 0; step < rows * 2; step++)
						{
							//using vectors, the vector from origin to point N (ON) is equal to N x OA - (N-1) x OB. 
							//keep iterating N until it goes off the map. N is "step" in this case. 
							pt pt_c = { (step + 1) * it_b->first - step * it_a->first,
										(step + 1) * it_b->second - step * it_a->second };

							if (grid.withinGrid(pt_c))
								combinedAntinodeSet.insert(pt_c);
							else
								break;
						}
					}
				}
			}
		}
	}

	int total = combinedAntinodeSet.size();

	std::cout << "Part 2 total: " << total << endl;

	return 0;

}
