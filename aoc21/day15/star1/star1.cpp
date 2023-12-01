
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <queue>

using namespace std;

enum class Dir
{
	N, E, S, W, NONE
};

enum class CellType
{
	START, END, CELL
};
struct Cell
{
	int risk;
	Dir bestDir;
	CellType cellType;
	int bestTotalRisk;
	bool processed = false;

	map<Dir, shared_ptr<Cell>> links;
};

typedef vector<shared_ptr<Cell>> cellvec;

cellvec cells;
int gridsize = 0;

shared_ptr<Cell> getCellIfValid(Dir dir, int row, int col)
{
	return cells[row * gridsize + col];
}

shared_ptr<Cell> getCellIfValid(Dir dir, int index)
{
	int row = index / gridsize;
	int col = index % gridsize;

	shared_ptr<Cell> ret = nullptr;

	if (dir == Dir::N && row - 1 >= 0)
	{
		ret = cells[(row - 1) * gridsize + col];
	}
	else if (dir == Dir::E && col + 1 < gridsize)
	{
		ret = cells[row * gridsize + col + 1];
	}
	else if (dir == Dir::S && row + 1 < gridsize)
	{
		ret = cells[(row + 1) * gridsize + col];
	}
	else if (dir == Dir::W && col - 1 >= 0)
	{
		ret = cells[row * gridsize + col - 1];
	}

	return ret;

}

Dir oppositeDir(Dir d)
{
	switch (d)
	{
	case Dir::N:
		return Dir::S;
	case Dir::S:
		return Dir::N;
	case Dir::E:
		return Dir::W;
	case Dir::W:
		return Dir::E;
	default:
		return Dir::NONE;
	}
}

void processCells()
{
	queue<shared_ptr<Cell>> cellqueue;
	
	cells.back()->bestTotalRisk = cells.back()->risk;
	cells.back()->processed = true;

	for (Dir d : {Dir::N, Dir::E, Dir::S, Dir::W})
	{
		if (cells.back()->links[d] != nullptr)
		{
			cellqueue.push(cells.back()->links[d]);
		}
	}

	while (cellqueue.size() > 0)
	{
		shared_ptr<Cell> curcell = cellqueue.front();
		cellqueue.pop();

		if (!curcell->processed)
		{
			for (Dir d : {Dir::N, Dir::E, Dir::S, Dir::W})
			{
				if (curcell->links[d] != nullptr && curcell->links[d]->processed)
				{
					int newRisk = curcell->links[d]->risk + curcell->bestTotalRisk;
					if (newRisk < curcell->links[d]->bestTotalRisk)
					{
						curcell->links[d]->bestTotalRisk = newRisk;
						curcell->links[d]->bestDir = oppositeDir(d);
					}
				}
			}

			curcell->processed = true;

			for (Dir d : {Dir::N, Dir::E, Dir::S, Dir::W})
			{
				if (curcell->links[d] != nullptr &&
					!curcell->links[d]->processed)
				{
					cellqueue.push(curcell->links[d]);
				}
			}
		}
	}

}

void printCells()
{
	int i = 0;
	for (auto c : cells)
	{
		if (i % gridsize == 0)
			cout << endl;
		cout << c->bestTotalRisk << "\t";
		i++;
	}
	cout << endl;

}

void printLowestTotalRisk()
{
	cout << "Lowest path risk " << cells.front()->bestTotalRisk - cells.back()->bestTotalRisk << "." << endl;
}

int main()
{
	string line;
	while (cin >> line)
	{
		for (char c : line)
		{
			shared_ptr<Cell> cell = make_shared<Cell>();
			cell->bestDir = Dir::NONE;
			cell->bestTotalRisk = 999999;
			cell->cellType = CellType::CELL;
			cell->risk = (int)(c - '0');
			cells.push_back(cell);
		}

		if (gridsize == 0)
			gridsize = line.length();
	}

	cells.front()->cellType = CellType::START;
	cells.back()->cellType = CellType::END;
	cells.back()->bestTotalRisk = cells.back()->risk;

	for (int i = 0; i < cells.size(); i++)
	{
		for (Dir d : {Dir::N, Dir::E, Dir::S, Dir::W})
		{
			cells[i]->links[d] = getCellIfValid(d, i);
		}
	}

	processCells();
	printLowestTotalRisk();
	printCells();

}

