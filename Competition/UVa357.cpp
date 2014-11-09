#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=293

#include "UVa357.h"
#include <iostream>
#include <iomanip>

typedef long long int64;

using namespace std;

const int UVa357_num_values = 5;
int values[UVa357_num_values] = {1, 5, 10, 25, 50};
const int UVa357_max_cents = 30000;
// ways[i, j] represents the number of ways i cents can be represented using the first [0, j] values
int64 UVa357_ways[UVa357_max_cents + 1][UVa357_num_values];

int UVa357()
{
    for (int j = 0; j < UVa357_num_values; j++)
    {
        UVa357_ways[0][j] = 1; // There is only one way to represent 0 cents no matter what values are allowed
    }

    for (int i = 1; i <= UVa357_max_cents; i++)
    {
        // Step 1: The number of ways to represent i cents in terms of just using a 1 cents is 1.
        UVa357_ways[i][0] = 1;

        // Step 2: The number of ways to represent i cents in terms of using values[0] .. values[j] is
        // Choosing how many instance of of the largest value to use
        // and then just sum the rest
        for (int j = 1; j < UVa357_num_values; j++)
        {
            int current = values[j];
            int64 way = 0;
            for (int n = 0; n <= i / current; n++)
            {
                way += UVa357_ways[i - n * current][j - 1];
            }
            UVa357_ways[i][j] = way;
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
        int64 way = UVa357_ways[value][UVa357_num_values - 1];
        if (way == 1)
        {
            cout << "There is only 1 way";
        }
        else
        {
            cout << "There are " << way << " ways";
        }
        cout << " to produce " << value << " cents change." << endl;
    }
    return 0;
}