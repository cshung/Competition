#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1184

#include "UVa10243.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

pair<int, int> UVa10243_dfs(int parent, int current, vector<vector<int> >& adjacency_list)
{
    vector<pair<int, int> > results;
    for (vector<int>::iterator ai = adjacency_list[current].begin(); ai != adjacency_list[current].end(); ai++)
    {
        if (*ai != parent)
        {
            results.push_back(UVa10243_dfs(current, *ai, adjacency_list));
        }
    }

    if (results.size() == 0)
    {
        // Leaf case
        if (parent != -1)
        {
            return pair<int, int>(0, 1);
        }
        else
        {
            return pair<int, int>(1, 1);
        }
    }
    else
    {
        int free_sum = 0;
        int force_sum = 0;
        for (vector<pair<int, int> >::iterator ri = results.begin(); ri != results.end(); ri++)
        {
            free_sum += ri->first;
            force_sum += ri->second;
        }

        int selected_result = 1 + free_sum;     
        int not_selected_result = force_sum; 

        return pair<int, int>(min(selected_result, not_selected_result), selected_result);
    }
}

int UVa10243()
{
    while (true)
    {
        // Step 1: Read input
        int number_of_galleries;
        cin >> number_of_galleries;
        if (number_of_galleries == 0)
        {
            break;
        }
        vector<vector<int> > adjacency_list;
        adjacency_list.resize(number_of_galleries);
        for (int i = 0; i < number_of_galleries; i++)
        {
            int number_of_adjacent_galleries;
            cin >> number_of_adjacent_galleries;
            adjacency_list[i].resize(number_of_adjacent_galleries);
            for (int a = 0; a < number_of_adjacent_galleries; a++)
            {
                int adjacent_gallery;
                cin >> adjacent_gallery;
                adjacency_list[i][a] = adjacent_gallery - 1;
            }
        }

        // Step 2: dfs for the answer
        pair<int, int> result = UVa10243_dfs(-1, 0, adjacency_list);
        cout << result.first << endl;
    }

    return 0;
}