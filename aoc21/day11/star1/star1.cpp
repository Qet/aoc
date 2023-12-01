#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct point
{
	point(int value) : v(value)
	{}
	int v;
	int hasFlashed = false;
};

typedef vector<vector<point>> data_t;

void printData(const data_t& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			cout << data[i][j].v;
		}
		cout << endl;
	}
}

void incrementAllEnergy(data_t& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			data[i][j].v++;
		}
	}
}

void incrementIfWithinBounds(data_t& data, int i, int j)
{
	if (i >= 0 && i < data.size() && j >= 0 && j < data[i].size())
		data[i][j].v++;
}

void incrementSurroundingEnergy(data_t& data, int i, int j)
{
	//N
	incrementIfWithinBounds(data, i - 1, j - 1);
	incrementIfWithinBounds(data, i - 1, j);
	incrementIfWithinBounds(data, i - 1, j + 1);

	//S
	incrementIfWithinBounds(data, i + 1, j - 1);
	incrementIfWithinBounds(data, i + 1, j);
	incrementIfWithinBounds(data, i + 1, j + 1);

	//W
	incrementIfWithinBounds(data, i, j - 1);

	//E
	incrementIfWithinBounds(data, i, j + 1);

}

void checkFlashes(data_t& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			if (data[i][j].v > 9 && !data[i][j].hasFlashed) //flash
			{
				data[i][j].hasFlashed = true;
				incrementSurroundingEnergy(data, i, j);
				checkFlashes(data);
			}
		}
	}
}

void step(data_t& data)
{
	incrementAllEnergy(data);
	checkFlashes(data);
}

int countAndZeroFlashes(data_t& data)
{
	int flashes = 0;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			if (data[i][j].hasFlashed)
			{
				flashes++;
				data[i][j].v = 0;
				data[i][j].hasFlashed = false;
			}
		}
	}
	return flashes;
}

int main()
{
	data_t data;
	string line;
	while (cin >> line && line.length() > 0)
	{
		vector<point> row;
		for (char c : line)
		{
			row.push_back(int(c - '0'));
		}
		data.push_back(row);
	}

	int flashes = 0;
	int stepNumber = 0;
	while(true)
	{
		step(data);
		stepNumber++;
		int stepFlashes = countAndZeroFlashes(data);
		flashes += stepFlashes;
		//cout << "After " << i << " steps, there have been a total of " << flashes << " flashes." << endl;
		//printData(data);
		if (stepFlashes == 100)
		{
			cout << "All octopuses flash, step " << stepNumber << endl;
			break;
		}
	}

	//cout << "After 100 steps, there have been a total of " << flashes << " flashes." << endl;
}

