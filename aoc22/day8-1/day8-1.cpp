#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Forest
{
	vector<vector<int>> grid;
	
	bool visibleN(int row, int col)
	{
		int max = -1;
		for (int curRow = row - 1; curRow >= 0; curRow--)
		{
			if (grid[curRow][col] > max)
				max = grid[curRow][col];
		}
		return max < grid[row][col];
	}

	bool visibleE(int row, int col)
	{
		int max = -1;
		for (int curCol = col + 1; curCol < grid[0].size(); curCol++)
		{
			if (grid[row][curCol] > max)
				max = grid[row][curCol];
		}
		return max < grid[row][col];
	}

	bool visibleS(int row, int col)
	{
		int max = -1;
		for (int curRow = row + 1; curRow < grid.size(); curRow++)
		{
			if (grid[curRow][col] > max)
				max = grid[curRow][col];
		}
		return max < grid[row][col];
	}

	bool visibleW(int row, int col)
	{
		int max = -1;
		for (int curCol = col - 1; curCol >= 0; curCol--)
		{
			if (grid[row][curCol] > max)
				max = grid[row][curCol];
		}
		return max < grid[row][col];
	}

	int numVisibleTrees()
	{
		int vis = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (visibleN(i, j) || visibleE(i, j) || visibleW(i, j) || visibleS(i, j))
					vis++;
			}
		}
		return vis;
	}

};

int main()
{
	string line;
	Forest forest;
	while (getline(cin, line))
	{
		forest.grid.push_back(vector<int>());
		for (char c : line)
		{
			forest.grid.back().push_back(c - '0');
		}
	}
	
	cout << forest.numVisibleTrees() << endl;
	cout << "hello?";

}
