// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct point{

	vector<int> adjacent_points;
	int value;

	bool isLowPoint()
	{
		for (int aj : adjacent_points)
		{
			if (aj <= value)
				return false;
		}
		return true;
	}

	int risk()
	{
		return value + 1;
	}
};

int main()
{
	string line;
	int rowCount = 0;
	vector<vector<int>> data;
	while (cin >> line && line.length() > 0)
	{
		vector<int> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		data.push_back(row);
	}
	
	vector<point> points;

	for (int row = 0; row < data.size(); row++)
	{
		for (int col = 0; col < data[row].size(); col++)
		{
			point p;
			p.value = data[row][col];

			//up
			if (row - 1 >= 0)
			{
				p.adjacent_points.push_back(data[row - 1][col]);
			}

			//down
			if (row + 1 < data.size())
			{
				p.adjacent_points.push_back(data[row + 1][col]);
			}

			//left
			if (col - 1 >= 0)
			{
				p.adjacent_points.push_back(data[row][col - 1]);
			}

			//right
			if (col + 1 < data[row].size())
			{
				p.adjacent_points.push_back(data[row][col + 1]);
			}

			points.push_back(p);
		}
	}

	int total_risk = 0;
	for (point p : points)
	{
		if (p.isLowPoint())
		{
			cout << "Low point risk: " << p.risk() << endl;
			total_risk += p.risk();
		}
	}

	cout << "Total risk: " << total_risk << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
