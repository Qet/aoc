#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <sstream>

using namespace std;

struct Data
{
	map<uint64_t, uint64_t> counts;

	void parseData(string toParse)
	{
		size_t pos = 0;
		while (true)
		{
			size_t prev = pos;
			size_t space = toParse.find(' ', pos);
			if (space != string::npos)
			{
				pos = space + 1;
				string temp = toParse.substr(prev, pos - prev - 1);
				int tempInt = stoi(temp);
				counts[tempInt]++;
			}
			else
			{
				string temp = toParse.substr(prev);
				int tempInt = stoi(temp);
				counts[tempInt]++;
				break;
			}
		}
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

	void blink()
	{
		
		map<uint64_t, uint64_t> newcounts;
		
		for (auto& [k, v] : counts)
		{
			string curStr = to_string(k);
			if (k == 0)
			{
				newcounts[1] += v;
				v = 0;
			}
			else if (curStr.size() % 2 == 0)
			{
				string l = curStr.substr(0, curStr.size() / 2);
				string r = curStr.substr(curStr.size() / 2);

				l = trimLeadingZeroes(l);
				r = trimLeadingZeroes(r);

				uint64_t il = stoull(l);
				uint64_t ir = stoull(r);

				newcounts[il] += v;
				newcounts[ir] += v;
				v = 0;
			}
			else
			{
				newcounts[k * 2024] += v;
				v = 0;
			}
		}

		for (auto [k, v] : newcounts)
		{
			counts[k] += v;
		}
		
		auto it = counts.begin();
		while(it != counts.end())
		{
			if (it->second == 0)
				it = counts.erase(it);
			else if (it != counts.end())
				++it;
			else
				break;
		}

	}

	void print()
	{
		for (auto [k, v] : counts)
		{
			cout << "(" << k << " x " << v << ") ";
		}
		cout << endl;
	}

	uint64_t size()
	{
		uint64_t ret = 0;
		for (auto [k, v] : counts)
		{
			ret += v;
		}
		return ret;
	}
};

int main()
{
	string input1 = "125 17";
	string input2 = "0 1 10 99 999";
	string input3 = "554735 45401 8434 0 188 7487525 77 7";

	string input = input3;

	Data data;

	data.parseData(input);

	for (int i = 0; i < 75; i++)
	{
		data.blink();
		//data.print();
		cout << "Blink " << i << " completed." << endl;
	}

	cout << "Part 2 num stones after 75 blinks: " << data.size() << endl;

	return 0;
}
