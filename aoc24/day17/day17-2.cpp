#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

namespace day17_2
{

	vector<int> parseCSVNums(string nums)
	{
		stringstream ss = stringstream(nums);
		vector<int> vec;
		while (true)
		{
			int temp;
			ss >> temp;
			if (ss.fail())
				break;
			else
				vec.push_back(temp);
			char comma;
			ss >> comma;
		}
		return vec;
	}

	struct Instruction
	{
		Instruction() {}

		Instruction(int opCode, int operand) :
			opCode(opCode),
			operand(operand)
		{}

		int opCode;
		int operand;
	};

	struct Computer
	{

		Computer(string progStr = "2,4,1,5,7,5,1,6,0,3,4,1,5,5,3,0") :
			initA(0), initB(0), initC(0)
		{
			inpVec = parseCSVNums(progStr);

			auto it = inpVec.begin();
			while (it != inpVec.end())
			{
				program.push_back({ *it++, *it++ });
			}

			programSize = program.size();

			reset();
		}

		uint64_t initA, initB, initC;
		uint64_t A, B, C;
		vector<Instruction> program;
		int programSize;
		int pc;

		vector<int> inpVec;
		vector<int> outpVec;

		void reset()
		{
			A = initA;
			B = initB;
			C = initC;
			pc = 0;
			outpVec.clear();
		}

		uint64_t opToCombo(uint64_t op)
		{
			if (op >= 0 && op <= 3)
				return op;
			else if (op == 4)
				return A;
			else if (op == 5)
				return B;
			else if (op == 6)
				return C;
			throw exception("Invalid op to combo");
		}

		void runOnce()
		{
			Instruction& instr = program[pc];

			pc++;

			switch (instr.opCode)
			{
			case 0:
				A = A >> (opToCombo(instr.operand));
				break;
			case 1:
				B = B ^ instr.operand;
				break;
			case 2:
				B = (opToCombo(instr.operand)) % 8;
				break;
			case 3:
				if (A > 0)
					pc = 0;
				else
					pc = INT_MAX;
				break;
			case 4:
				B = B ^ C;
				break;
			case 5:
				outpVec.push_back((opToCombo(instr.operand)) % 8);
				//if (!inputStartsWithOutput())
				//	pc = INT_MAX; //short circuit out of this program as it doesn't match the required output. 
				break;
			case 6:
				B = A >> (opToCombo(instr.operand));
				break;
			case 7:
				C = A >> (opToCombo(instr.operand));
				break;
			}
		}

		bool isHalted()
		{
			return pc >= programSize;
		}

		bool inputStartsWithOutput()
		{
			//still on track, as the output still matches up with the input so far. 
			for (int i = 0; i < outpVec.size(); i++)
			{
				if (outpVec[i] != inpVec[i]) //short circuit on any mismatch. 
					return false;
			}
			return true;
		}

		bool outputMatchesInput()
		{
			return inpVec == outpVec;
		}

		void incrA()
		{
			initA++;
		}

		void setA(uint64_t A)
		{
			initA = A;
		}

		void print()
		{
			for (int x : outpVec)
			{
				cout << x ;
			}
			cout << endl;
		}

		int len()
		{
			return outpVec.size();
		}

		string getOutputNum()
		{
			string out = "";
			for (int x : outpVec)
			{
				out += to_string(x);
			}
			
			return out;
		}
	};

}

using namespace day17_2;


string getOutputNum(uint64_t inputNumber)
{
	static Computer computer;

	computer.setA(inputNumber);
	computer.reset();

	while (!computer.isHalted())
	{
		computer.runOnce();
	}

	return computer.getOutputNum();

}

static const uint64_t CALCS_PER_CYCLE = 1'000'000;
static const string TARGET = "2415751603415530";
static const int TARGET_LEN = TARGET.length();



struct Cycler
{
	//uint64_t curMin = pow(8, 15);
	//uint64_t curMax = pow(8, 16);

	uint64_t curMin = 0;
	uint64_t curMax = pow(8, 17);


	Computer computer;

	vector<int> scores;

	int calcScore(string outp)
	{
		int score = 0;
		if (outp.length() == TARGET_LEN)
		{
			for (int i = TARGET_LEN - 1; i >= 0; i--)
			{
				if (TARGET[i] != outp[i]) break;

				score++;
			}
		}
		return score;
	}

	int findCentreMaxIndex()
	{
		int maxScore = *max_element(scores.begin(), scores.end());

		int iMin = 0;
		int iMax = 0;

		bool foundMax = false;


		for (int i = 0; i < scores.size(); i++)
		{
			if (!foundMax)
			{
				if (scores[i] == maxScore)
				{
					iMin = i;
					foundMax = true;
				}
			}
			else
			{
				if (scores[i] < maxScore)
				{
					iMax = i;
					break;
				}
			}
		}

		return (iMax + iMin) / 2;

	}

	void run()
	{
		
		while (true)
		{
			
			uint64_t step = (curMax - curMin) / CALCS_PER_CYCLE;
			if (step == 0)
				step = 1;

			for (uint64_t i = curMin; i < (curMax - step); i += step)
			{
				computer.setA(i);
				computer.reset();
				while (!computer.isHalted())
					computer.runOnce();

				const string curOutp = computer.getOutputNum();

				const int score = calcScore(curOutp);
				scores.push_back(score);

				if (score == TARGET_LEN)
				{
					cout << "FOUND IT: " << i << endl;
					return;
				}
			}

			const int bestScoreIndex = findCentreMaxIndex();
			const uint64_t bestIndex = curMin + bestScoreIndex * step;
			const uint64_t minDistFromBest = min(curMax - bestIndex, bestIndex - curMin);
			const uint64_t nextOffsetFromBest = minDistFromBest / 2;

			cout << "[" << (double)curMin << ", " << (double)curMax << "] ";
			cout << "Best score: " << scores[bestScoreIndex];
			cout << " Best idx: " << (double)bestIndex;
			cout << " minDistFromBest: " << (double)minDistFromBest;
			cout << " nextOffsetFromBest: " << (double)nextOffsetFromBest;
			cout << "  " << ((double)bestIndex - (double)curMin) / ((double)curMax - (double)curMin) * 100 << "% pos";
			cout << endl;

			curMin = bestIndex - nextOffsetFromBest;
			curMax = bestIndex + nextOffsetFromBest;
			scores.clear();
		}
	}
	

};



int main()
{
	
	//cout << getOutputNum(110379203127706) << endl;
	//return 0;
	
	Cycler c;

	c.run();

	cout << endl;

	return 0;
}

/*
start with a coarse scan over the whole range. find the lowest max point and zoom in. repeat until a solution is found. 

*/