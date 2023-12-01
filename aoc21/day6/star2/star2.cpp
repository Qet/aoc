// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

static const int MAX_DAY = 255;
static const int DAY_VECTOR_SIZE = MAX_DAY + 20;

struct day 
{
	uint64_t zeroes{ 0 };
	uint64_t eights{ 0 };
	uint64_t sixes{ 0 };
	int day_num{ 0 };
	
	uint64_t total{ 0 };

	void updateTotal(uint64_t previousTotal)
	{
		total = previousTotal + eights + sixes - zeroes;
	}
};

static vector<day> days(DAY_VECTOR_SIZE);

void initialise_days()
{
	for (int i = 0; i < days.size(); i++)
		days[i].day_num = i - 8;
}

vector<int> get_seeds() {

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

void load_seeds(const vector<int>& seeds)
{
	for (int seed : seeds)
	{
		days[seed].eights++;
	}
}

void spawn(int d, uint64_t count);

void spawn_for_day(int d)
{
	if (days[d].eights > 0)
	{
		spawn(d + 9, days[d].eights);
	}

	if (days[d].sixes > 0)
	{
		spawn(d + 7, days[d].sixes);
	}
}

void spawn(int d, uint64_t count)
{
	days[d].eights += count;
	days[d].sixes += count;
	days[d].zeroes += count;
}

int main()
{
	initialise_days();
	vector<int> seeds = get_seeds();
	load_seeds(seeds);

	uint64_t previous_total = 0;
	for (int d = 0; d < MAX_DAY + 10; d++)
	{
		spawn_for_day(d);
		days[d].updateTotal(previous_total);
		previous_total = days[d].total;

		cout << "At the end of day " << days[d].day_num << " there are: " << days[d].total << " fish." << endl;
	}
		   
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
