
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct point
{
	int x, y, z;

	point(int x, int y, int z) : x(x), y(y), z(z) {}

	bool operator=(const point& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool operator!=(const point& other)
	{
		return !operator=(other);
	}

	bool operator<(const point& other)
	{
		return (1000 * x + 100 * y + z) < (1000 * other.x + 100 * other.y + other.z);
	}
	
};

struct cube
{
	vector<cube*> exits;
};

map<point, cube> lava;

int main()
{
	string line;
	while (true)
	{
		int x, y, z;

	}
}
