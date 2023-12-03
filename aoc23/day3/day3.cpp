#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

struct Num
{
	int row;
	int col;
	int val;
	int len;

	int rowStart()
	{
		return row - 1;
	}
	
	int rowEnd()
	{
		return row + 2;
	}

	int colStart()
	{
		return col - 1;
	}

	int colEnd()
	{
		return col + len + 1;
	}
};

struct Gear
{
	int row;
	int col;

	bool isAroundMe(int r, int c)
	{
		//check if coord (r,c) is within +/- 1 square of this
		return
			r >= row - 1 &&
			r <= row + 1 &&
			c >= col - 1 &&
			c <= col + 1;
	}

	int gearRatio(vector<Num> nums)
	{
		int mult = 1;
		int numGears = 0;
		for (Num num : nums)
		{
			for (int c = num.col; c < num.col + num.len; c++)
			{
				if (isAroundMe(num.row, c))
				{
					numGears++;
					mult *= num.val; //it's clearly a product, not a ratio...
					c = num.colEnd(); 
					continue;
				}
			}
		}
		if (numGears == 2)
			return mult;
		return 0;
	}
};

struct Grid{

	vector<string> data;

	void readLine(string line)
	{
		data.push_back(line);
	}

	bool isCoordValid(int row, int col)
	{
		return row >= 0 && col >= 0 && row < data.size() && col < data[0].length();
	}

	bool isSymbol(char c)
	{
		return !isdigit(c) && (c != '.');
	}

	vector<Num> getNumbers()
	{
		vector<Num> ret;

		for (int row = 0; row < data.size(); row++)
		{
			for (int col = 0; col < data[row].size(); col++)
			{
				char c = data[row][col];
				if (isdigit(c))
				{
					Num num;
					num.val = stoi(data[row].substr(col));
					num.len = to_string(num.val).length();
					num.row = row;
					num.col = col;
					ret.push_back(num);
					col += num.len - 1; //advance past the number just read. 
				}
			}
		}
		return ret;
	}

	vector<Gear> getGears()
	{
		vector<Gear> ret;

		for (int row = 0; row < data.size(); row++)
		{
			for (int col = 0; col < data[row].size(); col++)
			{
				char c = data[row][col];

				if (c == '*')
				{
					Gear gear;
					gear.row = row;
					gear.col = col;
					ret.push_back(gear);
				}
			}
		}
		return ret;
	}

	bool isNumberCounted(Num num)
	{
		for (int row = num.rowStart(); row < num.rowEnd(); row++)
		{
			for (int col = num.colStart(); col < num.colEnd(); col++)
			{
				if (isCoordValid(row, col) && isSymbol(data[row][col]))
				{
					return true;
				}
			}
		}
		return false;
	}

	int partNumberSum()
	{
		int sum = 0;
		vector<Num> nums = getNumbers();
		for (Num num : nums)
		{
			if (isNumberCounted(num)) {
				sum += num.val;
			}
		}
		return sum;
	}

	int gearRatioSum()
	{
		int sum = 0;
		vector<Num> nums = getNumbers();
		vector<Gear> gears = getGears();
		for (Gear g: gears)
		{
			sum += g.gearRatio(nums);
		}
		return sum;
	}

};


int main()
{
	Grid grid;
	string line;
	
	while (getline(cin, line))
	{
		grid.readLine(line);
	}

	//cout << "Sum: " << grid.partNumberSum() << endl;
	cout << "Sum: " << grid.gearRatioSum() << endl;
}
