#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2267

#include "UVa11292.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int UVa11292()
{
    while (true)
    {
        int number_of_heads, number_of_knights;
        cin >> number_of_heads;
        cin >> number_of_knights;
        if (number_of_heads == 0 && number_of_knights == 0)
        {
            break;
        }
        vector<int> head_diameters;
        vector<int> knight_heights;
        for (int h = 0; h < number_of_heads; h++)
        {
            int head_diameter;
            cin >> head_diameter;
            head_diameters.push_back(head_diameter);
        }
        for (int k = 0; k < number_of_knights; k++)
        {
            int knight_height;
            cin >> knight_height;
            knight_heights.push_back(knight_height);
        }
        sort(head_diameters.begin(), head_diameters.end());
        sort(knight_heights.begin(), knight_heights.end());
        unsigned int j = 0;
        int cost = 0;
        for (int i = 0; i < number_of_heads; i++)
        {
            while (j < knight_heights.size() && head_diameters[i] > knight_heights[j])
            {
                j++;
            }
            if (j == knight_heights.size())
            {
                cout << "Loowater is doomed!" << endl;
                cost = -1;
                break;
            }
            else
            {
                cost += knight_heights[j];
                j++;
            }
        }
        if (cost > 0)
        {
            cout << cost << endl;
        }
    }
    return 0;
}