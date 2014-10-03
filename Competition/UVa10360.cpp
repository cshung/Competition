#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1301

#include "UVa10360.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct rat_population
{
    int x;
    int y;
    int size;
};

bool sort_by_x(rat_population* first, rat_population* second)
{
    return first->x < second->x;
}

bool sort_by_y(rat_population* first, rat_population* second)
{
    return first->y < second->y;
}

int UVa10360()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        // Step 1: Read input
        int strength;
        cin >> strength;
        int num_rat_populations;
        cin >> num_rat_populations;
        list<rat_population*> rat_populations;
        for (int p = 0; p < num_rat_populations; p++)
        {
            rat_population* current_line = new rat_population();
            cin >> current_line->x;
            cin >> current_line->y;
            cin >> current_line->size;
            rat_populations.push_back(current_line);
        }

        // Step 2: Build a spatial index using kd-tree
        vector<rat_population*> x_sorted_rat_populations;
        vector<rat_population*> y_sorted_rat_populations;

        // Step 2.1: Pre-sort the points
        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            x_sorted_rat_populations.push_back(*ri);
            y_sorted_rat_populations.push_back(*ri);
        }
        sort(x_sorted_rat_populations.begin(), x_sorted_rat_populations.end(), sort_by_x);
        sort(y_sorted_rat_populations.begin(), y_sorted_rat_populations.end(), sort_by_y);

        // Step 2.2: Recursively build the tree
        /// ...

        // Step 3: Search for answer
        int bestBombX = 0;
        int bestBombY = 0;
        int maxDeadRats = -1;

        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            // TODO: enhance the bounds, no point bombing outside boundary
            int minBombX = max(0, (*ri)->x - strength);
            int maxBombX = min(1024, (*ri)->x + strength);
            int minBombY = max(0, (*ri)->y - strength);
            int maxBombY = min(1024, (*ri)->y + strength);
            
            for (int bombX = minBombX; bombX <= maxBombX; bombX++)
            {
                for (int bombY = minBombY; bombY <= maxBombY; bombY++)
                {
                    int deadRats = 0;
                    // Time limit exceeded - as I would expect - we really need a spatial index here
                    for (list<rat_population*>::iterator ti = rat_populations.begin(); ti != rat_populations.end(); ti++)
                    {
                        if (abs(bombX - (*ti)->x) <= strength && abs(bombY - (*ti)->y) <= strength)
                        {
                            deadRats += (*ti)->size;
                        }
                    }
                    if (deadRats > maxDeadRats)
                    {
                        maxDeadRats = deadRats;
                        bestBombX = bombX;
                        bestBombY = bombY;
                    }
                }
            }
        }
        cout << bestBombX << " " << bestBombY << " " << maxDeadRats << endl;

        // Step 4: Release dynamicaly allocated memory
        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            delete (*ri);
        }
    }

    return 0;
}