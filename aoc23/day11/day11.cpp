#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

struct Coord
{
	int64_t r = 0, c = 0;
	Coord(int64_t r, int64_t c) : r(r), c(c) {}
	Coord() {}

	Coord operator+(const Coord& other)
	{
		return Coord(other.r + r, other.c + c);
	}

	bool operator==(const Coord& other)
	{
		return other.r == r && other.c == c;
	}

	bool operator!=(const Coord& other)
	{
		return !(*this == other);
	}

	int64_t manhattanDist(const Coord& other)
	{
		return abs(other.r - r) + abs(other.c - c);
	}
};

bool containsRow(vector<Coord>& galaxies, int64_t row)
{
	for (Coord c : galaxies)
	{
		if (c.r == row)
			return true;
	}
	return false;
}

bool containsCol(vector<Coord>& galaxies, int64_t col)
{
	for (Coord c : galaxies)
	{
		if (c.c == col)
			return true;
	}
	return false;
}

void expandFromRow(vector<Coord>& galaxies, int64_t row, int64_t expansionAmount)
{
	for (Coord& c : galaxies)
	{
		if (c.r > row)
			c.r+= expansionAmount;
	}
}

void expandFromCol(vector<Coord>& galaxies, int64_t col, int64_t expansionAmount)
{
	for (Coord& c : galaxies)
	{
		if (c.c > col)
			c.c+= expansionAmount;
	}
}

void applyCosmicExpansion(vector<Coord>& galaxies, int64_t rowMax, int64_t colMax, int64_t expansionAmount)
{
	for (int64_t r = 0; r < rowMax; r++)
	{
		if (!containsRow(galaxies, r))
		{
			expandFromRow(galaxies, r, expansionAmount);
			r+= expansionAmount; 
			rowMax+= expansionAmount;
		}
	}

	for (int64_t c = 0; c < colMax; c++)
	{
		if (!containsCol(galaxies, c))
		{
			expandFromCol(galaxies, c, expansionAmount);
			c+= expansionAmount;
			colMax+= expansionAmount;
		}
	}

}

int64_t distPairsSum(vector<Coord>& galaxies)
{
	int64_t ret = 0;
	for (int64_t i = 0; i < galaxies.size() - 1; i++)
	{
		for (int64_t j = i + 1; j < galaxies.size(); j++)
		{
			ret += galaxies[i].manhattanDist(galaxies[j]);
		}
	}
	return ret;
}

int main()
{
	vector<Coord> galaxies;
	string line;

	int64_t r = 0;
	int64_t c = 0;
	while (getline(cin, line))
	{
		c = 0;
		for (char ch : line)
		{
			if (ch == '#')
				galaxies.push_back(Coord(r, c));
			c++;
		}
		r++;
	}
	
	applyCosmicExpansion(galaxies, r, c, 999999); //replace 999999 with a 1 for part 1. 
	int64_t dist = distPairsSum(galaxies);
	cout << "Distances sum = " << dist << endl;

}

