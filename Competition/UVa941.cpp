#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=882

#include "UVa941.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void compute_permutation(long long num_permutation, string ordering_string, vector<unsigned int> unused_positions)
{
	if (unused_positions.size() == 1)
	{
		cout << ordering_string[*(unused_positions.begin())];
	}
	else
	{
		// Compute (size - 1)!
		long long factorial = 1;
		for (unsigned int i = 1; i < unused_positions.size(); i++)
		{
			factorial *= i;
		}

		int position = num_permutation / factorial;

		vector<unsigned int>::iterator p = unused_positions.begin();
		for (int j = 0; j < position; j++)
		{
			p++;
		}
		cout << ordering_string[*p];

		unused_positions.erase(p);
		num_permutation -= position * factorial;
		compute_permutation(num_permutation, ordering_string, unused_positions);
	}
}

void compute_permutation(long long num_permutation, string ordering_string)
{
	vector<unsigned int> unused_positions;
	for (unsigned int i = 0; i < ordering_string.length(); i++)
	{
		unused_positions.push_back(i);
	}
	compute_permutation(num_permutation, ordering_string, unused_positions);
}

int UVa941()
{
	int number_of_cases;
	cin >> number_of_cases;
	for (int c = 0; c < number_of_cases; c++)
	{
		long long num_permutation;
		string ordering_string;
		cin >> ordering_string;
		for (unsigned int i = 0; i < ordering_string.length(); i++)
		{
			for (unsigned int j = i + 1; j < ordering_string.length(); j++)
			{
				if (ordering_string[i] > ordering_string[j])
				{
					char temp = ordering_string[i];
					ordering_string[i] = ordering_string[j];
					ordering_string[j] = temp;
				}
			}
		}
		cin >> num_permutation;

		// Computing ordering recursively
		compute_permutation(num_permutation, ordering_string);
		cout << endl;
	}

	return 0;
}