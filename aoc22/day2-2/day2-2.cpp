#include <iostream>
#include <string>
#include <map>

using namespace std;

enum class result
{
	win,
	loss,
	draw
};

enum class shape
{
	rock,
	paper,
	scissors
};

int main()
{
	// A,B,C = rock,paper,scissors for opponent
	// X,Y,Z = need to lose, draw, win. 
	//rock 1, paper 2, scissors 3
	//loss 0, draw 3, win 6.

	map<string, shape> myShapePlayed
	{
		{"A X", shape::scissors},
		{"A Y", shape::rock},
		{"A Z", shape::paper},
				
		{"B X", shape::rock},
		{"B Y", shape::paper},
		{"B Z", shape::scissors},
				
		{"C X", shape::paper},
		{"C Y", shape::scissors},
		{"C Z", shape::rock}
	};

	map<char, result> results
	{
		{'X', result::loss},
		{'Y', result::draw},
		{'Z', result::win}
	};


	map<shape, int> shapeScores
	{
		{shape::rock, 1},
		{shape::paper, 2},
		{shape::scissors, 3}
	};

	map<result, int> resultScores
	{
		{result::loss, 0},
		{result::draw, 3},
		{result::win, 6}
	};


	string line;
	int totalScore{ 0 };
	while (getline(cin, line))
	{
		result lineResult = results[line[2]];
		shape myShape = myShapePlayed[line];

		totalScore += shapeScores[myShape] + resultScores[lineResult];
	}
	cout << "Total score is: " << totalScore << endl;
}
