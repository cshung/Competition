#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1305

#include "UVa10364.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

bool feasible(vector<int>& lengths, int length_target, int remaining_segments, int remaining_length, int starting_segment, int used_mask)
{
    if (remaining_segments == 0)
    {
        return true;
    }

    int bit = 1 << starting_segment;
    bool first_entry = (remaining_length == length_target);
    for (unsigned int i = starting_segment; i < lengths.size(); i++)
    {
        if ((used_mask & bit) == 0)
        {
            if (lengths[i] == remaining_length)
            {
                if (feasible(lengths, length_target, remaining_segments - 1, length_target, 0, used_mask | bit))
                {
                    return true;
                }
            }
            else if (lengths[i] < remaining_length)
            {
                if (feasible(lengths, length_target, remaining_segments, remaining_length - lengths[i], i + 1, used_mask | bit))
                {
                    return true;
                }
            }
            if (first_entry)
            {
                break;
            }
        }

        bit = bit << 1;        
    }

    return false;
}

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
            if (feasible(lengths, length_target, 4, length_target, 0, 0)) 
            {
                cout << "yes" << endl;
            }
            else
            {
                cout << "no" << endl;
            }
        }
        else
        {
            cout << "no" << endl;
        }
    }

    return 0;
}