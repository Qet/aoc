#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool endOfStackSection(string line)
{
	return line.substr(0, 3) == " 1 ";
}

// Position
//01234567890123456789012345678901234
// 1   2   3   4   5   6   7   8   9 
//1, 5, 9, 13, ... 
//Stack N, Offset 4N + 1  (0-based stack number and offset).


int main()
{
	const int MAX_STACKS = 9;
	string line;
	vector<vector<char>> stacks{ MAX_STACKS }; //A vector of default-constructed char vectors. 
	int lineNo = 0;

	//Process crate stack positions
	while (getline(cin, line))
	{
		lineNo++;
		if (endOfStackSection(line))
		{
			getline(cin, line); //skip over the single blank line between crates and moves.
			break;
		}

		for (int stack = 0; stack < MAX_STACKS; stack++)
		{
			int offset = 4 * stack + 1;
			if (offset >= line.length())
				break;  //break if we've processed all the stacks for this line. 

			if (line[offset] != ' ')
			{
				stacks[stack].insert(begin(stacks[stack]), line[offset]);  //insert crate at start of vector to preserve correct stack order.
			}
		}


	}

	//Process moves
	while (true)
	{
		lineNo++;

		//e.g.: move 7 from 3 to 9
		string ignore;
		int qty, from, to;
		cin >> ignore >> qty >> ignore >> from >> ignore >> to;

		if (cin.eof())
			break;

		from--;
		to--;
		
		//Could have used this solution with a reverse iterator on star 1. 
		stacks[to].insert(end(stacks[to]), end(stacks[from]) - qty, end(stacks[from]));
		stacks[from].erase(end(stacks[from]) - qty, end(stacks[from]));

	}

	//Get top of stacks string
	string tops = "";
	for (auto s : stacks)
	{
		if (s.size() > 0)
		{
			tops += s.back();
		}
	}

	cout << "Top of stacks string: " << tops << endl;;

}
