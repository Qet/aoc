
#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

struct Block
{
	Block(bool free, int id, bool isBlockStart, int size) :
		free(free),
		id(id),
		isBlockStart(isBlockStart),
		size(size),
		hasMoved(false)
	{
	}

	bool free;
	int id;
	bool isBlockStart;
	int size;
	bool hasMoved;
};


struct Disk
{
	Disk(string data)
	{
		init(data);
	}
	
	void moveIterators()
	{
		while (bstart != blocks.end() && !bstart->free) ++bstart;
		while (bend != blocks.begin() && bend->free) --bend;
	}

	void compact()
	{
		bstart = blocks.begin();
		bend = blocks.end();
		--bend; 
		moveIterators();

		while (bstart < bend)
		{
			iter_swap(bstart, bend);
			moveIterators();
		}
	}

	void moveEndIt()
	{
		//move to the start of the next file, backwards. 
		while (bend != blocks.begin() && 
			!( !bend->free && bend->isBlockStart && !bend->hasMoved)) --bend;
	}

	void moveStartIt(int minSize)
	{
		//move the start iterator from the start, until we find a free space at least minSize big. 
		//if nothing is found, end on the end.
		bstart = blocks.begin();
		while (bstart != blocks.end())
		{
			vector<Block>::iterator it{ bstart };
			int spanSize{ 0 };
			while (it != blocks.end() && it->free && spanSize < minSize)
			{
				spanSize++;
				++it;
			}
			if (spanSize >= minSize) break;
			++bstart;
		}
	}

	void defrag()
	{
		bstart = blocks.begin();
		bend = blocks.end();
		--bend;

		while (bend > blocks.begin())
		{
			//print();
			moveEndIt();
			moveStartIt(bend->size);

			bend->hasMoved = true;
			
			if (bstart != blocks.end() && bstart < bend) //found some space
			{
				swap_ranges(bstart, bstart + bend->size, bend);
			}

		}
	}

	uint64_t checksum()
	{
		uint64_t tot = 0;
		for (uint64_t i = 0; i < blocks.size(); i++)
			if (!blocks[i].free) tot += i * blocks[i].id;
		return tot;
	}
	
	void print()
	{
		for (const Block& b : blocks)
		{
			if (b.free)
				cout << '.';
			else
				cout << b.id;
		}
		cout << endl;
	}

private:
	vector<Block> blocks;

	vector<Block>::iterator bstart;
	vector<Block>::iterator bend;


	void init(string data)
	{
		int fileId = 0;
		bool isAFileSize = true;
		for (char c : data)
		{
			string cs{ c };
			int v = stoi(cs);

			if (v > 0)
			{
				blocks.insert(blocks.end(), { !isAFileSize, fileId, true, v });
				blocks.insert(blocks.end(), v - 1, { !isAFileSize, fileId, false, 0 });
			}

			if (isAFileSize) fileId++;
			isAFileSize = !isAFileSize;
		}
	}



};

chrono::time_point<chrono::steady_clock> getTime()
{
	return chrono::high_resolution_clock::now();
}

int main()
{

	string data;
	//data = "2333133121414131402";
	getline(cin, data);

	auto part1_start = getTime();
	Disk disk(data);
	disk.compact();
	cout << "Part 1 total: " << disk.checksum() << endl;
	auto part1_end = getTime();

	cout << "Part 1 time: " 
		<< chrono::duration_cast<chrono::milliseconds>(part1_end - part1_start).count()
		<< " ms." << endl;
	
	auto part2_start = getTime();
	Disk disk2(data);
	disk2.defrag();
	cout << "Part 2 total: " << disk2.checksum() << endl;
	auto part2_end = getTime();

	cout << "Part 2 time: "
		<< chrono::duration_cast<chrono::milliseconds>(part2_end - part2_start).count()
		<< " ms." << endl;


	return 0;
}
