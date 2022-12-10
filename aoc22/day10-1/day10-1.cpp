#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

int main()
{
	string line;
	int curCycle = 1;
	int x = 1;
	int delay = 0;
	map<int, int> futureAdds; //key: cycle, value: add
	
	map<int, int> cycleXValues;

	while (true)
	{
		x += futureAdds[curCycle];
		cycleXValues[curCycle] = x;
		delay--;

		if (delay <= 0)
		{
			getline(cin, line);
			if (cin.eof())
				break;

			string instr = line.substr(0, 4);
			int val = 0;
			if (line.length() > 4)
				val = stoi(line.substr(4));

			if (instr == "addx")
			{
				futureAdds[curCycle + 2] = val;
				delay = 2;
			}
		}


		curCycle++;
	}

	vector<int> chosenCycles{ 20, 60, 100, 140, 180, 220 };

	int sum = 0;
	for (int c : chosenCycles)
	{
		int s = cycleXValues[c] * c;
		cout << "cycle " << c << ": " << s << endl;
		sum += s;
	}
	cout << "sum = " << sum << endl;

}
