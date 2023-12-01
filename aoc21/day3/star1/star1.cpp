// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<string> read_data()
{
	string line;
	vector<string> data;
	while (cin >> line && line.length() > 0)
	{
		data.push_back(line);
	}
	return data;
}

int main()
{
	vector<string> data;
	data = read_data();

	vector<int> sum_ones;
	int bitwidth = data[0].size();

	for (int i = 0; i < data[0].size(); i++)
	{
		sum_ones.push_back(0);
	}
	
	for (string s : data)
	{
		for (int i = 0; i < s.length(); i++)
		{
			char c = s.at(i);
			if (c == '1')
			{
				sum_ones[i]++;
			}
		}
	}

	int total = data.size();
	int half = total / 2;

	int shift = bitwidth - 1;
	int gamma = 0;
	int epsilon = 0;
	for (int col : sum_ones)
	{
		if (col >= half) //most common is ones. 
		{
			gamma += (1 << shift);
		}
		else //most common is zeroes.
		{
			epsilon += (1 << shift);
		}

		shift--;
	}

	cout << "gamma = " << gamma << ", epsilon = " << epsilon << ", product = " << gamma * epsilon;
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
