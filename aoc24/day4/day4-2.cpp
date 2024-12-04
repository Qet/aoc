#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct grid
{
	const vector<vector<char>>& data;
	int rows;
	int cols;

	grid(const vector<vector<char>>& data) :
		data(data)
	{
		rows = data.size();
		cols = data[0].size();
	}

	bool inRange(int r, int c)
	{
		return r >= 0 && c >= 0 && r < rows && c < cols;
	}

	bool inXmasRange(int r, int c)
	{
		return r >= 1 && c >= 1 && r < rows-1 && c < cols-1;
	}


	bool hasXmas(int r, int c)
	{
		if (!inXmasRange(r, c)) return false;

		//the "mas x mas" shape can be rotated into 4 positions
		if (data[r][c] != 'A') return false;

		//L-R MAS
		if (data[r - 1][c - 1] == 'M' && data[r + 1][c - 1] == 'M' &&
			data[r - 1][c + 1] == 'S' && data[r + 1][c + 1] == 'S') return true;

		//L-R SAM
		if (data[r - 1][c - 1] == 'S' && data[r + 1][c - 1] == 'S' &&
			data[r - 1][c + 1] == 'M' && data[r + 1][c + 1] == 'M') return true;
		
		//T-B MAS
		if (data[r - 1][c - 1] == 'M' && data[r - 1][c + 1] == 'M' &&
			data[r + 1][c - 1] == 'S' && data[r + 1][c + 1] == 'S') return true;

		//T-B SAM
		if (data[r - 1][c - 1] == 'S' && data[r - 1][c + 1] == 'S' &&
			data[r + 1][c - 1] == 'M' && data[r + 1][c + 1] == 'M') return true;

		return false;
	}

	int countXmases()
	{
		int count = 0;

		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (hasXmas(r, c)) count++;
			}
		}
		return count;
	}

};



int main()
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

	grid g(data);

	cout << "Part 2 num xmases: " << g.countXmases() << endl;

}
