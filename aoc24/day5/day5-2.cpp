#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

typedef pair<int, int> pr;

list<int> parseCSVNums(string nums)
{
	stringstream ss = stringstream(nums);
	list<int> lis;
	while (true)
	{
		int temp;
		ss >> temp;
		if (ss.fail())
			break;
		else
			lis.push_back(temp);
		char comma;
		ss >> comma;
	}
	return lis;
}

//a row is a CSV row of values. 
//all rows default to not failed, but if a row fails a rule check, then
//the whole row is marked as failed. 
struct Row
{
	Row(list<int> data) :
		data(data)
	{}

	list<int> data;
	bool reordered = false;

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

int main()
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
		list<int> data = parseCSVNums(c);
		rows.push_back(data);
	}

	//this is essentially a bubble sort, so it's pretty slow. took about a minute to run I think. 
	bool stillReordering = true;
	while (stillReordering == true)
	{
		stillReordering = false;
		for (pr rule : rules.rules)
		{
			cout << "Rule: " << "{" << rule.first << ", " << rule.second << "}" << endl;
			for (Row& row : rows)
			{
				int maxA = INT_MIN;
				int minB = INT_MAX;
				list<int>::iterator minBit;

				int i = 0;
				for (auto it = row.data.begin(); it != row.data.end(); ++it)
				{
					if (*it == rule.first && i > maxA)
						maxA = i;
					if (*it == rule.second && i < minB)
					{
						minB = i;
						minBit = it;
					}

					i++;
				}

				list<list<int>::iterator> toMove;

				i = 0;
				for (auto it = row.data.begin(); it != row.data.end(); ++it)
				{
					if (*it == rule.first && i >= minB)
						toMove.push_back(it);

					i++;
				}

				for (auto it = toMove.begin(); it != toMove.end(); ++it)
				{
					row.data.insert(minBit, **it);
				}

				for (auto it = toMove.begin(); it != toMove.end(); ++it)
				{
					row.data.erase(*it);
					row.reordered = true;
					stillReordering = true;
				}
			}
		}
	}
	for (const Row& row : rows)
	{
		if (row.reordered)
		{
			auto it = row.data.begin();
			advance(it, row.data.size() / 2);
			total += *it;
		}
	}

	cout << "Part 2 total: " << total << endl;

}
