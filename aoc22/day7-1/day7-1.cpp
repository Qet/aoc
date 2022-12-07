// day7-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>

using namespace std;

struct Node
{
	Node(string name, bool isDir, int size):
		Node(name, isDir, size, nullptr)
	{}

	Node(string name, bool isDir, int size, shared_ptr<Node> parent) :
		name(name),
		isDir(isDir),
		size(size),
		parent(parent)
	{}

	bool isDir;
	string name;
	int size;
	map<string, shared_ptr<Node>> list;
	shared_ptr<Node> parent;

	void print(int level)
	{
		cout << string(level, ' ');
		cout << "- " << name << " ";
		if (isDir)
			cout << "(dir)";
		else
			cout << "(file, size=" << size << ")";
		cout << endl;
		for (auto& item : list)
		{
			item.second->print(level + 1);
		}
	}

	void calcSize()
	{
		if (isDir)
		{
			//Calculate size of all children item (including subdirs recursively)
			for (auto& item : list)
			{
				item.second->calcSize();
			}

			//Add up the sizes once that is done. 
			for (auto& item : list)
			{
				size += item.second->size;
			}
		}
		//If its a file then the size will have already been constructed with the correct value so no more needs to be done. 
	}

	int sum100kDirs(int currentSum)
	{
		//Calculate the sum of all dirs with a size of <= 100,000.
		if (isDir && size <= 100000)
		{
			currentSum += size;
		}

		for (auto& item : list)
		{
			currentSum = item.second->sum100kDirs(currentSum);
		}
		
		return currentSum;
	}
};



int main()
{
	string line;

	shared_ptr<Node> root = make_shared<Node>("/", true, 0);
	root->parent = root; 
	shared_ptr<Node> curDir = root;

	while (getline(cin, line))
	{
		if (line.substr(0, 4) == "$ cd")
		{
			string changeTo = line.substr(5);

			if (changeTo == "/")
			{
				curDir = root;
			}
			else if (changeTo == "..")
			{
				curDir = curDir->parent;
			}
			else
			{
				curDir = curDir->list[changeTo];
			}
		}
		else if (line.substr(0, 4) == "$ ls")
		{
			while (cin.peek() != (int)('$'))
			{
				string file;
				getline(cin, file);
				if (cin.eof())
					break;

				string fileName = file.substr(file.find(' ') + 1);
				string filePrefix = file.substr(0, file.find(' '));
				if (filePrefix == "dir")
				{
					curDir->list[fileName] = make_shared<Node>(fileName, true, 0, curDir);
				}
				else
				{
					curDir->list[fileName] = make_shared<Node>(fileName, false, stoi(filePrefix), curDir);
				}
			}
		}
	}

	//root->print(0);
	root->calcSize();
	cout << root->sum100kDirs(0);

}
