#include <vector>
#include <iostream>
#include <string>

using namespace std;

int numXmases(string data)
{
	int ret = 0;
	size_t pos = 0;
	while (true)
	{
		pos = data.find("XMAS", pos);
		if (pos == data.npos) break;
		ret++;
		pos++;
	}
	return ret;
}

struct grid
{
	const vector<vector<char>> &data;
	int rows;
	int cols;

	grid(const vector<vector<char>> &data) :
		data(data)
	{
		rows = data.size();
		cols = data[0].size();
	}

	bool inRange(int r, int c)
	{
		return r >= 0 && c >= 0 && r < rows && c < cols;
	}
};



int main1()
{
	vector<vector<char>> data;
	string line;

	while (getline(cin, line))
	{
		data.push_back({});
		for (char c : line)
		{
			data.back().push_back(c);
		}
	}

	string searchStr = "";

	const int ROWS = data.size();
	const int COLS = data[0].size();

	grid g(data);

	//horizontal
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			searchStr += data[r][c];
		}
		searchStr += ".";

		for (int c = COLS - 1; c >= 0; c--)
		{
			searchStr += data[r][c];
		}
		searchStr += ".";
	}

	//vertical
	for (int c = 0; c < COLS; c++)
	{
		for (int r = 0; r < ROWS; r++)
		{
			searchStr += data[r][c];
		}
		searchStr += ".";

		for (int r = ROWS - 1; r >= 0; r--)
		{
			searchStr += data[r][c];
		}
		searchStr += ".";
	}

	//top diag
	for(int c = 0; c < COLS; c++)
	{
		int curRow, curCol;
		
		//right
		curCol = c;
		curRow = 0;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow++;
			curCol++;
		}
		searchStr += ".";

		//left
		curCol = c;
		curRow = 0;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow++;
			curCol--;
		}
		searchStr += ".";
	}

	//bottom diag
	for (int c = 0; c < COLS; c++)
	{
		int curRow, curCol;

		//right
		curCol = c;
		curRow = ROWS-1;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow--;
			curCol++;
		}
		searchStr += ".";

		//left
		curCol = c;
		curRow = ROWS-1;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow--;
			curCol--;
		}
		searchStr += ".";
	}


	//left diag (but skip top and bottom)
	for (int r = 1; r < ROWS-1; r++)
	{
		int curRow, curCol;

		//up
		curCol = 0;
		curRow = r;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow--;
			curCol++;
		}
		searchStr += ".";

		//down
		curCol = 0;
		curRow = r;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow++;
			curCol++;
		}
		searchStr += ".";
	}

	//right diag (but skip top and bottom)
	for (int r = 1; r < ROWS - 1; r++)
	{
		int curRow, curCol;

		//up
		curCol = COLS-1;
		curRow = r;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow--;
			curCol--;
		}
		searchStr += ".";

		//down
		curCol = COLS-1;
		curRow = r;
		while (g.inRange(curRow, curCol))
		{
			searchStr += data[curRow][curCol];
			curRow++;
			curCol--;
		}
		searchStr += ".";
	}




	cout << "Part 1 num xmases: " << numXmases(searchStr) << endl;


	return 0;
}
