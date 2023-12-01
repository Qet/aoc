// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void printStats(const string& poly);

int main()
{
	string templ;
	cin >> templ;

	map<string, string> rules;
	
	string ruleL, ruleR, spacer;

	while (cin >> ruleL && cin >> spacer && cin >> ruleR)
	{
		rules.insert({ ruleL, ruleR });
	}

	string curPoly = templ;
	string nextPoly = "";
	for (int step = 1; step <= 10; step++)
	{
		uint64_t insertIndex = 1;
		for (uint64_t i = 0; i < curPoly.length() -1 ; i++)
		{
			string curPair = curPoly.substr(i, 2);
			nextPoly += curPair.substr(0, 1);
			if (rules.find(curPair) != rules.end())
			{
				nextPoly += rules[curPair];
			}
		}
		nextPoly += curPoly.substr(curPoly.size() - 1, 1);
			   		
		curPoly = nextPoly;
		nextPoly = "";

		cout << "End of step " << step << ", length of poly is: " << curPoly.length() << endl;
	}
	printStats(curPoly);
	return 0;
}

void printStats(const string& poly)
{
	map<char, uint64_t> counts;

	for (char c : poly)
	{
		if (counts.find(c) == counts.end())
		{
			counts[c] = 0;
		}

		counts[c]++;
	}

	uint64_t most = 0, least = UINT64_MAX;
	for (pair<char, uint64_t> item : counts)
	{
		if (item.second > most)
			most = item.second;
		if (item.second < least)
			least = item.second;
	}

	cout << "Most minus least = " << most - least << endl;
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
