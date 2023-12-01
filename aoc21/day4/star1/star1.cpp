
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class board
{
public: 
	board(const vector<int>& data) :
		rows(5, vector<int>()),
		cols(5, vector<int>())
	{
		int row = 0, col = 0;
		for (int d : data)
		{
			rows[row].push_back(d);
			cols[col].push_back(d);

			col++;
			if (col == 5)
			{
				col = 0;
				row++;
			}
		}
	}

	void draw(int val)
	{
		removeMatching(rows, val);
		removeMatching(cols, val);
	}

	bool isBingo()
	{
		return
			hasEmptyVec(rows) ||
			hasEmptyVec(cols);
	}

	int sumUnmarked()
	{
		int sum = 0;
		for (vector<int> row : rows)
		{
			for (int item : row)
			{
				sum += item;
			}
		}
		return sum;
	}

private: 
	vector<vector<int>> rows;
	vector<vector<int>> cols;

	void removeMatching(vector<vector<int>>& vecs, int val)
	{
		for (vector<int>& row : vecs)
		{
			for (auto it = row.begin(); it != row.end(); ++it)
			{
				if (*it == val)
				{
					row.erase(it);  //invalidates the iterator, but we only need to remove the first element found. 
					break;
				}
			}
		}
	}

	bool hasEmptyVec(vector<vector<int>>& vecs)
	{
		for (vector<int> row : vecs)
		{
			if (row.size() == 0)
			{
				return true;
			}
		}
		return false;
	}

};


int main()
{
	string draws;
	cin >> draws;

	vector<int> data;
	vector<board> boards;
	string s;
	while (cin >> s && s.length() > 0)
	{
		data.push_back(stoi(s));

		if (data.size() == 25)
		{
			boards.emplace_back(data);
			data.clear();
		}
	}

	stringstream ss(draws);
	
	string draw;
	while (getline(ss, draw, ','))
	{
		int idraw = stoi(draw);

		for (board &b : boards)
		{
			b.draw(idraw);
			if (b.isBingo())
			{
				int score = b.sumUnmarked() * idraw;
				cout << "Star 1: Bingo!! " << score << endl;
				return 0;
			}
		}


	}
	

}
