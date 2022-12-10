#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>

using namespace std;

struct point
{
	point(int x, int y) :
		x(x), y(y)
	{}

	point() {}

	int x{ 0 }, y{ 0 };

	bool operator<(const point& other) const
	{
		return (this->x + 1000 * this->y) < (other.x + 1000 * other.y);
	}
	
	bool operator==(const point& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const point& other)
	{
		return !(*this == other);
	}
	string coords()
	{
		return "(" + to_string(x) + ", " + to_string(y) + ")";
	}

	void move(char dir)
	{
		switch (dir)
		{
		case 'R':
			x++; break;
		case 'L':
			x--; break;
		case 'U':
			y++; break;
		case 'D':
			y--; break;
		}
	}

	double dist(point& other)
	{
		double dx = this->x - other.x;
		double dy = this->y - other.y;
		return sqrt(dx * dx + dy * dy);
	}

	point relativePoint(int dx, int dy)
	{
		point newpoint;
		newpoint.x = this->x + dx;
		newpoint.y = this->y + dy;
		return newpoint;
	}
};

int main()
{
	vector<point> rope(10);

	map<point, int> tailVisited;
	string line;
	while (getline(cin, line))
	{
		char dir = line.substr(0, 1)[0];
		int steps = stoi(line.substr(2));

		for (int i = 0; i < steps; i++)
		{
			//1: move H
			rope[0].move(dir);
			tailVisited[rope[9]]++;

			//move each of the parts of the rope according to the same logic for a short rope move. 
			for (int j = 0; j < rope.size() - 1; j++)
			{
			
				point& h = rope[j];
				point& t = rope[j + 1];
				
				
				//2: if distance from T to H is greater than the rope length then move T to the closest square to H that is within 1 square of T. 
				//rope length is probably sqrt(2) 
				double dist = h.dist(t);
				if (dist > 1.5)
				{
					vector<point> surroundingPoints;
					for (int dx = -1; dx <= 1; dx++)
					{
						for (int dy = -1; dy <= 1; dy++)
						{
							surroundingPoints.push_back(t.relativePoint(dx, dy));
						}
					}

					double closestDist = 999; //big enough number...
					point closestPoint;

					for (point p : surroundingPoints)
					{
						if (p.dist(h) < closestDist)
						{
							closestDist = p.dist(h);
							closestPoint = p;
						}
					}

					t = closestPoint;
				}
			}
		}
		//the tail might have moved in the final step. 
		tailVisited[rope[9]]++;
	}

	const int visitCount = tailVisited.size();

	//print out the tail (for debugging)
	//const int gs = 20;
	//for (int y = gs; y >= -gs; y--)
	//{
	//	for (int x = -gs; x <= gs; x++)
	//	{
	//		point p(x, y);
	//		if (p == point(0, 0))
	//			cout << "s";
	//		else if (tailVisited[p] > 0)
	//			cout << "#";
	//		else
	//			cout << ".";
	//	}
	//	cout << endl;
	//}
	cout << endl;

	cout << visitCount << endl;

}
