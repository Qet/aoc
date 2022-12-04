#include <iostream>
#include <string>

using namespace std;

struct range
{
	int lo;
	int hi;
};


bool rangesOverlap(range a, range b)
{
	return !(a.hi < b.lo || a.lo > b.hi); //A overlaps B if it's not completely lower than or higher than B.
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

		if (rangesOverlap(ra, rb))
			count++;

	}

	cout << "Overlapping ranges: " << count << endl;

}