#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

enum class EnabledResult
{
	TRUE, 
	FALSE, 
	NO_CHANGE
};

EnabledResult isMulEnabled(string line, size_t mulpos)
{
	size_t pdo = line.rfind("do()", mulpos);
	size_t pdont = line.rfind("don't()", mulpos);

	if (pdo == string::npos && pdont == string::npos) return EnabledResult::NO_CHANGE; 
	if (pdo == string::npos) return EnabledResult::FALSE;
	if (pdont == string::npos) return EnabledResult::TRUE;

	return pdo > pdont ? EnabledResult::TRUE : EnabledResult::FALSE;

}

struct LineResult
{
	LineResult(int val, EnabledResult status) : val(val), status(status) {}
	int val;
	EnabledResult status;
};

LineResult processLine2(string line, EnabledResult lastEnableStatus)
{
	int total = 0;

	size_t start = 0;
	size_t end = 0;

	EnabledResult curEnableStatus{ lastEnableStatus };

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

		auto res = isMulEnabled(line, start);
		if (res != EnabledResult::NO_CHANGE)
			curEnableStatus = res;

		if (m > 0 && curEnableStatus == EnabledResult::TRUE)
			total += m;
	}

	return { total, curEnableStatus };
}

int main()
{
	string line;

	int total1 = 0;
	int total2 = 0;
	EnabledResult enabledStatus = EnabledResult::TRUE; 
	while (getline(cin, line))
	{
		total1 += processLine(line);
		LineResult res = processLine2(line, enabledStatus);
		total2 += res.val;
		enabledStatus = res.status;
	}

	cout << "Part 1 total: " << total1 << endl;
	cout << "Part 2 total: " << total2 << endl;
}
