#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1305

#include "UVa10364.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int UVa10364()
{
    int num_test_case;
    cin >> num_test_case;
    for (int c = 0; c < num_test_case; c++)
    {
        int num_sticks;
        cin >> num_sticks;
        vector<int> lengths;
        lengths.resize(num_sticks);
        int length_sum = 0;
        for (int s = 0; s < num_sticks; s++)
        {
            int length;
            cin >> length;
            lengths[s] = length;
            length_sum += length;
        }

        if (length_sum % 4 == 0)
        {
            int length_target = length_sum / 4;
            
        }
        else
        {
            cout << "no" << endl;
        }
    }

    return 0;
}