#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=52

#include "UVa116.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

int UVa116()
{
    while (true)
    {
        int num_rows;
        int num_cols;
        cin >> num_rows;
        if (cin.eof())
        {
            break;
        }
        cin >> num_cols;
        vector<vector<int> > input;
        input.resize(num_rows);
        for (int r = 0; r < num_rows; r++)
        {
            input[r].resize(num_cols);
            for (int c = 0; c < num_cols; c++)
            {
                cin >> input[r][c];
            }
        }

        vector<int64> best_cost;
        vector<int64> next_best_cost;
        vector<vector<int> > next;

        best_cost.resize(num_rows);
        next_best_cost.resize(num_rows);
        next.resize(num_rows);

        // The virtual last column has no cost associated with it
        for (int r = 0; r < num_rows; r++)
        {
            next_best_cost[r] = 0;
            next[r].resize(num_cols);
        }

        for (int c = num_cols - 1; c >= 0; c--)
        {
            for (int r = 0; r < num_rows; r++)
            {
                int previous_row = (r == 0) ? num_rows - 1 : r - 1;
                int next_row = (r + 1) % num_rows;
                int64 previous_cost = next_best_cost[previous_row];
                int64 current_cost = next_best_cost[r];
                int64 next_cost = next_best_cost[next_row];
                int64 best_next_cost = min(previous_cost, min(current_cost, next_cost));
                best_cost[r] = input[r][c] + best_next_cost;
                int next_min = -1;
                bool first = true;

                if (best_next_cost == previous_cost)
                {
                    if (first)
                    {
                        next_min = previous_row;
                        first = false;
                    }
                    else
                    {
                        next_min = min(previous_row, next_min);
                    }
                } 
                if (best_next_cost == current_cost)
                {
                    if (first)
                    {
                        next_min = r;
                        first = false;
                    }
                    else
                    {
                        next_min = min(r, next_min);
                    }
                }
                if (best_next_cost == next_cost)
                {
                    if (first)
                    {
                        next_min = next_row;
                        first = false;
                    }
                    else
                    {
                        next_min = min(next_row, next_min);
                    }
                }
                next[r][c] = next_min;
            }
            for (int r = 0; r < num_rows; r++)
            {
                next_best_cost[r] = best_cost[r];
            }
#if LOG
            cout << "Col: " << c << endl;
            for (int r = 0; r < num_rows; r++)
            {
                cout << best_cost[r] << " " << next[r][c] << endl;
            }
            cout << "---" << endl;
#endif
        }

        bool first = true;
        int64 best_row_cost = -1;
        int best_row_index = 0;
        for (int r = 0; r < num_rows; r++)
        {
            if (first)
            {
                best_row_cost = best_cost[r];
                best_row_index = r;
                first = false;
            }
            else if (best_cost[r] < best_row_cost)
            {
                best_row_cost = best_cost[r];
                best_row_index = r;
                first = false;
            }
        }
        int best_row = best_row_index;
        for (int c = 0; c < num_cols; c++)
        {
            if (c != 0)
            {
                cout << " ";
            }
            cout << (best_row + 1);
            best_row = next[best_row][c];
        }
        cout << endl << best_row_cost << endl;
    }
    return 0;
}