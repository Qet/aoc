// star1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

typedef tuple<int, int, int> coord;
typedef pair<int, int> range;

pair<int, int> rangeFromString(string data, int from, int to)
{
	int dd = data.find("..", from);
	return pair<int, int>{
		stoi(data.substr(from, dd - from)),
			stoi(data.substr(dd + 2, to - dd - 2))
	};
}

bool isOutsideInitRange(range r)
{
	return
		(r.first < -50 && r.second < -50) ||
		(r.first > 50 && r.second > 50);
}

int main()
{
	set<coord> oncubes;
	string onoff;
	string cubeoid;
	
	while (cin >> onoff && cin >> cubeoid)
	{
		cout << "Processing: " << cubeoid << endl;
		int xpos = cubeoid.find("x=");
		int ypos = cubeoid.find(",y=");
		int zpos = cubeoid.find(",z=");
		bool isOn = onoff == "on";

		pair<int, int> x = rangeFromString(cubeoid, xpos+2, ypos);
		pair<int, int> y = rangeFromString(cubeoid, ypos+3, zpos);
		pair<int, int> z = rangeFromString(cubeoid, zpos+3, cubeoid.length());

		if (!(isOutsideInitRange(x) || isOutsideInitRange(y) || isOutsideInitRange(z)))
		{
			for (int i = x.first; i <= x.second; i++)
			{
				for (int j = y.first; j <= y.second; j++)
				{
					for (int k = z.first; k <= z.second; k++)
					{
						if (isOn)
						{
							oncubes.insert(coord{ i,j,k });
						}
						else
						{
							oncubes.erase(coord{ i,j,k });
						}
					}
				}
			}
		}
	}

	cout << "On cubes: " << oncubes.size() << endl;
}

