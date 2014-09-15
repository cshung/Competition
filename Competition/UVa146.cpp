#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=82

#include "UVa146.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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