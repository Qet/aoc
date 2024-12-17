#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <sstream>

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

		Computer(int A, int B, int C, string progStr) :
			initA(A), initB(B), initC(C)
		{
			inpVec = parseCSVNums(progStr);

			auto it = inpVec.begin();
			int curPc = 0;
			while (it != inpVec.end())
			{
				program.insert({ curPc,  { *it++, *it++ } });
				curPc += 2;
			}
			//outpVec.reserve(inpVec.max_size());
			reset();
		}

		int initA, initB, initC;
		int A, B, C;
		map<int, Instruction> program;
		int pc;
		int iterations = 0;

		vector<int> inpVec;
		vector<int> outpVec;

		void reset()
		{
			A = initA;
			B = initB;
			C = initC;
			pc = 0;
			iterations = 0;
			outpVec.clear();
		}

		int opToCombo(int op)
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
			Instruction instr = program[pc];

			int lit = instr.operand;
			int combo = opToCombo(instr.operand);

			pc += 2;

			switch (instr.opCode)
			{
			case 0:
				A = A >> combo;
				break;
			case 1:
				B = B ^ lit;
				break;
			case 2:
				B = combo % 8;
				break;
			case 3:
				if (A > 0)
					pc = lit;
				break;
			case 4:
				B = B ^ C;
				break;
			case 5:
				outpVec.push_back(combo % 8);
				break;
			case 6:
				B = A >> combo;
				break;
			case 7:
				C = A >> combo;
				break;
			}

			iterations++;
		}

		bool isHalted()
		{
			return program.find(pc) == program.end();
		}

		bool outputMatchesInput()
		{
			return inpVec == outpVec;
		}

		void incrA()
		{
			initA++;
		}
	};

}

int main()
{
	using namespace day17_2;
	//example 
	//Computer computer(729, 0, 0, "0,1,5,4,3,0");

	//part 1: 
	Computer computer(50000000, 0, 0, "2,4,1,5,7,5,1,6,0,3,4,1,5,5,3,0");

	//part 2 example
	//Computer computer(0, 0, 0, "0,3,5,4,3,0");

	while (true)
	{
		if (computer.initA % 1000000 == 0)
			cout << computer.initA << endl;

		while (!computer.isHalted())
		{
			computer.runOnce();
		}

		if (computer.outputMatchesInput())
		{
			cout << "Part 2: A = " << computer.initA << endl;
			break;
		}
		computer.incrA();
		computer.reset();
	}
	cout << endl;

	return 0;
}
