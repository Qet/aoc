#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cassert>

using namespace std;

enum class Direction
{
	N,S,E,W
};

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

	Direction getDirection(const Coord& toOther) //from me, to other
	{
		if (r == toOther.r)
		{
			if (c + 1 == toOther.c)
				return Direction::E;
			if (c - 1 == toOther.c)
				return Direction::W;
		}
		if (c == toOther.c)
		{
			if (r + 1 == toOther.r)
				return Direction::S;
			if (r - 1 == toOther.r)
				return Direction::N;
		}
		throw exception("cannot get direction of non-adjacent squares");
	}

	Coord N() const
	{
		return Coord(r - 1, c);
	}
	Coord S() const
	{
		return Coord(r + 1, c);
	}
	Coord E() const
	{
		return Coord(r, c + 1);
	}
	Coord W() const
	{
		return Coord(r, c - 1);
	}

};

enum class EnclosureStatus
{
	UNDEF,
	RIGHT, 
	LEFT,
	PIPE
};

struct Square
{
	vector<Square*> exits;
	
	int dist;
	bool isS;

	Coord loc;

	EnclosureStatus encl;

	void setLoc(Coord c)
	{
		loc = c;
	}

	Square():
		exits{},
		dist(INT_MAX),
		isS(false),
		encl(EnclosureStatus::UNDEF)
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

	void printEnclosureStatus()
	{
		for (const vector<Square>& row : data)
		{
			for (const Square& item : row)
			{
				if (item.encl == EnclosureStatus::LEFT)
					cout << 'L';
				else if (item.encl == EnclosureStatus::RIGHT)
					cout << 'R';
				else if (item.encl == EnclosureStatus::PIPE)
					cout << '#';
				else
					cout << 'U';
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

	void applyRL(Square* sq, Direction dir)
	{
		Coord rightSq = sq->loc;
		Coord leftSq = sq->loc;
		switch (dir)
		{
		case Direction::N:
			rightSq.c++;
			leftSq.c--;
			break;
		case Direction::E:
			rightSq.r++;
			leftSq.r--;
			break;
		case Direction::S:
			rightSq.c--;
			leftSq.c++;
			break;
		case Direction::W:
			rightSq.r--;
			leftSq.r++;
			break;
		}

		if (withinGrid(rightSq))
		{
			if (data[rightSq.r][rightSq.c].encl != EnclosureStatus::PIPE)
				data[rightSq.r][rightSq.c].encl = EnclosureStatus::RIGHT;
		}
		if (withinGrid(leftSq))
		{
			if (data[leftSq.r][leftSq.c].encl != EnclosureStatus::PIPE)
				data[leftSq.r][leftSq.c].encl = EnclosureStatus::LEFT;
		}

	}

	void traverseLoopSetEnclosures()
	{
		//traverse the loop and set adjacent squares as either right or left of the direction i'm going. 

		Square* curSq = data[locS.r][locS.c].exits[0];
		Square* prevSq = &data[locS.r][locS.c];

		while (curSq->loc != locS)
		{
			Direction dir = prevSq->loc.getDirection(curSq->loc);

			curSq->encl = EnclosureStatus::PIPE;

			applyRL(prevSq, dir);
			applyRL(curSq, dir);

			bool foundExit = false;
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
		}

	}

	void propogateEnclosures()
	{
		for (int i = 0; i < 100; i++) //terribly inefficient...
		{
			for (const vector<Square>& row : data)
			{
				for (const Square& item : row)
				{
					if (item.encl == EnclosureStatus::LEFT || item.encl == EnclosureStatus::RIGHT)
					{
						if (withinGrid(item.loc.N()) && getSquare(item.loc.N())->encl == EnclosureStatus::UNDEF)
						{
							getSquare(item.loc.N())->encl = item.encl;
						}
						if (withinGrid(item.loc.S()) && getSquare(item.loc.S())->encl == EnclosureStatus::UNDEF)
						{
							getSquare(item.loc.S())->encl = item.encl;
						}
						if (withinGrid(item.loc.E()) && getSquare(item.loc.E())->encl == EnclosureStatus::UNDEF)
						{
							getSquare(item.loc.E())->encl = item.encl;
						}
						if (withinGrid(item.loc.W()) && getSquare(item.loc.W())->encl == EnclosureStatus::UNDEF)
						{
							getSquare(item.loc.W())->encl = item.encl;
						}
					}
				}
			}
		}
		
	}

	int numEnclosedSquares()
	{
		int ret = 0;
		for (const vector<Square>& row : data)
		{
			for (const Square& item : row)
			{
				if (item.encl == EnclosureStatus::RIGHT)
					ret++;
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
	//grid.printDists();
	grid.traverseLoopSetEnclosures();
	grid.propogateEnclosures();
	grid.printEnclosureStatus();

	cout << "Max dist = " << grid.maxDist() << endl;
	cout << "enclosed sq = " << grid.numEnclosedSquares() << endl;
}
