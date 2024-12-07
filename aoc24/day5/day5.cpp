#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

typedef pair<int, int> pr;

vector<int> parseCSVNums(string nums)
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
		char comma;
		ss >> comma;
	}
	return vec;
}

//a row is a CSV row of values. 
//all rows default to not failed, but if a row fails a rule check, then
//the whole row is marked as failed. 
struct Row
{
	Row(vector<int> data) :
		data(data)
	{}

	vector<int> data;
	bool failed = false;

};

struct Rules
{
	vector<pr> rules;

	//for any rule a<b if the check pair is {b,a} then it fails the check. 
	bool rulePasses(pr rule, pr check)
	{
		if (check.second == rule.first && check.first == rule.second)
			return false;
		return true;
	}

	void processRuleLine(string line)
	{
		stringstream ss = stringstream(line);
		int a, b;
		ss >> a;
		char pipe;
		ss >> pipe;
		ss >> b;

		rules.push_back({ a, b });
	}
};

int main1()
{
	string line;
	Rules rules;
	vector<Row> rows;
	int total = 0;

	vector<string> pipes;
	vector<string> csvs;

	while (getline(cin, line))
	{
		if (line.find('|') != line.npos)
			pipes.push_back(line);
		else if (line.find(',') != line.npos)
			csvs.push_back(line);
	}

	for (string p : pipes)
		rules.processRuleLine(p);

	for (string c : csvs)
	{
		vector<int> data = parseCSVNums(c);
		rows.push_back({ data });
	}

	for (pr rule : rules.rules)
	{
		for (Row &row : rows)
		{
			if (!row.failed)
			{
				int maxA = INT_MIN;
				int minB = INT_MAX;

				for (int i = 0; i < row.data.size(); i++)
				{
					if (row.data[i] == rule.first && i > maxA)
						maxA = i;
					if (row.data[i] == rule.second && i < minB)
						minB = i;
				}

				if (maxA >= minB)
					row.failed = true;
			}
		}
	}

	for (const Row &row : rows)
	{
		if (!row.failed)
		{
			total += row.data[row.data.size() / 2];
		}
	}

	cout << "Part 1 total: " << total << endl;

	return 0;

}
