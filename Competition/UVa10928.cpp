#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1869 

#include "UVa10928.h"

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

int UVa10928()
{
    int number_of_cases;
    cin >> number_of_cases;
    string line;
    for (int c = 0; c < number_of_cases; c++)
    {
        list<int> neighbor_counts;
        int number_of_places;
        cin >> number_of_places;
        int min_neighbor = -1;
        getline(cin, line); /* consume the endline */
        for (int p = 0; p < number_of_places; p++)
        {
            getline(cin, line); 
            int number_of_neighbors = 1;
            for (unsigned int s = 0; s < line.length(); s++)
            {
                if (line[s] == ' ')
                {
                    number_of_neighbors++;
                }
            }
            neighbor_counts.push_back(number_of_neighbors);
            if (p == 0)
            {
                min_neighbor = number_of_neighbors;
            }
            else
            {
                min_neighbor = min(min_neighbor, number_of_neighbors);
            }
        }

        int place_index = 1;
        bool printed = false;
        for (list<int>::iterator nci = neighbor_counts.begin(); nci != neighbor_counts.end(); nci++)
        {
            if (*nci == min_neighbor)
            {
                if (printed)
                {
                    cout << " ";
                }
                else
                {
                    printed = true;
                }
                cout << place_index;
            }
            place_index++;
        }
        cout << endl;
    }

    return 0;
}