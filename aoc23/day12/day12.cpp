#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <list>
#include <cassert>
#include <thread>

using namespace std;

vector<int> parseCSVNums(string nums)
{
	stringstream ss = stringstream(nums);
	vector<int> vec;
	while (true)
	{
		int temp;
		ss >> temp;
		if (ss.fail())
			break;
		else
			vec.push_back(temp);
		char comma;
		ss >> comma;
	}
	return vec;
}

enum class ComboCheckResult
{
	VALID_COMPLETE,
	VALID_WITH_QNS,
	INVALID
};

struct Row
{
	list<string> combos;
	vector<int> code;

	void unfold()
	{
		string originalCombo = combos.back();
		vector<int> originalCode = code;
		for (int i = 0; i < 4; i++)
		{
			combos.back() += "?" + originalCombo;
			code.insert(code.end(), originalCode.begin(), originalCode.end());
		}
	}

	Row(string line)
	{
		int sp = line.find(' ');
		string hashLine = line.substr(0, sp);
		string codeLine = line.substr(sp + 1);
		code = parseCSVNums(codeLine);
		combos.push_back(hashLine);
	}

	ComboCheckResult codeCheck(string line, int pos, int len)
	{
		//check for a code at a position in the string
		string hashStr = line.substr(pos, len);
		bool hasQn = false;
		for (int i = pos; i < (pos + len); i++)
		{
			if (line[i] == '.')
				return ComboCheckResult::INVALID;
			if (line[i] == '?')
				hasQn = true;
		}
		if (line.length() >= (pos + len))
		{
			if (line[pos + len] == '#')
				return ComboCheckResult::INVALID;
			if (line[pos + len] == '?')
				hasQn = true;
		}

		if (hasQn)
		{
			return ComboCheckResult::VALID_WITH_QNS;
		}
		else if ((pos+len) <= line.length())
		{
			return ComboCheckResult::VALID_COMPLETE;
		}
		else
		{
			return ComboCheckResult::INVALID;
		}
		
	}

	ComboCheckResult getValidity(string line)
	{
		int pos = 0;
		const int sz = line.size();
		bool hasQn = line.find('?') != string::npos;
		for (int c : code)
		{
			bool codeFound = false;
			while (pos < sz && !codeFound)
			{
				if (line[pos] == '?')
					return ComboCheckResult::VALID_WITH_QNS;

				if (line[pos] != '.')
				{
					ComboCheckResult chk = codeCheck(line, pos, c);
					switch (chk)
					{
					case ComboCheckResult::INVALID:
						return chk;
					case ComboCheckResult::VALID_COMPLETE:
						pos += c;
						codeFound = true;
						break;
					case ComboCheckResult::VALID_WITH_QNS:
						return chk;
					}
				}
				pos++;
			}
			if (!codeFound)
				return ComboCheckResult::INVALID;
		}

		if (!hasQn && pos < sz)
		{
			string remainder = line.substr(pos);
			for (char c : remainder)
				if (c != '.')
					return ComboCheckResult::INVALID;
		}

		return hasQn ? ComboCheckResult::VALID_WITH_QNS : ComboCheckResult::VALID_COMPLETE;
	}

	void expand()
	{
		list<string>::const_iterator it = combos.begin();

		while (it != combos.end())
		{
			ComboCheckResult res = getValidity(*it);
			if (res == ComboCheckResult::VALID_WITH_QNS)
			{
				int qn = it->find('?');
				assert (qn != string::npos);
				
				//expand and add 2 combinations on the end of the list. 
				string comboDot = *it;
				string comboHash = *it;
				comboDot[qn] = '.';
				comboHash[qn] = '#';

				combos.push_back(comboDot);
				combos.push_back(comboHash);
				
				it = combos.erase(it); //this has been replaced by 2 more combos so can be erased. 

			}
			else if (res == ComboCheckResult::INVALID)
			{
				it = combos.erase(it); //prune this branch as it's invalid
			}
			else
			{
				++it;
			}
		}
	}

	void printCombos()
	{
		for (string l : combos)
		{
			cout << l << endl;
		}
	}
};


void doWork(Row& r)
{
	//part 2
	r.unfold();

	r.expand();


	//r.printCombos();
	//cout << "-------------------" << endl;
}


int main()
{
	vector<Row> rows;
	vector<thread> threads;
	string line;
	while (getline(cin, line))
	{
		rows.push_back(Row(line));
	}

	for (Row& r : rows)
	{
		threads.push_back(thread(doWork, ref(r)));
	}

	int tnum = 0;
	for (thread& t : threads)
	{
		t.join();
		cout << "thread " << ++tnum << " finished" << endl;
	}

	int rowComboSum = 0;
	int rowNum = 1;
	for (Row& r : rows)
	{
		cout << "Row " << rowNum << " combos: " << r.combos.size() << endl;
		rowComboSum += r.combos.size();
		rowNum++;
	}

	cout << "total combos: " << rowComboSum << endl;
	

}

