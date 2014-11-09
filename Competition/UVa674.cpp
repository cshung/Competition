#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=615

#include "UVa674.h"
#include <iostream>
#include <iomanip>

typedef long long int64;

using namespace std;

const int UVa674_num_values = 5;
int UVa674_values[UVa674_num_values] = {1, 5, 10, 25, 50};
const int UVa674_max_cents = 7489;
// ways[i, j] represents the number of ways i cents can be represented using the first [0, j] values
int64 UVa674_ways[UVa674_max_cents + 1][UVa674_num_values];

int UVa674()
{
    for (int j = 0; j < UVa674_num_values; j++)
    {
        UVa674_ways[0][j] = 1; // There is only one way to represent 0 cents no matter what values are allowed
    }

    for (int i = 1; i <= UVa674_max_cents; i++)
    {
        // Step 1: The number of ways to represent i cents in terms of just using a 1 cents is 1.
        UVa674_ways[i][0] = 1;

        // Step 2: The number of ways to represent i cents in terms of using values[0] .. values[j] is
        // Choosing how many instance of of the largest value to use
        // and then just sum the rest
        for (int j = 1; j < UVa674_num_values; j++)
        {
            int current = UVa674_values[j];
            int64 way = 0;
            for (int n = 0; n <= i / current; n++)
            {
                way += UVa674_ways[i - n * current][j - 1];
            }
            UVa674_ways[i][j] = way;
        }
    }

    while (!cin.eof())
    {
        int value;
        cin >> value;
        if (cin.fail())
        {
            break;
        }
        cout << UVa674_ways[value][UVa674_num_values - 1] << endl;
    }
    return 0;
}