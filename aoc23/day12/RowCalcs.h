#pragma once

#include <vector>

/**
No matter what length the springs are, there will be a fixed number of positions that each spring can 
be in (p). 
Let the line length be l, the sum of all spring lengths be s, number of springs n
p = l - s - n
(subtract n as all springs need a space between them)
Whether or not each spring can be located in each position depends on whether there are adjacent dots or hashes (. / #)

For each position for a spring, calculate the total number of positions moving right to the end, starting from the right-most spring.
If a spring can't be in a position (due to a dot or hash as above) then the total number of positions for that position is zero. 

Example (ignoring spacings, dots or hashes):
4 springs (A, B, C, D), length 7.
	A  B  C  D  ?  ?  ?
D)           4  3  2  1
C)       10  6  3  1  0
B)    20 10  4  1  0  0 
A) 35 15  5  1  0  0  0 

*/

class RowCalcs
{
	int len;
	int numItems;
	std::vector<std::vector<bool>> allowedSquares;



public:
	RowCalcs(int len, int numItems);

	void setAllowedSquare(int item, int pos, bool value);
	
	uint64_t numPositions();

};

