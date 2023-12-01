#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> wordDigits = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

int checkWordDigit(string input, int pos)
{
	for (int dig = 0; dig < 9; dig++)
	{
		string wordDigit = wordDigits[dig];
		if (wordDigit.length() + pos > input.length()) continue; //word digit is too long to fit in the string, so skip it. 

		if (input.substr(pos, wordDigit.length()) == wordDigit) return dig + 1;
	}
	return 0;
}


int main()
{
	string line;
	int total = 0;



	while (getline(cin, line))
	{
				
		int front = 0, back = 0;
		for (int i = 0; i < line.length(); i++)
		{
			if (!front && isdigit(line[i])) front = line[i] - '0';
			if (!back && isdigit(line[line.length() - i - 1])) back = line[line.length() - i - 1] - '0';

			int val;
			
			if (!front)
				if (val = checkWordDigit(line, i)) front = val;
			if (!back)
				if (val = checkWordDigit(line, line.length() - i - 1)) back = val;

		}
		cout << "Got " << front << back << endl;
		total += front * 10 + back;

		
	}

	cout << total << endl;
}

