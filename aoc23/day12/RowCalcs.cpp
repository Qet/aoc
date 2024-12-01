#include "RowCalcs.h"

using namespace std;

void RowCalcs::setAllowedSquare(int item, int pos, bool value)
{
	allowedSquares[item][pos] = value;
}

RowCalcs::RowCalcs(int len, int numItems):
	len(len),
	numItems(numItems)
{
	allowedSquares = vector<vector<bool>>(numItems);
	for (int i = 0; i < allowedSquares.size(); i++)
	{
		allowedSquares[i] = vector<bool>(len);
	}
}

uint64_t numPositions()
{
	
}