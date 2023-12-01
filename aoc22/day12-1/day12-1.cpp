#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <limits>
#include <list>

using namespace std;

enum class NodeType
{
	Start,
	End,
	Normal
};

struct Node
{
	Node(char h)
	{
		if (h == 'S')
		{
			nodetype = NodeType::Start;
			h = 'a';
		}
		else if (h == 'E')
		{
			nodetype = NodeType::End;
			h = 'z';
		}
		else
		{
			nodetype = NodeType::Normal;
		}

		height = h - 'a';
	}

	vector<Node*> exits;
	int height;
	NodeType nodetype;
	int dist = INT_MAX;
	Node* bestNode = nullptr;
	coord coords;

	bool hasBestNode()
	{
		return bestNode != nullptr;
	}

	bool isOtherBetter(Node* other)
	{
		return other->hasBestNode() && other->dist < dist;
	}

	void setBestNode(Node* best)
	{
		bestNode = best;
		dist = best->dist + 1; //distance between all adjacent nodes is 1. 
	}
	
};

typedef pair<int, int> coord;

static coord operator-(const coord& first, const coord& second)
{
	return make_pair(first.first - second.first, first.second - second.second);
}

struct Game
{

	vector<vector<unique_ptr<Node>>> grid;
		
	Node* startNode;
	Node* endNode;
	   
	int rows{}, cols{};

	void readgrid()
	{
		int row = 0;
		string line;
		while (getline(cin, line))
		{
			int col = 0;
			cols = line.size();
			grid.push_back(vector<unique_ptr<Node>>());
			for (char c : line)
			{
				grid[row].push_back(make_unique<Node>(c));
				grid[row].back()->coords = make_pair(row, col);
				if (c == 'S')
					startNode = grid[row].back().get();
				else if (c == 'E')
					endNode = grid[row].back().get();
				col++;
			}
			row++;
		}
		rows = row;
	}

	bool validCoords(int r, int c)
	{
		return r >= 0 && r < rows && c >= 0 && c < cols;
	}

	bool reachableNode(unique_ptr<Node>& me, unique_ptr<Node>& other)
	{
		return abs(other->height - me->height) <= 1; //max climbing distance up or down is 1. 
	}

	void linkExits()
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				unique_ptr<Node>& curNode = grid[r][c];
								
				vector<pair<int, int>> pts{ {0, -1},{0, 1},	{1, 0},	{-1, 0} }; //find all the chars surrounding the current node that are within [-1,1] of the current node's height.
				
				for (auto& p : pts)
				{
					int i = p.first + r;
					int j = p.second + c;
					if (validCoords(i, j) && reachableNode(curNode, grid[i][j]))
					{
						curNode->exits.push_back(grid[i][j].get());
					}
				}
			}
		}
	}

	void calcDists(Node* curNode, vector<Node*>& visited)
	{
		for (Node* n : curNode->exits)
		{
			if (n->isOtherBetter(curNode))
			{
				n->setBestNode(curNode);
			}
		}

		visited.push_back(curNode);

		for (Node* n : curNode->exits)
		{
			if (find(begin(visited), end(visited), n) == end(visited))
			{
				calcDists(n, visited);
			}
		}
	}

	void printDirs()
	{
		for(auto& row: grid)
		{
			for (unique_ptr<Node>& node : row)
			{
				coord d = node->bestNode->coords - node->coords;
				
			}
		}
	}

	Game()
	{
		readgrid();
		linkExits();
		endNode->dist = 0;
		endNode->bestNode = endNode;
		vector<Node*> visited;
		calcDists(endNode, visited);
	}

};


int main()
{
	Game game;

}
