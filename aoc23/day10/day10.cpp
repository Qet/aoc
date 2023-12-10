#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cassert>

using namespace std;

struct Coord
{
	int r = 0, c = 0;
	Coord(int r, int c) : r(r), c(c) {}
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
};

struct Square
{
	vector<Square*> exits;
	
	int dist;
	bool isS;

	Coord loc;

	void setLoc(Coord c)
	{
		loc = c;
	}

	Square():
		exits{},
		dist(INT_MAX),
		isS(false)
	{

	}
};



struct Grid
{
	vector<vector<Square>> data;

	Grid(int width, int height)
	{
		for (int i = 0; i < height; i++)
		{
			data.push_back(vector<Square>(width));
		}
	}

	// . F 7 J L | - S

	map<char, vector<Coord>> exitOffsets{
		{'.', {}},
		{'F', {{0, 1}, {1, 0}}},
		{'7', {{0, -1}, {1, 0}}},
		{'J', {{0, -1}, {-1, 0}}},
		{'L', {{0, 1}, {-1, 0}}},
		{'|', {{-1, 0}, {1, 0}}},
		{'-', {{0, -1}, {0, 1}}},
		{'S', {}}
	};


	bool withinGrid(Coord coord)
	{
		return coord.r >= 0 && 
			coord.c >= 0 && 
			coord.r < data[0].size() && 
			coord.c < data.size();
	}

	Square* getSquare(Coord c)
	{
		return &data[c.r][c.c];
	}

	Coord locS;

	void parseData(const vector<string>& lines)
	{
		for (int r = 0; r < lines.size(); r++)
		{
			for (int c = 0; c < lines[0].size(); c++)
			{
				char pipe = lines[r][c];
				if (pipe == 'S')
				{
					data[r][c].isS = true;
					locS = Coord(r, c);
				}

				data[r][c].setLoc(Coord(r, c));

				for (Coord off : exitOffsets[pipe])
				{
					Coord exCoord = off + Coord(r, c);
					if (withinGrid(exCoord))
					{
						data[r][c].exits.push_back(getSquare(exCoord));
					}
				}
			}
		}
	}

	void hookUpS()
	{
		Square* S = &data[locS.r][locS.c];


		for (Coord curOffset : vector<Coord>{ {-1, 0}, {0, -1}, {0, 1}, {1, 0} })
		{
			Coord curCoord = curOffset + locS;
			if (withinGrid(curCoord))
			{
				Square* curSquare = &data[curCoord.r][curCoord.c];
				for (Square* exit : curSquare->exits)
				{
					if (exit == S)
					{
						S->exits.push_back(curSquare);
					}
				}
			}
		}
	}

	void calcDists()
	{
		for (Square* startExit : data[locS.r][locS.c].exits)
		{
			int curDist = 1;
			Square* curSq = startExit;
			Square* prevSq = &data[locS.r][locS.c];

			while (curSq->loc != locS)
			{
				bool foundExit = false;
				curSq->dist = min(curDist, curSq->dist);
				for (Square* ex : curSq->exits)
				{
					if (ex != prevSq)
					{
						prevSq = curSq;
						curSq = ex;
						foundExit = true;
						break;
					}
				}
				assert(foundExit, "failed to find exit");
				curDist++;
			}


		}

	}

	void printDists()
	{
		for (const vector<Square>& row : data)
		{
			for (const Square& item : row)
			{
				if (item.dist > 999)
					cout << 'x' << '\t';
				else
					cout << item.dist << '\t';
			}
			cout << endl;
		}
		cout << endl;
	}

	int maxDist()
	{
		int ret = 0;
		for (const vector<Square>& row : data)
		{
			for (const Square& item : row)
			{
				if (item.dist > ret && item.dist != INT_MAX)
					ret = item.dist;
			}
		}
		return ret;
	}

};


int main()
{
	vector<string> lines;
	string temp;
	while (getline(cin, temp))
	{
		lines.push_back(temp);
	}
	Grid grid(lines[0].size(), lines.size());
	grid.parseData(lines);
	grid.hookUpS();
	grid.calcDists();
	grid.printDists();

	cout << "Max dist = " << grid.maxDist() << endl;

}
