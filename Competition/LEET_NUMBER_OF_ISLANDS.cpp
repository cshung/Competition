#include "stdafx.h"

// https://leetcode.com/problems/number-of-islands/

#include "LEET_NUMBER_OF_ISLANDS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_NUMBER_OF_ISLANDS
{
    class Solution
    {
    private:
        int find_disjoint_set(vector<int>& disjoint_sets, int set1)
        {
            if (disjoint_sets[set1] < 0)
            {
                return set1;
            }
            else
            {
                return (disjoint_sets[set1] = find_disjoint_set(disjoint_sets, disjoint_sets[set1]));
            }
        }

        void union_disjoint_set(vector<int>& disjoint_sets, int set1, int set2)
        {
            int set1rep = find_disjoint_set(disjoint_sets, set1);
            int set2rep = find_disjoint_set(disjoint_sets, set2);
            if (set1rep != set2rep)
            {
                int set1size = -disjoint_sets[set1rep];
                int set2size = -disjoint_sets[set2rep];
                if (set1size < set2size)
                {
                    disjoint_sets[set1rep] = set2rep;
                    disjoint_sets[set2rep] = -(set1size + set2size);
                }
                else
                {
                    disjoint_sets[set2rep] = set1rep;
                    disjoint_sets[set1rep] = -(set1size + set2size);
                }
            }
        }
    public:
        int numIslands(vector<vector<char>>& grid)
        {
            int height = grid.size();
            if (height == 0)
            {
                return 0;
            }
            int width = grid[0].size();
            if (width == 0)
            {
                return 0;
            }

            // Step 1: Initialize the size of the disjoint sets to be -1
            int size = height * width;
            vector<int> disjoint_sets;
            disjoint_sets.resize(size);
            for (int i = 0; i < size; i++)
            {
                disjoint_sets[i] = -1;
            }

            // Step 2: Union!
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width - 1; col++)
                {
                    if (grid[row][col] == grid[row][col + 1])
                    {
                        int set1 = row * width + col;
                        int set2 = row * width + col + 1;
                        union_disjoint_set(disjoint_sets, set1, set2);
                    }
                }
            }
            for (int row = 0; row < height - 1; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    if (grid[row][col] == grid[row + 1][col])
                    {
                        int set1 = row * width + col;
                        int set2 = (row + 1) * width + col;
                        union_disjoint_set(disjoint_sets, set1, set2);
                    }
                }
            }

            // Step 3: Count
            int count = 0;
            for (int i = 0; i < size; i++)
            {
                if (disjoint_sets[i] < 0)
                {
                    int row = i / width;
                    int col = i % width;
                    if (grid[row][col] == '1')
                    {
                        count++;
                    }
                }
            }
            return count;
        }
    };
};

using namespace _LEET_NUMBER_OF_ISLANDS;

int LEET_NUMBER_OF_ISLANDS()
{
    Solution s;
    char row11[] = {'1', '1', '1', '1', '0'};
    char row12[] = {'1', '1', '0', '1', '0'};
    char row13[] = {'1', '1', '0', '0', '0'};
    char row14[] = {'0', '0', '0', '0', '0'};

    vector<vector<char>> grid1;
    grid1.push_back(vector<char>(row11, row11 + _countof(row11)));
    grid1.push_back(vector<char>(row12, row12 + _countof(row12)));
    grid1.push_back(vector<char>(row13, row13 + _countof(row13)));
    grid1.push_back(vector<char>(row14, row14 + _countof(row14)));
    cout << s.numIslands(grid1) << endl;
    return 0;
}