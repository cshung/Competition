#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36

#include "UVa100.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int cycle_length(unsigned int input, map<unsigned int, int>& cycle_lengths)
{
    if (input == 1)
    {
        return 1;
    }

    map<unsigned int, int>::iterator probe = cycle_lengths.find(input);
    if (probe != cycle_lengths.end())
    {
        return probe->second;
    }

    unsigned int recursive_input;

    if (input % 2 == 0)
    {
        recursive_input = input / 2;
    }
    else
    {
        recursive_input = input * 3 + 1;
    }

    return cycle_lengths[input] = (1 + cycle_length(recursive_input, cycle_lengths));
}

int UVa100()
{
    // Ideally we would have use the stack - but that will stack overflow
    map<unsigned int, int> cycle_lengths;

    int i, j, min_index, max_index;

    do
    {
        cin >> i;
        cin >> j;
        if (cin.fail())
        {
            break;
        }

        if (i > j)
        {
            min_index = j; max_index = i;
        }
        else
        {
            min_index = i; max_index = j;
        }

        int max_cycle_length = -1;
        for (int index = min_index; index <= max_index; index++)
        {
            int cycle_length_of_index = cycle_length(index, cycle_lengths);
            if (cycle_length_of_index > max_cycle_length)
            {
                max_cycle_length = cycle_length_of_index ;
            }
        }

        cout << i << " " << j << " " << max_cycle_length << endl;
    } 
    while (!cin.eof());

    return 0;
}