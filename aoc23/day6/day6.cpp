#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

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
	string strTime, strDist;
	getline(cin, strTime);
	getline(cin, strDist);

	vector<int> times = parseNums(strTime.substr(11));
	vector<int> dists = parseNums(strDist.substr(11));

	/*
	Total allowed time: t
	Button held for:	b
	Speed:				b
	Time boat moving:	t-b
	Distance travelled: b(t-b)
	*/

	
	int winProduct = 1;

	for (int i = 0; i < times.size(); i++)
	{
		int winCombinations = 0;
		int raceTime = times[i];
		int bestDistance = dists[i];

		for (int timeButtonHeld = 0; timeButtonHeld <= raceTime; timeButtonHeld++)
		{
			int timeBoatMoving = raceTime - timeButtonHeld;
			int distanceTravelled = timeBoatMoving * timeButtonHeld;
			if (distanceTravelled > bestDistance)
				winCombinations++;
		}

		winProduct *= winCombinations;
	}
	cout << "Win product: " << winProduct << endl;

	return 0;
}

int64_t getTrimmedNumber(string input)
{
	string ret;
	for (int64_t pos = 11; pos < input.size(); pos++)
	{
		if (input[pos] != ' ')
			ret += input[pos];
		
	}
	return stoll(ret);
}


int main()
{
	string strTime, strDist;
	getline(cin, strTime);
	getline(cin, strDist);

	int64_t raceTime = getTrimmedNumber(strTime);
	int64_t bestDistance = getTrimmedNumber(strDist);

	int64_t winCombinations = 0;

	for (int64_t timeButtonHeld = 0; timeButtonHeld <= raceTime; timeButtonHeld++)
	{
		int64_t timeBoatMoving = raceTime - timeButtonHeld;
		int64_t distanceTravelled = timeBoatMoving * timeButtonHeld;
		if (distanceTravelled > bestDistance)
			winCombinations++;
	}

	cout << "Win combinations: " << winCombinations << endl;

	return 0;
}
