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

	for (int offset = 0; ;offset++)
	{
		string window = line.substr(offset, 4);
		if (hasNoDuplicateChars(window))
		{
			cout << "First marker after " << offset + 4 << " chars." << endl;
			break;
		}
	}

}