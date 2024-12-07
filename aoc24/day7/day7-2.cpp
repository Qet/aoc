#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <deque>

using namespace std;

int main()
{
	string line;
	uint64_t totalTargets = 0;


	while (getline(cin, line))
	{
		stringstream ss = stringstream(line);
		uint64_t target;
		ss >> target;
		char colon;
		ss >> colon;

		vector<uint64_t> ops;
		while (true)
		{
			uint64_t v;
			ss >> v;
			if (ss.fail()) break;
			ops.push_back(v);
		}

		deque<uint64_t> tots;
		tots.push_back(ops[0]);

		uint64_t numPrevPushes = 1;
		for (uint64_t i = 1; i < ops.size(); i++)
		{
			for (uint64_t j = 0; j < numPrevPushes; j++)
			{
				uint64_t L = tots.front();
				tots.pop_front();

				tots.push_back(L * ops[i]);
				tots.push_back(L + ops[i]);
				tots.push_back(stoll(to_string(L) + to_string(ops[i])));
			}
			numPrevPushes *= 3;
		}


		for (uint64_t t : tots)
		{
			if (t == target)
			{
				cout << "target of " << t << " met." << endl;
				totalTargets += t;
				break;
			}
		}
	}

	cout << "Part 2: " << totalTargets << endl;
}
