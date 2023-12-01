
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>
#include <string>

using namespace std;

struct cave
{
	cave(string caveID) :
		caveID(caveID)
	{}

	string caveID;
	vector<shared_ptr<cave>> exits;
	bool isSmall = false;
};

map<string, shared_ptr<cave>> caves;
shared_ptr<cave> startCave;
shared_ptr<cave> endCave;

bool isCaveSmall(string caveID)
{
	for (char c : caveID)
	{
		if (tolower(c) != c)
			return false;
	}
	return true;
}

void addCaveIfDoesntExist(string caveID)
{
	if (caves.find(caveID) == caves.end())
	{
		shared_ptr<cave> newCave = make_shared<cave>(caveID);
		if (caveID == "start")
		{
			newCave->isSmall = true;
			startCave = newCave;
		}
		else if (caveID == "end")
		{
			newCave->isSmall = true;
			endCave = newCave;
		}
		else if (isCaveSmall(caveID))
		{
			newCave->isSmall = true;
		}
		
		caves.insert({ caveID, newCave });
	}
}

void linkCaves(string caveFromID, string caveToID)
{
	caves[caveFromID]->exits.push_back(caves[caveToID]);
	caves[caveToID]->exits.push_back(caves[caveFromID]);
}

typedef vector<shared_ptr<cave>> path;
vector<path> paths;

void searchPaths(path& curPath, shared_ptr<cave> curNode)
{
	if (curNode != endCave)
	{
		for (shared_ptr<cave> exit : curNode->exits)
		{
			if (!exit->isSmall ||
				(exit->isSmall &&
					find(begin(curPath), end(curPath), exit) == end(curPath)) //Haven't visited this small cave before.
				)
			{
				path newPath = curPath;
				newPath.push_back(exit);
				searchPaths(newPath, exit);
			}
		}
	}
	else
	{
		paths.push_back(curPath);
	}
}

void printPaths()
{
	cout << "Paths: " << endl;
	for (path p : paths)
	{
		for (shared_ptr<cave> c : p)
		{
			cout << c->caveID << ",";
		}
		cout << endl;
	}

	cout << "Total: " << paths.size() << " paths." << endl;
}

int main()
{
	string line;

	while (cin >> line && line.length() > 0)
	{
		int dash = line.find('-');
		string cavefrom = line.substr(0, dash);
		string caveto = line.substr(dash + 1);

		addCaveIfDoesntExist(cavefrom);
		addCaveIfDoesntExist(caveto);

		linkCaves(cavefrom, caveto);
	}

	shared_ptr<cave> curNode = startCave;
	path curPath;
	curPath.push_back(curNode);

	searchPaths(curPath, curNode);
	
	printPaths();
}

