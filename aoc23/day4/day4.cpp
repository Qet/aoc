#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric> 

using namespace std;

vector<int> parseNums(string nums)
{
	stringstream ss = stringstream(nums);
	vector<int> vec;
	while (true)
	{
		int temp;
		ss >> temp;
		if (ss.fail())
			break;
		else
			vec.push_back(temp);
	}
	return vec;
}


int main_part1()
{
	string line;

	int totalPoints = 0;

	while (getline(cin, line))
	{
		int p1 = line.find(':');
		int p2 = line.find('|');

		string winNums = line.substr(p1 + 1, p2 - p1 - 1);
		string scratchieNums = line.substr(p2 + 1);

		vector<int> vWin = parseNums(winNums);
		vector<int> vScratch = parseNums(scratchieNums);

		int wins = 0;

		for (int n : vScratch)
		{
			if (find(begin(vWin), end(vWin), n) != end(vWin))
			{
				wins++;
			}
		}

		int gameScore = wins > 0 ?
			pow(2, wins - 1) : 0; //wins [0, 1, 2, 3, ...] = score [0, 1, 2, 4, ...]

		totalPoints += gameScore;
	}

	cout << "Total score: " << totalPoints << endl;
	return 0;
}


//part 2
int main()
{
	string line;

	int totalCards = 0;

	
	vector<int> gameWins;

	while (getline(cin, line))
	{

		int p1 = line.find(':');
		int p2 = line.find('|');

		string winNums = line.substr(p1 + 1, p2 - p1 - 1);
		string scratchieNums = line.substr(p2 + 1);

		vector<int> vWin = parseNums(winNums);
		vector<int> vScratch = parseNums(scratchieNums);

		int wins = 0;

		for (int n : vScratch)
		{
			if (find(begin(vWin), end(vWin), n) != end(vWin))
			{
				wins++;
			}
		}

		gameWins.push_back(wins);
	}
	
	vector<uint64_t> cardCount(gameWins.size(), 1);
	for (int i = 0; i < gameWins.size(); i++)
	{
		int sc = gameWins[i];
		for (int j = i + 1; j < i + 1 + sc; j++)
		{
			cardCount[j] += cardCount[i]; //each following card will be incremented by the number of cards of the current game. 
		}
	}

	uint64_t sum = 0;
	for (uint64_t x : cardCount)
	{
		sum += x;
	}

	cout << "Total scratchies: " << sum << endl;

	return 0;
}