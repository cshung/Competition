#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1082

#include "UVa10141.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int UVa10141()
{
	while (true)
	{
		int num_requirements;
		int num_proposals;
		cin >> num_requirements;
		cin >> num_proposals;
		vector<string> requirements;
		for (int r = 0; r < num_requirements; r++)
		{
			string requirement;
			getline(cin, requirement);
			requirements.push_back(requirement);
		}

	}
    return 0;
}