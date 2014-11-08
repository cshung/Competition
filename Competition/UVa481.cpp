#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=422

#include "UVa481.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int UVa481()
{
    vector<int> input;
    while (true)
    {
        int value;
        cin >> value;
        if (cin.eof())
        {
            break;
        }
        input.push_back(value);
    }

    vector<int> parent;
    parent.resize(input.size());
    vector<int> active_sequence_ends;
    vector<int> active_sequence_indices;

    // Initialize
    parent[0] = -1;
    active_sequence_ends.push_back(input[0]);
    active_sequence_indices.push_back(0);

    for (unsigned int i = 1; i < input.size(); i++)
    {
        // Step 1: Find the active sequence
        unsigned int index = lower_bound(active_sequence_ends.begin(), active_sequence_ends.end(), input[i]) - active_sequence_ends.begin();

        // At this point - index is pointing to the element not less than input[i], which means we should 
        // Case 1: input[i] is the least element, active_sequence_ends[0] should be updated
        // Case 2: input[i] can extend the sequence of length 2, so index should be 3 right now
        // Case 3: input[i] is the maximum element, the longest element can be extended, so extend it
        if (index == active_sequence_ends.size())
        {
            parent[i] = active_sequence_indices[active_sequence_indices.size() - 1];
            active_sequence_ends.push_back(input[i]);
            active_sequence_indices.push_back(i);
        }
        else 
        {
            if (index == 0)
            {
                parent[i] = -1;
            }
            else
            {
                parent[i] = active_sequence_indices[index - 1];
            }
            active_sequence_ends[index] = input[i];
            active_sequence_indices[index] = i;
        }
    }
    cout << active_sequence_ends.size() << endl;
    cout << "-" << endl;
    int index = active_sequence_indices[active_sequence_indices.size() - 1];
    list<int> result;
    while (index != -1)
    {
        result.push_front(input[index]);
        index = parent[index];
    }
    for (list<int>::iterator i = result.begin(); i != result.end(); i++)
    {
        cout << *i << endl;
    }
    return 0;
}