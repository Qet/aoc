
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int itemCals;
	vector<int> elves = { 0 };
	string line;
	while (getline(cin, line))
	{
		if (line == "")
		{
			elves.push_back(0);
		}
		else
		{
			elves.back() += stoi(line);
		}
	}

	cout << "Max calories = " << *max_element(elves.begin(), elves.end()) << endl;


}

