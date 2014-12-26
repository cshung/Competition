#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=410

#include "UVa469.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int UVa469_find(int item, vector<int>& sets);

int UVa469()
{
    int number_of_test_case;
    cin >> number_of_test_case;

    string line;
    getline(cin, line); // Consume the endline after the test case number
    getline(cin, line); // Consume the blank line

    for (int test_case = 1; test_case <= number_of_test_case; test_case++)
    {
        // Step 1: Input the grid
        getline(cin, line); // Prefetching the first line in the test case
        vector<string> lines;
        while (true)
        {
            if (line.length() > 0 && (line[0] == 'L' || line[0] == 'W'))
            {
                lines.push_back(line);
            }
            else
            {
                break;
            }
            getline(cin, line);
        }

        // Step 2: Form the disjoint sets for the grid
        int num_rows = lines.size();
        int num_cols = lines[0].length();
        int num_cells = num_rows * num_cols;

        // Step 2.1: Allocate disjoint sets
        vector<int> disjoint_sets;
        disjoint_sets.resize(num_cells);
        for (int c = 0; c < num_cells; c++)
        {
            disjoint_sets[c] = -1;
        }

        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                if (lines[r][c] == 'W')
                {
                    vector<pair<int, int> > neighbor_candidates;
                    neighbor_candidates.push_back(pair<int, int>(r - 1, c - 1));
                    neighbor_candidates.push_back(pair<int, int>(r - 1, c + 0));
                    neighbor_candidates.push_back(pair<int, int>(r - 1, c + 1));
                    neighbor_candidates.push_back(pair<int, int>(r + 0, c - 1));
                    neighbor_candidates.push_back(pair<int, int>(r + 0, c + 1));
                    neighbor_candidates.push_back(pair<int, int>(r + 1, c - 1));
                    neighbor_candidates.push_back(pair<int, int>(r + 1, c + 0));
                    neighbor_candidates.push_back(pair<int, int>(r + 1, c + 1));
                    for (vector<pair<int, int> >::iterator nci = neighbor_candidates.begin(); nci != neighbor_candidates.end(); nci++)
                    {
                        int ncr = nci->first;
                        int ncc = nci->second;
                        if (0 <= ncr && ncr < num_rows && 0 <= ncc && ncc < num_cols)
                        {
                            if (lines[ncr][ncc] == 'W')
                            {

                                int src = r * num_cols + c;
                                int dst = ncr * num_cols + ncc;

                                int src_set = UVa469_find(src, disjoint_sets);
                                int dst_set = UVa469_find(dst, disjoint_sets);

                                if (src_set != dst_set)
                                {
                                    // Union 
                                    if (disjoint_sets[src_set] < disjoint_sets[dst_set]) // src_set is larger
                                    {
                                        disjoint_sets[src_set] = disjoint_sets[src_set] + disjoint_sets[dst_set]; // size increased
                                        disjoint_sets[dst_set] = src_set;                                         // union
                                    }
                                    else
                                    {
                                        disjoint_sets[dst_set] = disjoint_sets[src_set] + disjoint_sets[dst_set]; // size increased
                                        disjoint_sets[src_set] = dst_set;                                         // union
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (test_case != 1)
        {
            cout << endl;
        }

        while (true)
        {
            istringstream iss(line);
            int row;
            int col;
            iss >> row;
            iss >> col;

            cout << -disjoint_sets[UVa469_find((row-1) * num_cols + (col-1), disjoint_sets)] << endl;
            if (cin.eof())
            {
                break;
            }
            getline(cin, line);
            if (line == "")
            {
                break;
            }
        }
    }
    return 0;
}

int UVa469_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa469_find(sets[item], sets);
    }
}