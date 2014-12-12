#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=288

#include "UVa352.h"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int UVa352_find(vector<int>& sets, int i)
{
    if (sets[i] < 0)
    {
        return i;
    }
    else
    {
        int result = UVa352_find(sets, sets[i]);
        sets[i] = result;
        return result;
    }
}

int UVa352()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;
        // Step 1: Read input
        int dimension;
        cin >> dimension;
        if (cin.eof())
        {
            break;
        }

        vector<vector<int> > image;
        image.resize(dimension);
        for (int row = 0; row < dimension; row++)
        {
            image[row].resize(dimension);
            char c;
            for (int col = 0; col < dimension; col++)
            {
                cin >> c;
                image[row][col] = c - '0';
            }
        }

        // Step 2: Disjoint set union find
        // Goal - count the number of sets
        // Each cell with a 1 is a set, union all the connected sets

        // Step 2.1: Construct the data structure (and index, and a vector representing the sets)
        int number_of_sets = 0;

        vector<vector<int> > index;
        vector<int> sets;
        index.resize(dimension);
        for (int row = 0; row < dimension; row++)
        {
            index[row].resize(dimension);
            for (int col = 0; col < dimension; col++)
            {
                if (image[row][col] == 1)
                {
                    index[row][col] = number_of_sets++;
                }
            }
        }
        sets.resize(number_of_sets);

        for (int i = 0; i < number_of_sets; i++)
        {
            // All sets have size 1
            sets[i] = -1;
        }

        // Step 2.2: Performing the union operations
        for (int src_row = 0; src_row < dimension; src_row++)
        {
            for (int src_col = 0; src_col < dimension; src_col++)
            {
                if (image[src_row][src_col] == 1)
                {
                    int src_index = index[src_row][src_col];
                    vector<pair<int, int> > candidates;
                    candidates.push_back(pair<int, int>(src_row - 1, src_col - 1));
                    candidates.push_back(pair<int, int>(src_row - 1, src_col));
                    candidates.push_back(pair<int, int>(src_row - 1, src_col + 1));
                    candidates.push_back(pair<int, int>(src_row, src_col - 1));
                    candidates.push_back(pair<int, int>(src_row, src_col + 1));
                    candidates.push_back(pair<int, int>(src_row + 1, src_col - 1));
                    candidates.push_back(pair<int, int>(src_row + 1, src_col));
                    candidates.push_back(pair<int, int>(src_row + 1, src_col + 1));
                    for (unsigned ci = 0; ci < candidates.size(); ci++)
                    {
                        int dst_row = candidates[ci].first;
                        int dst_col = candidates[ci].second;
                        if (0 <= dst_row && dst_row < dimension)
                        {
                            if (0 <= dst_col && dst_col < dimension)
                            {
                                if (image[dst_row][dst_col] == 1)
                                {
                                    int dst_index = index[dst_row][dst_col];
                                    int src_root = UVa352_find(sets, src_index);
                                    int dst_root = UVa352_find(sets, dst_index);

                                    if (src_root != dst_root)
                                    {
                                        if (sets[src_root] < sets[dst_root]) // src_index is a larger set
                                        {
                                            sets[src_root] = sets[src_root] + sets[dst_root];
                                            sets[dst_root] = src_root;
                                        }
                                        else 
                                        {
                                            sets[dst_root] = sets[src_root] + sets[dst_root];
                                            sets[src_root] = dst_root;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Step 2.3: Extract the number of sets
        int num_sets = 0;
        for (unsigned i = 0; i < sets.size(); i++)
        {
            if (sets[i] < 0)
            {
                num_sets++;
            }
        }

        // Step 3: Output
        cout << "Image number " << test_case_number << " contains " << num_sets <<" war eagles." << endl;
        
    }


    return 0;
}