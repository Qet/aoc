#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

//real data
const vector<int> bases{ 2, 17, 7, 11, 19, 5, 13, 3 }; //they're all prime. does that mean anything? maybe...

//test data
//const vector<int> bases{ 23, 19, 13, 17 };

enum class Op
{
	Plus,
	Times,
	Squared
};

struct Item
{
	Item(int startingWorry)
	{
		for (int b : bases)
		{
			worry[b] = (startingWorry % b);
		}
	}

	Item()
	{
		for (int b : bases)
		{
			worry[b] = 0;
		}
	}

	//for each item, we store the current base and remainder for each possible monkey's divisor, rather than storing the whole number, which would be too large. 
	map<int, int> worry; //key: base, value: remainder
	
	void operate(Op operation, int operand)
	{
		for (auto& w : worry)
		{
			int base = w.first;
			switch (operation) //monkey inspection
			{
			case Op::Plus:
				worry[base] = (worry[base] + operand) % base;
				break;
			case Op::Times:
				worry[base] = (worry[base] * operand) % base;
				break;
			case Op::Squared:
				//expansion of (r + b)^2, discarding b^2 as it doesn't change r  (where r = remainder, b = base)
				worry[base] = (worry[base] * worry[base] + 2 * worry[base] * operand) % base;
				break;
			}
		}
	}


};

struct Monkey
{
	list<Item> items;
	Op operation;
	int operand;
	int test;
	int monkeyTrue;
	int monkeyFalse;
	uint64_t inspectCount = 0;
	
	void inspectItems()
	{
		for (Item& item : items)
		{
			item.operate(operation, operand);
			inspectCount++;
		}
	}

	int checkThrowItem(Item& item)
	{
		return item.worry[test] == 0 ? monkeyTrue : monkeyFalse;
	}
};

struct Game
{
	//test data
	//vector<Monkey> monkeys =
	//{
	//{{79, 98}, Op::Times,19,23,2,3},
	//{{54, 65, 75, 74},Op::Plus,6,19,2,0},
	//{{79, 60, 97},Op::Squared,0,13,1,3,},
	//{{74},Op::Plus,3,17,0,1}
	//};

	////real data
	vector<Monkey> monkeys = {
		{{99, 63, 76, 93, 54, 73},Op::Times,11,2,7,1},
		{{91, 60, 97, 54},Op::Plus,1,17,3,2},
		{{65},Op::Plus,7,7,6,5},
		{{84, 55},Op::Plus,3,11,2,6},
		{{86, 63, 79, 54, 83},Op::Squared,0,19,7,0},
		{{96, 67, 56, 95, 64, 69, 96},Op::Plus,4,5,4,0},
		{{66, 94, 70, 93, 72, 67, 88, 51},Op::Times,5,13,4,5},
		{{59, 59, 74},Op::Plus,8,3,1,3}
	};

	void run()
	{
		for (int round = 1; round <= 10000; round++)
		{
			for (Monkey& m : monkeys)
			{
				m.inspectItems();
				while (m.items.size() > 0)
				{
					Item& curItem = m.items.front();
					int throwTo = m.checkThrowItem(curItem);
					monkeys[throwTo].items.push_back(curItem);
					m.items.pop_front();
				}
			}
			if (round == 1 || round == 20 || (round % 1000 == 0))
				print(round);
		}
	}

	void print(int round)
	{
		cout << "Round " << round << endl;
		for (int m = 0; m < monkeys.size(); m++)
		{
			cout << "Monkey " << m << ": ";
			cout << "[insp: " << monkeys[m].inspectCount << "] ";
			for (Item& i : monkeys[m].items)
			{
				cout << i.worry[monkeys[m].test] << ", ";
			}
			cout << endl;
		}
	}

	uint64_t monkeyBusiness()
	{
		vector<uint64_t> counts;
		for (Monkey& m : monkeys)
		{
			counts.push_back(m.inspectCount);
		}
		sort(begin(counts), end(counts), greater<uint64_t>());

		return counts[0] * counts[1];
	}
};

int main()
{
	Game game;
	game.run();

	cout << game.monkeyBusiness() << endl;

}
