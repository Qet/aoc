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

int main()
{
	// A,B,C = rock,paper,scissors for opponent
	// X,Y,Z = rock,paper,scissors for you. 
	//rock 1, paper 2, scissors 3
	//loss 0, draw 3, win 6.

	map<string, result> results
	{
		{"A X", result::draw},
		{"A Y", result::win},
		{"A Z", result::loss},

		{"B X", result::loss},
		{"B Y", result::draw},
		{"B Z", result::win},

		{"C X", result::win},
		{"C Y", result::loss},
		{"C Z", result::draw}
	};

	map<char, int> shapeScores
	{
		{'X', 1},
		{'Y', 2},
		{'Z', 3}
	};

	map<result, int> resultScores
	{
		{result::loss, 0},
		{result::draw, 3},
		{result::win, 6}
	};
	

	string line;
	int totalScore{0};
	while (getline(cin, line))
	{
		result lineResult = results[line];
		totalScore += shapeScores[line[2]] + resultScores[lineResult];
	}
	cout << "Total score is: " << totalScore << endl;
}

// This code had 3 bugs in it the first time I ran it. 
// 1: I had mixed up the opponent and me, so the results map win/loss were around the wrong way. 
// 2: copy-paste error in shapeScores - they were all set to 1.
// 3: I was getting the shape score from the opponents shape (first char) instead of my shape (3rd char). 
