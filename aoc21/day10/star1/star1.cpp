
#include <iostream>
#include <stack>
#include <string>

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

int getPoints(char c)
{
	switch (c)
	{
	case ')':
		return 3;
	case ']':
		return 57;
	case '}':
		return 1197;
	case '>':
		return 25137;
	default: 
		return 0;
	}
}

int main()
{
	string line;

	int filePoints = 0;
	while (cin >> line && line.length() > 0)
	{
		int linePoints = 0;
		stack<char> openBrackets;
		for (char c : line)
		{
			if (isOpenBracket(c))
			{
				openBrackets.push(c);
			}
			else
			{
				if (openBrackets.size() > 0 && 
					getCloseFromOpenBracket(openBrackets.top()) == c) //Then the close bracket matches the open one, all good. 
				{
					openBrackets.pop();
				}
				else //syntax error. 
				{
					cout << "Expected " << ((openBrackets.size() > 0) ? getCloseFromOpenBracket(openBrackets.top()) : '?') <<
						", but found " << c << " instead. " << getPoints(c) <<" points." << endl;
					linePoints += getPoints(c);
					break;
				}
			}
		}

		filePoints += linePoints;
	}

	cout << "Total file points: " << filePoints;
    
}

