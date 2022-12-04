
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int letterVal(char letter)
{
	if (islower(letter))
	{
		return letter - 'a' + 1;
	}
	else
	{
		return letter - 'A' + 27;
	}
}


int main()
{
	string line;
	int sum{ 0 };
	
	while (getline(cin, line))
	{
		int halfLength = line.length() / 2;  //the lines are guaranteed to be an even number... we hope!
		string compartment1 = line.substr(0, halfLength);
		string compartment2 = line.substr(halfLength);

		for (char c : compartment1)
		{
			if (find(begin(compartment2), end(compartment2), c) != end(compartment2))
			{
				sum += letterVal(c);
				break;
			}
		}
	}

	cout << "sum of items in both compartments: " << sum << endl;
}