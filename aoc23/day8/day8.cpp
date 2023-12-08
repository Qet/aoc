#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


struct NodePair
{
	string L;
	string R;
	NodePair(string L, string R) : L(L), R(R) {}
	NodePair() {}
	string getLR(char LR)
	{
		return LR == 'L' ? L : R;
	}
};

map<string, NodePair> nodeMap;

int traverseNodeMap(string cmd)
{
	string curNode = "AAA";
	int stepCount = 0;
	while (true)
	{
		for (char c : cmd)
		{
			curNode = nodeMap[curNode].getLR(c);
			stepCount++;

			if (curNode == "ZZZ")
				return stepCount;
		}
	}
	return -1; //shouldn't happen...?!
}

int main()
{
	string cmds;
	getline(cin, cmds);
	
	string line;
	while (getline(cin, line))
	{
		string key = line.substr(0, 3);
		string L = line.substr(7, 3);
		string R = line.substr(12, 3);
		nodeMap[key] = NodePair(L, R);
	}

	cout << "Total steps to ZZZ: " << traverseNodeMap(cmds) << endl;

}
