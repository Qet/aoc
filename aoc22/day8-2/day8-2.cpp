#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Forest
{
	vector<vector<int>> grid;
	vector<vector<int>> scenicScores;

	int countN(int row, int col)
	{
		int dist = 0;
		int h = grid[row][col];
		for (int curRow = row - 1; curRow >= 0; curRow--)
		{
			dist++;
			if (grid[curRow][col] >= h)
				break;
		}
		return dist;
	}

	int countE(int row, int col)
	{
		int dist = 0;
		int h = grid[row][col];
		for (int curCol = col + 1; curCol < grid[0].size(); curCol++)
		{
			dist++;
			if (grid[row][curCol] >= h)
				break;
		}
		return dist;
	}

	int countS(int row, int col)
	{
		int dist = 0;
		int h = grid[row][col];
		for (int curRow = row + 1; curRow < grid.size(); curRow++)
		{
			dist++;
			if (grid[curRow][col] >= h)
				break;
		}
		return dist;
	}

	int countW(int row, int col)
	{
		int dist = 0;
		int h = grid[row][col];
		for (int curCol = col - 1; curCol >= 0; curCol--)
		{
			dist++;
			if (grid[row][curCol] >= h)
				break;
		}
		return dist;
	}

	void calcScenicScores()
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				scenicScores[i][j] = countN(i, j) * countE(i, j) * countS(i, j) * countW(i, j);
			}
		}
	}

	void initialiseScenicScores()
	{
		for (int i = 0; i < grid.size(); i++)
		{
			scenicScores.push_back(vector<int>(grid[0].size(), 0));		
		}
	}

	int maxScenicScore()
	{
		int max = 0;
		for (auto& row : scenicScores)
		{
			int rowMax = *max_element(begin(row), end(row));
			if (rowMax > max)
			{
				max = rowMax;
			}
		}
		return max;
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

	forest.initialiseScenicScores();
	forest.calcScenicScores();
	cout << forest.maxScenicScore() << endl;
	
	system("pause");
}
