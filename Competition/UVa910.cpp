#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=851

#include "UVa910.h"

#include <iostream>
#include <vector>

using namespace std;

int UVa910()
{
    while (true)
    {
        // Step 1: Read Input
        int number_of_nodes;
        cin >> number_of_nodes;
        if (cin.eof())
        {
            break;
        }
        vector<vector<int> > adjacency_list;
        vector<bool> mode;
        adjacency_list.resize(number_of_nodes);
        mode.resize(number_of_nodes);
        for (int i = 0; i < number_of_nodes; i++)
        {            
            char from;
            char to1;
            char to2;
            char mode_char;
            cin >> from;
            cin >> to1;
            cin >> to2;
            cin >> mode_char;
            adjacency_list[from - 'A'].resize(2);
            adjacency_list[from - 'A'][0] = to1 - 'A';
            adjacency_list[from - 'A'][1] = to2 - 'A';
            mode[from - 'A'] = (mode_char == 'x');
        }
        int steps;
        cin >> steps;

        // Step 2: Dynamic programming
        vector<int> old_ways;
        vector<int> new_ways;
        old_ways.resize(number_of_nodes);
        new_ways.resize(number_of_nodes);

        for (int i = 0; i < number_of_nodes; i++)
        {
            old_ways[i] = 0;
        }
        old_ways[0] = 1;
        
        for (int s = 0; s < steps; s++)
        {
            for (int n = 0; n < number_of_nodes; n++)
            {
                new_ways[n] = 0;
            }
            for (int n = 0; n < number_of_nodes; n++)
            {
                new_ways[adjacency_list[n][0]] = new_ways[adjacency_list[n][0]] + old_ways[n];
                new_ways[adjacency_list[n][1]] = new_ways[adjacency_list[n][1]] + old_ways[n];
            }
            for (int n = 0; n < number_of_nodes; n++)
            {
                old_ways[n] = new_ways[n];
            }            
        }

        int win_ways = 0;
        for (int n = 0; n < number_of_nodes; n++)
        {
            if (mode[n])
            {
                win_ways += old_ways[n];
            }
        }
        cout << win_ways << endl;
    }

    return 0;
}