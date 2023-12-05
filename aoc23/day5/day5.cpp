#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Range  //a single line from the file indicating a mapping range
{
	uint32_t src;
	uint32_t dst;
	uint32_t len;
	int32_t diff;

public:
	Range(uint32_t src, uint32_t dst, uint32_t len) :
		src(src),
		dst(dst),
		len(len),
		diff(dst - src)
	{
	}

	bool withinRange(uint32_t val)
	{
		return val >= src &&
			val < src + len;
	}

	uint32_t map(uint32_t val)
	{
		return val + diff; //shouldn't go negative, right?
	}	
};

class RangeCollection //a collection of ranges, i.e. a "map" from the file (e.g. seed to soil)
{
	vector<Range> ranges;

public :
	void addRange(string line)
	{
		uint32_t src, dst, len;
		stringstream ss = stringstream(line);
		ss >> dst;
		ss >> src;
		ss >> len;
		ranges.push_back(Range(src, dst, len));
	}

	uint32_t map(uint32_t val)
	{
		for (Range range : ranges)
		{
			if (range.withinRange(val))
			{
				return range.map(val);
			}
		}
		return val;
	}
};

vector<uint32_t> parseNums(string nums)
{
	stringstream ss = stringstream(nums);
	vector<uint32_t> vec;
	while (true)
	{
		uint32_t temp;
		ss >> temp;
		if (ss.fail())
			break;
		else
			vec.push_back(temp);
	}
	return vec;
}

RangeCollection parseMapSection()
{
	RangeCollection ret;
	string line;

	while (true)
	{
		auto& x = getline(cin, line);
		if (x && isdigit(line[0]))
		{
			ret.addRange(line);
		}
		else
		{
			break;
		}
	}

	return ret;
}

uint32_t mapSeed(uint32_t seed, vector<RangeCollection> maps)
{
	uint32_t curVal = seed;
	for (RangeCollection rc : maps)
	{
		curVal = rc.map(curVal);
	}

	return curVal;
}

int main_part1()
{
	//Get the seed list
	string line;
	getline(cin, line);
	vector<uint32_t> seeds = parseNums(line.substr(line.find(':') + 2));
	
	vector<string> headers{
		"seed-to-soil map:",
		"soil-to-fertilizer map:",
		"fertilizer-to-water map:",
		"water-to-light map:",
		"light-to-temperature map:",
		"temperature-to-humidity map:",
		"humidity-to-location map:"
	};

	//get all the maps
	vector<RangeCollection> maps;

	for (string header : headers)
	{
		while (getline(cin, line))
		{
			if (line.find(header))
			{
				maps.push_back(parseMapSection());
			}
		}
	}

	//calculate the locations
	vector<uint32_t> locations;
	for (uint32_t seed : seeds)
	{
		locations.push_back(mapSeed(seed, maps));
	}

	cout << "Min location: " << *min_element(locations.begin(), locations.end()) << endl;
	return 0;

}


int main()
{
	//Get the seed list
	string line;
	getline(cin, line);
	vector<uint32_t> seeds = parseNums(line.substr(line.find(':') + 2));

	vector<string> headers{
		"seed-to-soil map:",
		"soil-to-fertilizer map:",
		"fertilizer-to-water map:",
		"water-to-light map:",
		"light-to-temperature map:",
		"temperature-to-humidity map:",
		"humidity-to-location map:"
	};

	//get all the maps
	vector<RangeCollection> maps;

	for (string header : headers)
	{
		while (getline(cin, line))
		{
			if (line.find(header))
			{
				maps.push_back(parseMapSection());
			}
		}
	}

	//calculate the locations
	uint32_t totalSeeds = 0;
	for (int i = 0; i < seeds.size(); i += 2)
	{
		totalSeeds += seeds[i + 1];
	}

	uint32_t minLoc = UINT_MAX;
	uint32_t seedCount = 0;
	for (int i = 0; i < seeds.size(); i += 2)
	{
		uint32_t seedStart = seeds[i];
		uint32_t seedLen = seeds[i + 1];
		
		for (uint32_t curSeed = seedStart; curSeed < seedStart + seedLen; curSeed++)
		{
			if (seedCount % 100000 == 0)
				cout << (int)((double)(seedCount) / totalSeeds * 100) << "% complete" << endl;
			uint32_t mappedLocation = mapSeed(curSeed, maps);
			
			if (mappedLocation < minLoc)
				minLoc = mappedLocation;
			seedCount++;
		}
		
	}

	cout << "Min location: " << minLoc << endl;
}
