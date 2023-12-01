// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> get_data()
{
	string data;
	cin >> data;
	stringstream ss(data);

	string item;
	vector<int> seeds;
	while (getline(ss, item, ','))
	{
		seeds.emplace_back(stoi(item));
	}

	return seeds;
}

//star 1
int calc_fuel(const vector<int>& data, int pos)
{
	int fuel = 0;
	for (int d : data)
	{
		fuel += abs(d - pos);
	}
	return fuel;
}

//star 2
int calc_fuel2(const vector<int>& data, int pos)
{
	int fuel = 0;
	for (int d : data)
	{
		int steps = abs(d - pos);
		int this_crabs_fuel = (1 + steps) * steps / 2;  //divide by 2 last - it will divide evenly as n(n+1) is even.
		fuel += this_crabs_fuel;
	}
	return fuel;
}


int main()
{
	vector<int> data = get_data();

	int min_fuel = INT_MAX;
	int min_pos = 0;
	int data_min = *min_element(begin(data), end(data));
	int data_max = *max_element(begin(data), end(data));
	
	for (int i = data_min; i <= data_max; i++)
	{
		int this_fuel = calc_fuel2(data, i);
		if (this_fuel < min_fuel)
		{
			min_pos = i;
			min_fuel = this_fuel;
		}
	}

	cout << "Min fuel position: " << min_pos << " using " << min_fuel << " fuel." << endl;

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
