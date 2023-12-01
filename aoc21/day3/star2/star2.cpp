// star2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <bitset>

using namespace std;


list<string> read_data()
{
	string line;
	list<string> data;
	while (cin >> line && line.length() > 0)
	{
		data.push_back(line);
	}
	return data;
}

//Find the most common bit in a vector of data, at the index requested. 
//Equally common will return true, not false.   (true = 1, false = 0);
bool most_common_bit(const list<string>& data, int index)
{
	int sum_ones{ 0 };
		
	for (string s : data)
	{
		if (s.at(index) == '1')
		{
			sum_ones++;
		}
	}

	float total = data.size();
	float half = total / 2.0; 
	
	return sum_ones > (half-0.01); 
}

//remove all data matching this bit, at this index.
void remove_data(list<string>& data, int index, bool bit)
{
	int i = 0;
	auto it = data.begin();
	
	while(it != data.end())
	{
		if (
			(it->at(index) == '1' && bit) ||
			(it->at(index) == '0' && !bit)
			)
		{
			it = data.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void print_data(const list<string>& data)
{
	cout << "[";
	bool first = true;
	for (string s : data)
	{
		if (!first)
			cout << ",";

		cout << s;
		first = false;
	}
	cout << "]" << endl;
}

int binary_string_to_int(string val)
{
	return bitset<32>(val).to_ulong();
}

int main()
{
	list<string> data;
	list<string> data_co2;
	data = read_data();
	copy(data.begin(), data.end(), back_inserter(data_co2));

	int bitwidth = data.front().size();
	
	for (int i = 0; i < bitwidth; i++)
	{
		remove_data(data, i, !most_common_bit(data, i));
	}
	int oxy = binary_string_to_int(data.front());
	cout << "Oxygen: " << data.front() << " = " << oxy << endl;

	for (int i = 0; i < bitwidth; i++)
	{
		remove_data(data_co2, i, most_common_bit(data_co2, i));
		if (data_co2.size() == 1)
			break;
	}
	int co2 = binary_string_to_int(data_co2.front());
	cout << "CO2: " << data_co2.front() << " = " << co2 << endl;
			
	cout << "product = " << oxy * co2 << endl;
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
