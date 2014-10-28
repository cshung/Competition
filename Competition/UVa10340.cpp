#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1281

#include "UVa10340.h"

#include <iostream>
#include <string>

using namespace std;

int UVa10340()
{
    while (true)
    {
        string first_string;
        string second_string;
        cin >> first_string;
        if (cin.eof())
        {
            break;
        }
        cin >> second_string;
        unsigned int first_pointer = 0;
        unsigned int second_pointer = 0;
        while (first_pointer < first_string.length() && second_pointer < second_string.length())
        { 
            if (first_string[first_pointer] == second_string[second_pointer])
            {
                first_pointer++;
                second_pointer++;
            }
            else
            {
                second_pointer++;
            }
        }
        if (first_pointer == first_string.length())
        {
            cout << "Yes" << endl;
        }
        else 
        {
            cout << "No" << endl;
        }
    }
    return 0;
}