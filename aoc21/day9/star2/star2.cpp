
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct point
{
	int value;
	bool isLowPoint = false;
	int basinID = 0;  //Default basin is 0 for all points, which is not counted at the end. 
	int i;
	int j;
};

template <class T>
class BoundsCheck
{
private:
	vector<vector<T>>& data;
	int i, j;
public: 
	BoundsCheck(vector<vector<T>>& data, int i, int j) : data(data), i(i), j(j) {}
	
	bool checkN()
	{
		return i - 1 >= 0;
	}

	bool checkE()
	{
		return j + 1 < data[i].size();
	}

	bool checkW()
	{
		return j - 1 >= 0;
	}

	bool checkS()
	{
		return i + 1 < data.size();
	}

	T& getN()
	{
		return data[i - 1][j];
	}

	T& getE()
	{
		return data[i][j + 1];
	}

	T& getS()
	{
		return data[i + 1][j];
	}

	T& getW()
	{
		return data[i][j - 1];
	}


};

struct ij
{
	int i, j;
	ij(int i, int j): i(i), j(j) {}
};

class PointProcessing
{

	vector<vector<point>> points;
	vector<vector<int>>& data;
	int i;
	int j;
	int curBasin = 1;
	vector<ij> lowPoints;

public: 

	PointProcessing(vector<vector<int>>& data) :
		data(data),
		i(0),j(0)
	{}

	bool isLowPoint()
	{
		BoundsCheck<int> b(data, i, j);
		int v = data[i][j];
		return 
			(b.checkN() ? b.getN() : INT_MAX) > v &&
			(b.checkE() ? b.getE() : INT_MAX) > v &&
			(b.checkS() ? b.getS() : INT_MAX) > v &&
			(b.checkW() ? b.getW() : INT_MAX) > v;
	}

	void createPoints()
	{
		for (i = 0; i < data.size(); i++)
		{
			vector<point> row;
			for (j = 0; j < data[i].size(); j++)
			{
				point p;
				p.value = data[i][j];
				p.i = i;
				p.j = j;
				if (isLowPoint())
				{
					p.isLowPoint = true;
					p.basinID = curBasin++;
					lowPoints.push_back(ij(i,j));
				}
				row.push_back(p);
			}
			points.push_back(row);
		}
	}
	
	void markBasins()
	{
		//Starting from the low points, branch out in the carninal directions, in a depth-first-search fashion, searching for higher points.
		//If you reach a 9 or a equal or lower point, then stop branching in that direction as that's the end of the basin. 
		//Mark all these points with a basin number. 
		for (int i = 0; i < lowPoints.size(); i++)
		{
			point& p = points[lowPoints[i].i][lowPoints[i].j];
			checkPointForBasin(p);
		}
	}
	
	
	void checkPointForBasin(point& p)
	{
		BoundsCheck<point> b(points, p.i, p.j);
		if (b.checkN())
		{
			point& pN = b.getN();
			if (pN.value > p.value && pN.value != 9)
			{
				pN.basinID = p.basinID;
				checkPointForBasin(pN);
			}
		}
		if (b.checkE())
		{
			point& pE = b.getE();
			if (pE.value > p.value && pE.value != 9)
			{
				pE.basinID = p.basinID;
				checkPointForBasin(pE);
			}
		}
		if (b.checkS())
		{
			point& pS = b.getS();
			if (pS.value > p.value && pS.value != 9)
			{
				pS.basinID = p.basinID;
				checkPointForBasin(pS);
			}
		}
		if (b.checkW())
		{
			point& pW = b.getW();
			if (pW.value > p.value && pW.value != 9)
			{
				pW.basinID = p.basinID;
				checkPointForBasin(pW);
			}
		}
	}
	void go()
	{
		createPoints();
		markBasins();
		print();
		measureBasins();
	}

	void measureBasins()
	{
		vector<int> basins = vector<int>(curBasin, 0);
		for (int i = 0; i < points.size(); i++)
		{
			for (int j = 0; j < points[i].size(); j++)
			{
				point& p = points[i][j];
				if (p.basinID > 0)
				{
					basins[p.basinID]++;
				}
			}
		}
		
		sort(begin(basins), end(basins), [](int a, int b)
			{
				return a > b;
			});

		cout << "Three largest basins are: " << basins[0] << ", " << basins[1] << ", and " << basins[2] << endl;
		cout << "Product of which is: " << basins[0] * basins[1] * basins[2] << endl;

	}

	void print()
	{
		for (i = 0; i < data.size(); i++)
		{
			for (j = 0; j < data[i].size(); j++)
			{
				point& p = points[i][j];
				cout << p.basinID << " ";
			}
			cout << endl;
		}
	}
};



int main()
{
	string line;
	int rowCount = 0;
	vector<vector<int>> data;
	while (cin >> line && line.length() > 0)
	{
		vector<int> row;
		for (char c : line)
		{
			row.push_back(c - '0');
		}
		data.push_back(row);
	}

	PointProcessing pp(data);
	pp.go();
	
}
