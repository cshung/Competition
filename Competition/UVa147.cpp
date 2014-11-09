#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=83

#include "UVa147.h"
#include <iostream>
#include <iomanip>

typedef long long int64;

using namespace std;

int UVa147()
{
    const int num_values = 11;
    int values[num_values] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    int values_in_5_cents[num_values];
    for (int i = 0; i < num_values; i++)
    {
        values_in_5_cents[i] = values[i] / 5;
    }

    const int max_dollars = 300;
    const int max_cents = max_dollars * 100;
    const int max_in_5_cents = max_cents / 5;

    // ways[i, j] represents the number of ways (i * 5) cents can be represented using the first [0, j] values
    int64 ways[max_in_5_cents + 1][num_values];
    for (int j = 0; j < num_values; j++)
    {
        ways[0][j] = 1; // There is only one way to represent 0 cents no matter what values are allowed
    }

    for (int i = 1; i <= max_in_5_cents; i++)
    {
        // Step 1: The number of ways to represent i * 5 cents in terms of just using a 5 cents is 1.
        ways[i][0] = 1;

        // Step 2: The number of ways to represent i * 5 cents in terms of using values[0] .. values[j] is
        // Choosing how many instance of of the largest value to use
        // and then just sum the rest
        for (int j = 1; j < num_values; j++)
        {
            int current = values_in_5_cents[j];
            int64 way = 0;
            for (int n = 0; n <= i / current; n++)
            {
                way += ways[i - n * current][j - 1];
            }
            ways[i][j] = way;
        }
    }

    while (true)
    {
        double value;
        cin >> value;
        if (value < 0.05)
        {
            break;
        }

        // Be careful with the rounding here - thanks to the forum I know (int)(2.05 * 20) = 40, which is not what I want.
        int value_in_5_cents = (int)(value * 100 / 5 + 0.1);
        cout << right << setw(6) << setprecision(2) << fixed << value << right << setw(17) << ways[value_in_5_cents][num_values - 1] << endl;
    }
    return 0;
}