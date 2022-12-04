
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include <vector>

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

bool hasChar(string s, char c)
{
	return find(begin(s), end(s), c) != end(s);
}

vector<char> letters()
{
	vector<char> ret;
	for (char c = 'a'; c <= 'z'; c++)
		ret.push_back(c);
	for (char c = 'A'; c <= 'Z'; c++)
		ret.push_back(c);
	return ret;
}

int main()
{
	vector<string> lines;
	int sum{ 0 };
	bool moreLines{ true };

	while (moreLines)
	{
		lines.clear();
		for (int i = 0; i < 3; i++)
		{
			string line;
			if (getline(cin, line))
			{
				lines.push_back(line);
			}
			else
			{
				moreLines = false;
				break;
			}
		}

		for (char c: letters())
		{
			bool allHaveChar = lines.size() > 0;
			for (string s : lines)
			{
				allHaveChar &= hasChar(s, c);
			}

			if (allHaveChar)
			{
				sum += letterVal(c);
				break;
			}
		}

	}
	
	cout << "sum of badges across groups: " << sum << endl;
}