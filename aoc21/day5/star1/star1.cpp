
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct point
{
	int x, y;

	point(int x, int y) : x(x), y(y) {}


};

bool operator==(const point& a, const point& b)
{
	return (a.x == b.x && a.y == b.y);
}

inline bool operator<(const point& a, const point& b)
{
	return (a.x + a.y * 2000) < (b.x + b.y * 2000);
}

inline bool operator>(const point& a, const point& b)
{
	return !(a>b);
}

vector<int> get_coord_sequence(int start, int end)
{
	vector<int> ret;
	
	int coord_min = min(start, end);
	int coord_max = max(start, end);

	for (int i = coord_min; i <= coord_max; i++)
	{
		ret.push_back(i);
	}

	return ret;
}

vector<point> get_line_points(point start, point end)
{
	int curx = 0, cury = 0;
	vector<point> points;
	if (start.x == end.x)
	{
		vector<int> seq = get_coord_sequence(start.y, end.y);

		for (int q : seq)
		{
			points.emplace_back(start.x, q);
		}
	}
	else if (start.y == end.y)
	{
		vector<int> seq = get_coord_sequence(start.x, end.x);

		for (int q : seq)
		{
			points.emplace_back(q, start.y);
		}
	}
	else
	{
		//ignore diagonal lines. 
	}

	return points;
}

point coord_to_point(string coord)
{
	int comma = coord.find(',');
	return point(stoi(coord.substr(0, comma)), stoi(coord.substr(comma + 1)));
}

int main()
{
    
	set<point> points;
	set<point> overlap_points;

	while(true)
	{
		string start_coord;
		string middle;
		string end_coord;
		cin >> start_coord;
		cin >> middle;
		cin >> end_coord;

		if (start_coord.length() == 0)
			break;

		point start_point = coord_to_point(start_coord);
		point end_point = coord_to_point(end_coord);

		vector<point> newPoints = get_line_points(start_point, end_point);

		for (point p : newPoints)
		{
			if (points.count(p) == 1) //Then it already has this point. so this is an overlapping point.
			{
				overlap_points.insert(p);
			}
			points.insert(p);
		}
	}

	cout << "Overlapping points: " << overlap_points.size() << endl;


}

