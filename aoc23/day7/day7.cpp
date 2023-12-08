#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int cardScore(char card)
{
	map<char, int> scores = {
		{'2', 1},
		{'3', 2},
		{'4', 3},
		{'5', 4},
		{'6', 5},
		{'7', 6},
		{'8', 7},
		{'9', 8},
		{'T', 9},
		{'J', 10},
		{'Q', 11},
		{'K', 12},
		{'A', 13}
	};

	return scores[card];
}

class CardCount
{
	map<char, int> counts = {
		{'2', 0},
		{'3', 0},
		{'4', 0},
		{'5', 0},
		{'6', 0},
		{'7', 0},
		{'8', 0},
		{'9', 0},
		{'T', 0},
		{'J', 0},
		{'Q', 0},
		{'K', 0},
		{'A', 0}
	};

	int numXOfKind(int x)
	{
		int ret = 0;
		for (auto const& card : counts)
		{
			if (card.second == x)
				ret++;
		}
		return ret;
	}

	bool onePair()
	{
		return numXOfKind(2) == 1;
	}

	bool twoPair()
	{
		return numXOfKind(2) == 2;
	}

	bool trips()
	{
		return numXOfKind(3) == 1;
	}

	bool quads()
	{
		return numXOfKind(4) == 1;
	}

	bool pents()
	{
		return numXOfKind(5) == 1;
	}

	bool fullHouse()
	{
		return numXOfKind(3) == 1 && numXOfKind(2) == 1;
	}

public: 
	CardCount(string hand)
	{
		for (char c : hand)
		{
			counts[c]++;
		}
	}

	int handType()
	{
		if (pents()) return 6;
		if (quads()) return 5;
		if (fullHouse()) return 4;
		if (trips()) return 3;
		if (twoPair()) return 2;
		if (onePair()) return 1;
		return 0;
	}
};


class HandBid
{
	
public:

	int bid;
	int handType;
	string hand;

	HandBid(string line)
	{
		hand = line.substr(0, 5);
		bid = stoi(line.substr(5));
		CardCount cc(hand);
		handType = cc.handType();
	}
};


bool worstHand(HandBid handA, HandBid handB) //sort from worst to best 
{
	if (handA.handType != handB.handType)
	{
		return handA.handType < handB.handType;
	}

	for (int i = 0; i < 5; i++)
	{
		int cardScoreA = cardScore(handA.hand[i]);
		int cardScoreB = cardScore(handB.hand[i]);

		if (cardScoreA != cardScoreB)
			return cardScoreA < cardScoreB;
	}
	return false;
}

int main()
{
	string line;
	vector<HandBid> hands;

	while (getline(cin, line))
	{
		hands.push_back(HandBid(line));
	}

	sort(hands.begin(), hands.end(), worstHand);
	
	int winnings = 0;
	for (int i = 0; i < hands.size(); i++)
	{
		winnings += (i + 1) * hands[i].bid;
	}

	cout << "Winnings: " << winnings << endl;

	return 0;
}

