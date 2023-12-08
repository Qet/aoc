#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>

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

vector<string> getStartingNodes()
{
	vector<string> startingNodes;
	for (auto& kv : nodeMap)
	{
		if (kv.first[2] == 'A') //a node that ends with A
		{
			startingNodes.push_back(kv.first);
		}
	}
	return startingNodes;
}

bool isNodeAtZ(string node)
{
	return node[2] == 'Z';
}

void traverseNodeMap(string cmd)
{
	vector<string> curNodes = getStartingNodes();
	vector<uint64_t> steps(curNodes.size(), 0);

	for (int n = 0; n < curNodes.size(); n++)
	{
		string node = curNodes[n];
		uint64_t stepCount = 0;
		while (true)
		{
			for (char c : cmd)
			{
				node = nodeMap[node].getLR(c);
				
				stepCount++;

				if (isNodeAtZ(node))
					goto nextnode;
			}
		}
	nextnode:
		steps[n] = stepCount;
	}

	uint64_t temp = 1;
		for (int n = 0; n < curNodes.size(); n++)
	{
		temp = lcm(temp, steps[n]);
		cout << steps[n] << ",";
	}

	cout << endl << temp << " steps total." << endl;
	
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

	traverseNodeMap(cmds);

}
