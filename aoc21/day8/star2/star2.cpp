
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> digits{
	{"ABCEFG", 0},
	{"CF", 1},
	{"ACDEG", 2},
	{"ACDFG", 3},
	{"BCDF", 4},
	{"ABDFG", 5},
	{"ABDEFG", 6},
	{"ACF", 7},
	{"ABCDEFG", 8},
	{"ABCDFG", 9}
};

class processing
{

public:
	int decode_line_outputs(const vector<string>& signals, const vector<string>& outputs)
	{
		string s1 = get_number_set(2)[0];
		string s4 = get_number_set(4)[0];
		string s7 = get_number_set(3)[0];

		string A = find_unique_chars(s7, s1);

		string C = s1;
		string F = s1;

		string B = find_unique_chars(s4, s1);
		string D = B;

		string E = find_unique_chars(find_unique_chars("abcdefg", s4), s7);
		string G = E;
		
		vector<string> fives = find_fives_pairs();

		string EF_five;
		string BC_five;
		string five1 = fives[0];
		string five2 = fives[1];
		if (find_unique_chars(E + F, five1).length() == 2)
		{
			EF_five = five1;
			BC_five = five2;
		}
		else
		{
			EF_five = five2;
			BC_five = five1;
		}

		if (E.find(EF_five[0]) != string::npos)
		{
			E = EF_five[0];
			F = EF_five[1];
		}
		else
		{
			E = EF_five[1];
			F = EF_five[0];
		}

		if (B.find(BC_five[0]) != string::npos)
		{
			B = BC_five[0];
			C = BC_five[1];
		}
		else
		{
			B = BC_five[1];
			C = BC_five[0];
		}

		D = find_unique_chars(D, B);
		G = find_unique_chars(G, E);
		
		map<char, char> decoder{
			{A[0], 'A'},
			{B[0], 'B'},
			{C[0], 'C'},
			{D[0], 'D'},
			{E[0], 'E'},
			{F[0], 'F'},
			{G[0], 'G'},
		};

		string output_digits = "";
		for (string output : outputs)
		{
			output_digits += to_string(decode_item(decoder, output));
		}

		return stoi(output_digits);
	}
	
	int decode_item(const map<char, char>& decoder, string item)
	{
		vector<char> segments;
		for (char c : item)
		{
			segments.push_back(decoder.find(c)->second);
		}
		sort(begin(segments), end(segments));

		string segments_string(begin(segments), end(segments));

		return digits.find(segments_string)->second;
	}

	processing(
		const vector<string>& signals,
		const vector<string>& outputs
	) :
		signals(signals),
		outputs(outputs)
	{}

private:
	
	const vector<string>& signals;
	const vector<string>& outputs;

	vector<string> get_number_set(int length)
	{
		vector<string> ret;

		for (string s : signals)
		{
			if (s.length() == length)
			{
				ret.push_back(s);
			}
		}

		return ret;
	}

	string find_unique_chars(string large, string small)
	{
		string ret = "";
		//find the unique chars in the large string that aren't in the small one. 
		for (char c : large)
		{
			if (small.find(c) == string::npos) //npos is not found, so we'll take that. 
			{
				ret.append(1, c);
			}
		}
		return ret;
	}

	vector<string> find_fives_pairs()
	{
		vector<string> all_fives = get_number_set(5); //this will be of length 3. 
		vector<string> all_diffs;

		process_fives_pair(all_fives, all_diffs, 0, 1);
		process_fives_pair(all_fives, all_diffs, 0, 2);
		process_fives_pair(all_fives, all_diffs, 1, 2);

		return all_diffs;
	}

	void process_fives_pair(const vector<string>& all_fives, vector<string>& all_diffs, int index1, int index2)
	{
		string fives_overlap = find_unique_chars(all_fives[index1], all_fives[index2]) +
			find_unique_chars(all_fives[index2], all_fives[index1]);

		if (fives_overlap.length() == 2)
			all_diffs.push_back(fives_overlap);
	}



};


int main()
{
	string line;
	int outputs_sum = 0;

	while (getline(cin, line))
	{
		vector<string> signals;
		vector<string> outputs;
		string input;

		stringstream linestream{ line };
		for (int i = 0; i < 10; i++)
		{
			linestream >> input;
			signals.push_back(input);
		}
		linestream >> input; //skip pipe

		for (int i = 0; i < 4; i++)
		{
			linestream >> input;
			outputs.push_back(input);
		}

		processing p(signals, outputs);
		outputs_sum += p.decode_line_outputs(signals, outputs);
	}

	cout << "Sum of all output values: " << outputs_sum << endl;
}
