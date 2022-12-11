#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct Item
{
	Item(uint64_t w) :
		worry(w)
	{}

	Item() :
		worry(0)
	{}

	uint64_t worry;

};

enum class Op
{
	Plus,
	Times,
	Squared
};

struct Monkey
{
	list<Item> items;
	Op operation;
	uint64_t operand;
	uint64_t test;
	int monkeyTrue;
	int monkeyFalse;
	int inspectCount = 0;

	uint64_t operate(uint64_t input)
	{
		uint64_t ret = 0;
		switch (operation) //monkey inspection
		{
		case Op::Plus:
			ret = input + operand;
			break;
		case Op::Times:
			ret = input * operand;
			break;
		case Op::Squared:
			ret = input * input;
			break;
		}

		ret /= 3;  //Monkey bored with item;

		return ret;
	}

	void inspectItems()
	{
		for (Item& item : items)
		{
			item.worry = operate(item.worry);
			inspectCount++;
		}
	}

	int checkThrowItem(Item& item)
	{
		return item.worry % test == 0 ? monkeyTrue : monkeyFalse;
	}
};

struct Game
{
	//test data
	/*vector<Monkey> monkeys =
	{
	{{79, 98}, Op::Times,19,23,2,3},
	{{54, 65, 75, 74},Op::Plus,6,19,2,0},
	{{79, 60, 97},Op::Squared,0,13,1,3,},
	{{74},Op::Plus,3,17,0,1}
	};*/

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
		for (int round = 1; round <= 20; round++)
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
			print(round);
		}
	}

	void print(int round)
	{
		cout << "Round " << round << endl;
		for (int m = 0; m < monkeys.size(); m++)
		{
			cout << "Monkey " << m << ": ";
			for (Item& i : monkeys[m].items)
			{
				cout << i.worry << ", ";
			}
			cout << endl;
		}
	}

	int monkeyBusiness()
	{
		vector<int> counts;
		for (Monkey& m : monkeys)
		{
			counts.push_back(m.inspectCount);
		}
		sort(begin(counts), end(counts), greater<int>());

		return counts[0] * counts[1];
	}
};

int main()
{
	Game game;
	game.run();

	cout << game.monkeyBusiness() << endl;

}
