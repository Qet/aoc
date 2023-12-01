
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
		cols(5, vector<int>()),
		bingoCalled(false)
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

	bool isFirstBingo()
	{
		if (isBingo() && !bingoCalled)
		{
			bingoCalled = true;
			return true;
		}
		return false;
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
	bool bingoCalled;

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
	int idraw;
	vector<int> bingoBoardOrder;
	while (getline(ss, draw, ','))
	{
		idraw = stoi(draw);

		for (board& b : boards)
		{
			b.draw(idraw);
		}

		for (int i = 0; i < boards.size(); i++)
		{
			if (boards[i].isFirstBingo())
			{
				bingoBoardOrder.push_back(i);
			}
		}

		if (bingoBoardOrder.size() == boards.size())
		{
			break;
		}
	}

	int score = boards[bingoBoardOrder.back()].sumUnmarked() * idraw;
	cout << "Star 2. Last board (board " << bingoBoardOrder.back() + 1 << ") score = " << score << endl;
}
