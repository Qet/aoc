#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <sstream>

using namespace std;

list<string> parseData(string data)
{
	list<string> lis;
	size_t pos = 0;
	while (true)
	{
		size_t prev = pos;
		size_t space = data.find(' ', pos);
		if (space != string::npos)
		{
			pos = space + 1;
			lis.push_back(data.substr(prev, pos - prev - 1));
		}
		else
		{
			lis.push_back(data.substr(prev));
			break;
		}
	}
	return lis;
}

string trimLeadingZeroes(string in)
{
	int pos = 0;
	while (in[pos] == '0')
	{
		pos++;
	}
	if (in.substr(pos) == "")
		return "0";
	else
		return in.substr(pos);
}

void blink(list<string>& data)
{
	list<string>::iterator it = data.begin();
	while(it != data.end())
	{
		string curStr = *it;
		uint64_t curStrInt = stoull(curStr);
		if (curStrInt == 0)
		{
			it = data.erase(it);
			data.insert(it, "1");
		}
		else if (curStr.size() % 2 == 0)
		{
			it = data.erase(it);
			string l = curStr.substr(0, curStr.size() / 2);
			string r = curStr.substr(curStr.size() / 2);

			l = trimLeadingZeroes(l);
			r = trimLeadingZeroes(r);
			
			data.insert(it, l);
			data.insert(it, r);
		}
		else
		{
			it = data.erase(it);
			data.insert(it, to_string(curStrInt * 2024));
		}
		
	}
}

void print(list<string>& data)
{
	for (auto s : data)
	{
		cout << s << " ";
	}
	cout << endl;
}

int main()
{
	string input1 = "125 17";
	string input2 = "0 1 10 99 999";
	string input3 = "554735 45401 8434 0 188 7487525 77 7";

	string input = input3;

	list<string> d = parseData(input);

	for (int i = 0; i < 25; i++)
	{
		blink(d);
		cout << "Blink " << i << " completed." << endl;
	}

	cout << "Part 1 num stones after 25 blinks: " << d.size() << endl;

	return 0;
}
