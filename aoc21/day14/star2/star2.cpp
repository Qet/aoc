#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef pair<char, char> poly;

class processing
{
	const map<poly, char>& rules;
	string templ;
	map<char, uint64_t> counts; 
	map<poly, uint64_t> curPolyCounts;
	map<poly, uint64_t> nextPolyCounts; 

public:

	void initialiseCounts()
	{
		for (char c = 'A'; c <= 'Z'; c++)
		{
			counts[c] = 0;
		}
	}

	void countInitialPolyChars()
	{
		for (unsigned int i = 0; i < templ.length(); i++)
		{
			char curItem = templ.substr(i, 1)[0];
			counts[curItem]++;
		}
	}

	void initialisePolyCounts()
	{
		for (unsigned int i = 0; i < templ.length() - 1; i++)
		{
			string curPair = templ.substr(i, 2);
			poly p{ curPair[0] , curPair[1] };
			addToPolyCount(curPolyCounts, p, 1);
		}
	}

	processing(const map<poly, char>& rules, string templ) : rules(rules), templ(templ)
	{
		initialiseCounts();
		countInitialPolyChars();
		initialisePolyCounts();
	}
	
	void addToPolyCount(map<poly, uint64_t>& polycounts, poly p, uint64_t amt)
	{
		if (polycounts.count(p) == 0)
			polycounts.insert({ p, amt });
		else
			polycounts[p]+= amt;
	}

	void go()
	{
		for (int level = 1; level <= 40; level++)
		{
			cout << "Starting level " << level << endl;
			for (auto currentPoly : curPolyCounts)
			{
				auto matchingRule = rules.find(currentPoly.first);
				if (matchingRule != rules.end())
				{
					counts[matchingRule->second] += currentPoly.second;
					poly polyL { currentPoly.first.first, matchingRule->second };
					poly polyR{ matchingRule->second, currentPoly.first.second };
					addToPolyCount(nextPolyCounts, polyL, currentPoly.second);
					addToPolyCount(nextPolyCounts, polyR, currentPoly.second);
				}
			}

			curPolyCounts = nextPolyCounts;
			nextPolyCounts.clear();
		}

	}

	void printResults()
	{
		uint64_t largest = 0, smallest = UINT64_MAX;
		for (pair<char, uint64_t> item : counts)
		{
			if (item.second > 0)
			{
				cout << "Letter " << item.first << " count: " << item.second << endl;
				if (item.second < smallest) 
					smallest = item.second;
				if (item.second > largest)
					largest = item.second;
			}
		}
		cout << "Largest minus smallest = " << (largest - smallest) << endl;
	}

};


int main()
{
	string templ;
	cin >> templ;

	map<poly, char> rules;

	string ruleL, ruleR, spacer;

	while (cin >> ruleL && cin >> spacer && cin >> ruleR)
	{
		rules.insert({ poly(ruleL[0], ruleL[1]) , ruleR[0] });
	}

	processing p(rules, templ);
	p.go();
	p.printResults();

}
