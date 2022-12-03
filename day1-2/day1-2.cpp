
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

	sort(elves.begin(), elves.end(), greater<int>());
	
	cout << "Sum of Top 3 elves = " << elves[0] + elves[1] + elves[2] << endl;
	

}

