#include <iostream>
#include <string>

using namespace std;

struct range
{
	int lo;
	int hi;
};


bool rangeAInB(range a, range b)
{
	return  (a.lo >= b.lo && a.hi <= b.hi);
}

bool rangeIsContained(range a, range b)
{
	return  rangeAInB(a, b) || rangeAInB(b, a);
}

range parseRange(string rangeString)
{
	range r;
	r.lo = stoi(rangeString.substr(0, rangeString.find('-')));
	r.hi = stoi(rangeString.substr(rangeString.find('-') + 1));
	return r;
}

int main()
{
	string line;
	int count{ 0 };
	while (getline(cin, line))
	{
		string a = line.substr(0, line.find(','));
		string b = line.substr(line.find(',') + 1);

		range ra = parseRange(a);
		range rb = parseRange(b);

		if (rangeIsContained(ra, rb))
			count++;

	}

	cout << "Contained ranges: " << count << endl;

}