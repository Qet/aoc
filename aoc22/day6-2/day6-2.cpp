#include <iostream>
#include <string>
#include <map>

using namespace std;

bool hasNoDuplicateChars(string test)
{
	map<char, int> letterCounts;
	for (char c : test)
		letterCounts[c]++;

	for (const auto& item : letterCounts)
		if (item.second > 1)
			return false;

	return true;
}


int main()
{
	string line;
	getline(cin, line);
	const int WINDOW_SIZE = 14;

	for (int offset = 0; ; offset++)
	{
		string window = line.substr(offset, WINDOW_SIZE);
		if (hasNoDuplicateChars(window))
		{
			cout << "First **message marker** after " << offset + WINDOW_SIZE << " chars." << endl;
			break;
		}
	}

}