#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <list>
#include <cassert>
#include <numeric>
#include <chrono>

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


struct Spring
{
	int pos;
	int len;
	int maxLen;

	void moveRight()
	{
		pos++;
	}

	bool atEnd()
	{
		return pos + len >= maxLen;
	}
};

struct Combo
{

	string str;
	int len;
	Combo() {}
	Combo(string cmb)
	{
		for (int i = 0; i < cmb.size(); i++)
		{
			if (cmb[i] == '.')
				dots.push_back(i);
			else if (cmb[i] == '#')
				hashes.push_back(i);
		}
		str = cmb;
		len = str.length();
	}

	vector<int> dots;
	vector<int> hashes;

	bool dotsValid(const Spring& spring)
	{
		for (int d : dots)
		{
			//if we have gone past the spring then no point checking the rest as they won't hit the spring. 
			if (d >= spring.pos + spring.len)
				break;

			if (spring.pos <= d)
			{
				if (spring.pos + spring.len > d)
					return false;
			}
		}

		return true;
	}


	bool hashesValid(const vector<Spring>& springs)
	{
		/*
		fail =
			hash not in a spring
		*/

		for (int h : hashes)
		{
			bool hashInSpring = false;

			for (const Spring& sp: springs)
			{
				if (sp.pos <= h)
				{
					if (sp.pos + sp.len > h)
					{
						hashInSpring = true;
						break;
					}
				}
			}
			
			if (!hashInSpring)
				return false;
		}

		return true;
	}

};

struct Row
{
	Combo combo;
	vector<int> code;
	int codeLen;

	void unfold()
	{
		string originalCombo = combo.str;
		string newCombo = originalCombo;
		vector<int> originalCode = code;
		for (int i = 0; i < 4; i++)
		{
			newCombo += "?" + originalCombo;
			code.insert(code.end(), originalCode.begin(), originalCode.end());
		}
		combo = Combo(newCombo);
	}

	Row(string line, string prepend, string append, bool unfoldLine)
	{
		int sp = line.find(' ');
		combo = Combo(prepend + line.substr(0, sp) + append);
		string codeLine = line.substr(sp + 1);
		code = parseCSVNums(codeLine);

		//part 2
		if (unfoldLine) unfold();

		//min length of the "train" of springs with one dot between them
		codeLen = accumulate(code.begin(), code.end(), code.size() - 1);

		initialise();
	}

	vector<Spring> springs;

	void initialise()
	{
		int offset = 0;
		for (int c : code)
		{
			Spring sp;
			sp.len = c;
			sp.pos = offset;
			springs.push_back(sp);
			offset += c + 1;
		}
		offset = combo.len;
		for (int i = springs.size() - 1; i >= 0; i--)
		{
			springs[i].maxLen = offset;
			offset -= (1 + springs[i].len);
		}

	}

	int validCodes = 0;

	void timeSampling()
	{
		if (checks % checksPerClockSample == 0)
		{
			auto tNow = chrono::system_clock::now();
			cout << (float)checks / chrono::duration_cast<chrono::seconds>(tNow - tStart).count() / 1e6 << " million checks/s" << endl;
		}
	}

	bool allSpringsAtEnd()
	{
		for (int i = 0; i < springs.size(); i++)
		{
			if (!springs[i].atEnd())
				return false;
		}
		return true;
	}

	int findRightMostSpringThatCanMove()
	{
		for (int i = springs.size() - 1; i >= 0; i--)
		{
			if (!springs[i].atEnd())
				return i;
		}
		return -1;
	}

	void pullRightSpringsBack(int rms)
	{
		if (rms < (springs.size() - 1))
		{
			for (int i = rms + 1; i < springs.size(); i++)
			{
				springs[i].pos = springs[i - 1].pos + springs[i - 1].len + 1;
			}
		}
	}

	bool bumpSpringsRight(int sp)
	{
		bool ret = false;
		for (int i = sp; i < springs.size(); i++)
		{
			if (!springs[i].atEnd())
			{
				springs[i].pos++;
				ret = true;
			}
		}
		return ret;
	}

	uint64_t checks = 0;
	uint64_t checksPerClockSample = 10000000;
	chrono::time_point<chrono::system_clock> tStart;

	void checkCode()
	{
		bool stillBumping = true;
		while (stillBumping)
		{
			stillBumping = false;
			//printCombo();
			bool allSpringsValid = true;
			for (int sp = 0; sp < springs.size(); sp++)
			{
				if (!combo.dotsValid(springs[sp]))
				{
					stillBumping = bumpSpringsRight(sp);
					allSpringsValid = false;
					break;
				}
				checks++;
			}
			if (allSpringsValid)
			{
				if (combo.hashesValid(springs))
					validCodes++;
				checks++;
			}
		}
		//timeSampling();
	}

	void scan()
	{
		tStart = chrono::system_clock::now();
		int curSpring = springs.size() - 1;
		
		checkCode();

		while (!allSpringsAtEnd())
		{
			int rms = findRightMostSpringThatCanMove();
			if (rms >= 0)
			{
				springs[rms].moveRight();
				if (rms != springs.size() - 1)
					pullRightSpringsBack(rms);
			}
			checkCode();
		} 
	}

	void print()
	{
		cout << validCodes << endl;
	}

	void printCombo()
	{
		for (const Spring& sp : springs)
		{
			cout << sp.pos << " ";
		}
		cout << endl;
		
	}

};



void calcValidCodes(vector<Row>& rows)
{
	for (Row& r : rows)
	{
		r.scan();
		//r.print();
	}
}




class MainCalcs
{
	string line;
	vector<string> lines;
	vector<Row> plainRows;
	vector<Row> qnStartRows;
	vector<Row> qnEndRows;
	vector<Row> qnDblRows;
	vector<Row> unfoldedRows;


public: 
	void init()
	{
		while (getline(cin, line))
		{
			lines.push_back(line);
		}

		for (string l : lines)
		{
			plainRows.push_back(Row(l, "", "", false));
			qnStartRows.push_back(Row(l, "?", "", false));
			qnEndRows.push_back(Row(l, "", "?", false));
			qnDblRows.push_back(Row(l, "?", "?", false));
			unfoldedRows.push_back(Row(l, "", "", true));
		}

		calcValidCodes(plainRows);
		calcValidCodes(qnStartRows);
		calcValidCodes(qnEndRows);
		calcValidCodes(qnDblRows);
	}

	
	int part1()
	{
		int validCodes = 0;
		for (Row& r : plainRows)
		{
			validCodes += r.validCodes;
		}
		return validCodes;
	}

	uint64_t part2()
	{
		uint64_t validCodes = 0;
		for (int i = 0; i < plainRows.size(); i++)
		{
			uint64_t firstVal = plainRows[i].validCodes;
			uint64_t otherVals = 0;
			//if ((plainRows[i].combo.str.back()) == '#')
			//	otherVals = qnEndRows[i].validCodes;
			//else
			//otherVals = max(qnEndRows[i].validCodes, qnStartRows[i].validCodes);
			otherVals = qnDblRows[i].validCodes;

			//validCodes += firstVal * powl(otherVals, 4);
			validCodes += powl(firstVal, 2) * powl(otherVals, 3);
		}
		return validCodes;
	}

};


int main()
{
	MainCalcs mc;
	mc.init();

	cout << "Part 1: " << mc.part1() << endl;
	cout << "Part 2: " << mc.part2() << endl;
}

