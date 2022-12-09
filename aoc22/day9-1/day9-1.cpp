// day9-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <windows.h>

using namespace std;

struct point
{
	int x{ 0 }, y{ 0 };

	bool operator==(point& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(point& other)
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
	point h, t;
	point originalT = t;
	point originalH = h;

	map<string, int> tailVisited;
	string line;
	while (getline(cin, line))
	{
		char dir = line.substr(0, 1)[0];
		int steps = stoi(line.substr(2));

		for (int i = 0; i < steps; i++)
		{
			tailVisited[t.coords()]++;

			//1: move H
			h.move(dir);

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

		//the tail might have moved in the final step. 
		tailVisited[t.coords()]++;
	}

	int visitCount = tailVisited.size();
	cout << visitCount << endl;
	   
}
