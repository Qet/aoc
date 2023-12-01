
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
	bool isStartCave = false;
};

map<string, shared_ptr<cave>> caves;
shared_ptr<cave> startCave;
shared_ptr<cave> endCave;

typedef vector<shared_ptr<cave>> path;
vector<path> paths;
path smallCaves;

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
			newCave->isStartCave = true;
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
			smallCaves.push_back(newCave);
		}

		caves.insert({ caveID, newCave });
	}
}

void linkCaves(string caveFromID, string caveToID)
{
	caves[caveFromID]->exits.push_back(caves[caveToID]);
	caves[caveToID]->exits.push_back(caves[caveFromID]);
}



bool haveVisitedASmallCaveTwice(path& curPath)
{
	for (shared_ptr<cave> c : smallCaves)
	{
		if (count(begin(curPath), end(curPath), c) == 2)
			return true;
	}
	return false;
}

bool haveVisitedThisSmallCave(path& curPath, shared_ptr<cave> curNode)
{
	return count(begin(curPath), end(curPath), curNode) > 0;
}

void searchPaths(path& curPath, shared_ptr<cave> curNode)
{
	if (curNode != endCave)
	{
		for (shared_ptr<cave> exit : curNode->exits)
		{
			if (!exit->isStartCave)
			{
				if (!exit->isSmall ||  //if it's big, or
					(exit->isSmall && !haveVisitedThisSmallCave(curPath, exit)) || //if it's small, and I haven't visited it, or
					(exit->isSmall && !haveVisitedASmallCaveTwice(curPath))  //if it's small (and I haven't visited it), and I haven't visited a small cave twice yet. 
					)
				{
					path newPath = curPath;
					newPath.push_back(exit);
					//cout << exit->caveID << " ";
					searchPaths(newPath, exit);
				}
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
	//cout << "Paths: " << endl;
	//for (path p : paths)
	//{
	//	for (shared_ptr<cave> c : p)
	//	{
	//		cout << c->caveID << ",";
	//	}
	//	cout << endl;
	//}

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

