// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class fish
{
	int timer;

public:
	fish(int timer) : timer(timer) {}

	void step()
	{
		if (--timer < 0)
		{
			timer = 6;
		}
	}
	
	bool isSpawning()
	{
		return timer == 0;
	}

	int getTimer()
	{
		return timer;
	}
};

int main()
{
    vector<fish> sea;
	int day = 0;
	
	string data;
	cin >> data;
	stringstream ss(data);

	string item;
	while (getline(ss, item, ','))
	{
		sea.emplace_back(stoi(item));
	}
	

	while (day != 80)
	{
		//check spawning
		int newFish = 0;
		for (fish& f : sea)
		{
			if (f.isSpawning())
			{
				newFish++;
			}
		}

		//step fish
		for (fish& f : sea)
		{
			f.step();
		}

		//add spawns
		for (int i = 0; i < newFish; i++)
		{
			sea.emplace_back(8);
		}

		++day;
		cout << "At the end of day " << day << " there are: " << sea.size() << " fish." << endl;
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
