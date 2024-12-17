#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <vector>
#include <sstream>

using namespace std;

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
	Instruction(){}

	Instruction(int opCode, int operand) :
		opCode(opCode),
		operand(operand)
	{}

	int opCode;
	int operand;
};

struct Computer
{
	
	Computer(int A, int B, int C, string progStr):
		A(A), B(B), C(C)
	{
		vector<int> prog = parseCSVNums(progStr);

		auto it = prog.begin();
		int curPc = 0;
		while (it != prog.end())
		{
			program.insert({ curPc,  { *it++, *it++ } });
			curPc += 2;
		}

		pc = 0;
	}
	
	int A, B, C;
	map<int, Instruction> program;
	int pc;
	int iterations = 0;

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
			cout << combo % 8 << ",";
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

};



int main1()
{
	//example 
	//Computer computer(729, 0, 0, "0,1,5,4,3,0");

	//part 1: 
	Computer computer(44374556, 0, 0, "2,4,1,5,7,5,1,6,0,3,4,1,5,5,3,0");

	//part 2 example
	//Computer computer(117440, 0, 0, "0,3,5,4,3,0");


	while (!computer.isHalted())
	{
		computer.runOnce();
	}
	cout << endl;
	cout << computer.iterations << " iterations." << endl;



	return 0;
}
