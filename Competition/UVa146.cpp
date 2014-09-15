#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=82

#include "UVa146.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Would be nice to know what next_permutation actually do
 * I *think* this algorithm would work
 * Scan from the second last element to see if any element on the left of it greater than it.
 * For the first one that does pick the smallest of them on the left and replace self
 * Sort the rest on the left and output
 * 
 * Return false if scan fails
 */
int UVa146()
{
    vector<char> line;
    while (!cin.eof())
    {   
        char c = cin.get();
        if (c != -1)
        {
            if (c != '\r' && c != '\n')
            {
                if (c == '#')
                {
                    break;
                }
                line.push_back(c);
            }
            else
            {
                if (next_permutation(line.begin(), line.end()))
                {
                    for (vector<char>::iterator i = line.begin(); i != line.end(); i++)
                    {
                        cout << *i;
                    }
                    cout << endl;
                }
                else
                {
                    cout << "No Successor" << endl;
                }
                line.clear();
            }
        }
    }

    return 0;
}