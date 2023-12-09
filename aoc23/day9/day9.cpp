#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

using namespace std;

vector<int> parseNums(string nums)
{
	stringstream ss = stringstream(nums);
	vector<int> vec;
	while (true)
	{
		int temp;
		ss >> temp;
		if (ss.fail())
			break;
		else
			vec.push_back(temp);
	}
	return vec;
}

class Hist
{
	vector<vector<int>> data;

	bool finished()
	{
		const vector<int>& lastData = data.back();
		for (int d : lastData)
		{
			if (d != 0)
				return false;
		}
		return true;
	}

public: 
	Hist(string line)
	{
		data.push_back(parseNums(line));
	}
	Hist() {}

	void process()
	{
		while (!finished())
		{
			const vector<int>& lastData = data.back();
			vector<int> diffs;
			for (int i = 0; i < lastData.size() - 1; i++)
			{
				diffs.push_back(lastData[i + 1] - lastData[i]);
			}
			data.push_back(diffs);
		}
	}

	int nextValue()
	{
		int ret = 0;
		for (const vector<int>& d : data)
		{
			ret += d.back();
		}
		return ret;
	}

	int nextLeftValue()
	{
		bool firstVal = true;
		int ret = 0;
		bool neg = true;
		for (const vector<int>& d : data)
		{
			if (firstVal)
			{
				ret = d.front();
				firstVal = false;
			}
			else
			{
				//top-left value = a - (b - (c - (d ... )))
				//which expands to a - b + c - d + e - f ... (alternating sign)
				//where a, b, c, etc are the left-most values of each row
				ret += d.front() * (neg ? -1 : 1); 
				neg = !neg;
			}
		}
		return ret;
	}
};

int main()
{
	string line;
	
	vector<Hist> rows;

	while (getline(cin, line))
	{
		rows.push_back(line);
	}

	int valueSum = 0;
	int leftValueSum = 0;
	for (Hist& h : rows)
	{
		h.process();
		valueSum += h.nextValue();
		leftValueSum += h.nextLeftValue();
	}
	cout << valueSum << endl;
	cout << leftValueSum << endl;
}
