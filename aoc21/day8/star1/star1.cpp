// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void process_outputs(const vector<string>& outputs)
{
	//digits:   1, 4, 7, 8
	//segments: 2, 4, 3, 7

	int count = 0;

	for (string s : outputs)
	{
		if (s.size() == 2 ||
			s.size() == 4 ||
			s.size() == 3 ||
			s.size() == 7)
		{
			count++;
		}
	}
	cout << "Digits 1,4,7 or 8 appear " << count << " times.";
}

int main()
{
	string input;
	string line;

	vector<string> signals;
	vector<string> outputs;
	
	while (getline(cin, line))
	{
		stringstream linestream{ line };
		for (int i = 0; i < 10; i++)
		{
			linestream >> input;
			signals.push_back(input);
		}
		linestream >> input; //skip pipe

		for (int i = 0; i < 4; i++)
		{
			linestream >> input;
			outputs.push_back(input);
		}

	}
	process_outputs(outputs);
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
