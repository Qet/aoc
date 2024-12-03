#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> parseNums(string nums)
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


int calcMul(string data)
{

	for(char c: data)
	{
		if (!isdigit(c) && c != ',') //invalid mul function - non-digit or comma 
			return 0; 
	}

	size_t comma = data.find(',');

	if (comma == data.npos)
		return 0; //invalid - no comma found. 

	stringstream ss = stringstream(data);
	int a;
	ss >> a;
	if (ss.fail())
		return 0;
	char expectcomma;
	ss >> expectcomma;
	int b;
	ss >> b;
	if (ss.fail())
		return 0;

	if (a > 999 || b > 999) //invalid - more than 3 digits
		return 0;

	return a * b;
	
}


int processLine(string line)
{
	int total = 0;

	size_t start = 0;
	size_t end = 0;

	while (true)
	{
		start = line.find("mul(", start);
		if (start == line.npos)
			break; //didn't find a mul, so this string is finished. 
		start += 4; //shift to start of contents of brackets

		end = line.find(")", start);
		if (end == line.npos)
			continue; //couldn't find a closing bracket, so skip this mul. 

		int m = calcMul(line.substr(start, end - start));
		if (m > 0)
			total += m;

	}

	return total;

}


int main()
{
	string line;

	int total = 0;
	while (getline(cin, line))
	{
		total += processLine(line);
	}

	cout << "Part 1 total: " << total << endl;
}
