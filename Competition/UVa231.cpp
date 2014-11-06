#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=167

#include "UVa231.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UVa231()
{
    int c = 0;
    while (true)
    {
        c++;
        vector<int> missile_heights;
        while (true)
        {
            int missile_height;
            cin >> missile_height;
            if (missile_height == -1)
            {
                break;
            }

            missile_heights.push_back(missile_height);
        }

        if (missile_heights.size() == 0)
        {
            break;
        }

        // represents the longest_non_increasing_sequence_length that ends at the index
        vector<int> longest_non_increasing_sequence_lengths;
        longest_non_increasing_sequence_lengths.push_back(1);

        // represents the longest_non_increasing_sequence_length that ends at any index
        int the_longest_non_increasing_sequence_length = 1;

        for (unsigned int i = 1; i < missile_heights.size(); i++)
        {
            int longest_non_increasing_sequence_length = 1;
            for (unsigned int j = 0; j < i; j++)
            {
                if (missile_heights[j] >= missile_heights[i])
                {
                    longest_non_increasing_sequence_length = longest_non_increasing_sequence_lengths[j] + 1;
                }
            }

            longest_non_increasing_sequence_lengths.push_back(longest_non_increasing_sequence_length);
            the_longest_non_increasing_sequence_length = max(the_longest_non_increasing_sequence_length, longest_non_increasing_sequence_length);
        }

        if (c != 1)
        {
            cout << endl;
        }

        cout << "Test #" << c << ":" << endl;
        cout << "  maximum possible interceptions : " << the_longest_non_increasing_sequence_length << endl;
    }
   return 0;
}