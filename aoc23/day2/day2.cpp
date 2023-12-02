// day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

enum class Colour
{
	Red,
	Green,
	Blue
};

map<string, Colour> ColourMap{
	{"red", Colour::Red},
	{"green", Colour::Green},
	{"blue", Colour::Blue}
};

map<Colour, int> parseDraw(string draw)
{
	int pos = 0;
	map<Colour, int> ret{
		{Colour::Red, 0},
		{Colour::Green, 0},
		{Colour::Blue, 0}
	};
	while (true)
	{

		int qty = stoi(draw.substr(pos));
		Colour col;
		while (!isalpha(draw[pos])) pos++;
		for (auto const& kv : ColourMap)
		{
			if (kv.first == draw.substr(pos, kv.first.length()))
			{
				col = kv.second;
				break;
			}
		}
		
		cout << (int)col << " " << qty << endl;
		ret[col] = qty;

		int comma = draw.find(',', pos);
		if (comma < draw.length())
			pos = comma + 1;
		else
			break;
	}

	return ret;

}

bool drawPossible(map<Colour, int> draw)
{
	return draw[Colour::Red] <= 12 && draw[Colour::Green] <= 13 && draw[Colour::Blue] <= 14;
}





int main_star1()
{
	string line;
	int pos = 0;

	int possibleGamesSum = 0;

	while (getline(cin, line))
	{
		int game = stoi(line.substr(4));
		pos = line.find(':') + 2;

		int endPos = 0;
		bool possibleGame = true;
		while (endPos < line.length())
		{
			endPos = line.find(';', pos);
			if (endPos < 0) endPos = line.length();
			map<Colour, int> draw = parseDraw(line.substr(pos, endPos - pos));
			if (!drawPossible(draw))
			{
				possibleGame = false;
				break;
			}
			pos = endPos + 2;
		}
		
		if (possibleGame) possibleGamesSum += game;

	}

	cout << "Total possible games ID sum: " << possibleGamesSum << endl;

	return 0;
}

int gamePower(map<Colour, int> game)
{
	int ret = 1;
	for (auto const& kv : game)
	{
		ret *= kv.second;
	}
	return ret;
}

int main()
{
	string line;
	int pos = 0;

	
	int totalGamePower = 0;
	
	while (getline(cin, line))
	{
		map<Colour, int> gameMaxes{ 
			{Colour::Red, 0},
			{Colour::Green, 0},
			{Colour::Blue, 0}
		};

		int game = stoi(line.substr(4));
		pos = line.find(':') + 2;

		int endPos = 0;
		bool possibleGame = true;
		while (endPos < line.length())
		{
			endPos = line.find(';', pos);
			if (endPos < 0) endPos = line.length();
			map<Colour, int> draw = parseDraw(line.substr(pos, endPos - pos));

			for (auto const& kv : draw)
			{
				gameMaxes[kv.first] = max(gameMaxes[kv.first], kv.second);
			}
		
			pos = endPos + 2;
		}

		totalGamePower += gamePower(gameMaxes);

	}

	cout << "Total game power: " << totalGamePower << endl;

}
