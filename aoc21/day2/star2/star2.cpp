
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string line;

	long horiz = 0;
	long depth = 0;
	long aim = 0;

	while (true)
	{
		string command;
		cin >> command;
		
		if (command.size() == 0)
			break;

		string dist_str;
		cin >> dist_str;
		int dist = stoi(dist_str);

		//cout << "Command: [" << command << "], " << "Dist: " << dist << endl;

		if (command == "forward")
		{
			horiz += dist;
			depth += aim * dist;
		}
		else if (command == "up")
		{
			aim -= dist;
		}
		else if (command == "down")
		{
			aim += dist;
		}

	}

	cout << "Horiz = " << horiz << ", Depth = " << depth << ", product = " << horiz * depth << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
