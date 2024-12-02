#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;


//part 1
/*
int main()
{
	string line;
	int total = 0;
	
	vector<int> a;
	vector<int> b;

	while (getline(cin, line))
	{
		a.push_back(stoi(line));
		b.push_back(stoi(line.substr(line.find(' '))));

	}

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	
	for (int i = 0; i < a.size(); i++)
	{
		total += abs(a[i] - b[i]);
	}
	
	cout << "total dist: " << total << endl;

}
*/

int main()
{
	string line;
	int total = 0;

	vector<int> a;
	vector<int> b;

	while (getline(cin, line))
	{
		a.push_back(stoi(line));
		b.push_back(stoi(line.substr(line.find(' '))));

	}

	map<int, int> counts;
		
	for (int i = 0; i < a.size(); i++)
	{
		auto item = counts.find(b[i]);
		if (item != counts.end())
		{
			counts[item->first] += 1;
		}
		else
		{
			counts[b[i]] = 1;
		}
	}

	for (int i = 0; i < a.size(); i++)
	{
		total += a[i] * counts[a[i]];
	}

	cout << "Part 2 total: " << total << endl;
	

}