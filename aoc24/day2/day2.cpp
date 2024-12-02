// day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool isLineSafe(vector<int> line)
{
	int min = INT_MAX;
	int max = INT_MIN;

	for (int i = 0; i < line.size() - 1; i++)
	{
		int diff = line[i + 1] - line[i];
		if (diff < min)
			min = diff;
		if (diff > max)
			max = diff;
	}

	return (min >= 1 && max <= 3) || (min >= -3 && max <= -1);
}


vector<int> parseLine(string line)
{
	stringstream ss = stringstream(line);
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


void part1(vector<string> lines)
{
	int safeLines = 0;
	for(string line: lines)
	{
		auto v = parseLine(line);
		if (isLineSafe(v)) safeLines++;
	}

	cout << "Part 1, Total safe lines: " << safeLines << endl;
}


bool safeWithDampner(string line)
{
	auto v = parseLine(line);
	for (int pos = 0; pos < v.size(); pos++)
	{
		vector<int> variant;
		for (int j = 0; j < v.size(); j++)
		{
			if (pos != j)
				variant.push_back(v[j]);
		}
		if (isLineSafe(variant))
			return true;
	}

	return false;
}

void part2(vector<string> lines)
{
	int safeLines = 0;
	for (string line : lines)
	{
		if (safeWithDampner(line)) safeLines++;
	}

	cout << "Part 2, Total safe lines: " << safeLines << endl;

}

int main()
{
	vector<string> lines;
	string line;
	while (getline(cin, line))
	{
		lines.push_back(line);
	}

	part1(lines);
	part2(lines);

}
