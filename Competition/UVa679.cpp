#include "stdafx.h"

// http://uva.onlinejudge.org/external/6/679.html

#include "UVa679.h"

#include <iostream>
#include <bitset>

using namespace std;

// #define simulation

int UVa679()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int depth;
        int drops;
        int number_of_internal_nodes = 1;

        cin >> depth;
        cin >> drops;

#ifdef simulation
        // We don't need to keep the flag for the leaves
        for (int d = 0; d < (depth - 1); d++)
        {
            number_of_internal_nodes *= 2;
        }
        number_of_internal_nodes--;

        bool* tree = new bool[number_of_internal_nodes];

        for (int i = 0; i < number_of_internal_nodes; i++)
        {
            tree[i] = false;
        }

        for (int i = 0; i < drops; i++)
        {
            int ball_position = 1; 
            // The ball only go down (depth - 1) times
            for (int j = 0; j < depth - 1; j++) 
            {
                if (tree[ball_position - 1] == false)
                {
                    tree[ball_position - 1] = true;
                    // Go to left
                    ball_position = ball_position * 2;
                }
                else
                {
                    tree[ball_position - 1] = false;
                    ball_position = ball_position * 2 + 1;
                }
            }

            // Showing the leaf number for all drops
            // cout << ball_position << endl;

            // Showing the binary representation of the solution
            cout << bitset<8>(ball_position) << endl;
        }

        delete[] tree;
#else
        /* 
         * The key to this smart algorithm is based on the observation of the sequence in binary form.
         * Running the simulation and shows the sequence in binary can easily reveal the pattern.
         */

        // The binary algorithm starts with 0 drops
        drops--;
        int solution = 0;

        for (int i = 0; i < (depth - 1); i++)
        {
            // Computing the ith bit
            if (drops >= 1 << (depth - 2 - i))
            {
                drops -= 1 << (depth - 2 - i);
                solution += 1 << i;
            }
        }
        solution += 1 << (depth - 1);
        
        cout << solution << endl;
#endif
    }

    return 0;
}