
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isOpenBracket(char c)
{
	return
		c == '[' ||
		c == '{' ||
		c == '(' ||
		c == '<';
}

char getCloseFromOpenBracket(char c)
{
	if (c == '[')
		return ']';
	if (c == '{')
		return '}';
	if (c == '(')
		return ')';
	if (c == '<')
		return '>';
	return 0;
}

uint64_t getPoints(char c)
{
	switch (c)
	{
	case ')':
		return 1;
	case ']':
		return 2;
	case '}':
		return 3;
	case '>':
		return 4;
	default:
		return 0;
	}
}

int main()
{
	string line;
	vector<uint64_t> scores;
	int lineCount = 1;
	while (cin >> line && line.length() > 0)
	{
		stack<char> openBrackets;
		for (char c : line)
		{
			if (isOpenBracket(c))
			{
				openBrackets.push(c);
			}
			else
			{
				if (!openBrackets.empty() &&
					getCloseFromOpenBracket(openBrackets.top()) == c) //Then the close bracket matches the open one, all good. 
				{
					openBrackets.pop();
				}
				else //Corrupted line, drop line.
				{
					while (!openBrackets.empty())
						openBrackets.pop();
					break;
				}
			}
		}

		uint64_t lineScore = 0;
		//check line for incomplete chars
		if (!openBrackets.empty())
		{
			cout << "Line " << lineCount << " is incomplete, complete by adding: ";
			while (!openBrackets.empty())
			{
				char closingChar = getCloseFromOpenBracket(openBrackets.top());
				cout << closingChar;
				openBrackets.pop();

				lineScore *= 5;
				lineScore += getPoints(closingChar);
			}
			cout << ". Line score: " << lineScore << endl;
			scores.push_back(lineScore);
		}
		lineCount++;
	}
		
	sort(begin(scores), end(scores));
	cout << "middle score: " << scores[scores.size() / 2] << endl;

}

