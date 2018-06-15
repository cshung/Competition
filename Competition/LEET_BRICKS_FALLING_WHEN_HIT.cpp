#include "stdafx.h"

// https://leetcode.com/problems/bricks-falling-when-hit

#include "LEET_BRICKS_FALLING_WHEN_HIT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BRICKS_FALLING_WHEN_HIT
{
    class Solution
    {
    public:

        int do_find(vector<int>& disjoint_set, int s)
        {
            if (disjoint_set[s] < 0)
            {
                return s;
            }
            else
            {
                return disjoint_set[s] = do_find(disjoint_set, disjoint_set[s]);
            }
        }

        void do_union(vector<int>& disjoint_set, int left, int right)
        {
            int left_find = do_find(disjoint_set, left);
            int right_find = do_find(disjoint_set, right);
            if (left_find != right_find)
            {
                int left_size = -disjoint_set[left_find];
                int right_size = -disjoint_set[right_find];
                int total_size = left_size + right_size;
                if (left_size < right_size)
                {
                    disjoint_set[left_find] = right_find;
                    disjoint_set[right_find] = -total_size;
                }
                else
                {
                    disjoint_set[right_find] = left_find;
                    disjoint_set[left_find] = -total_size;
                }
            }
        }

        void union_with_neighbors(vector<vector<int>>& grid, vector<int>& disjoint_set, int row, int col)
        {
            int num_rows = grid.size();
            int num_cols = grid[0].size();
            int size = num_rows * num_cols;
            int cell_id = row * num_cols + col;
            if (grid[row][col] == 1)
            {
                if (row == 0)
                {
                    do_union(disjoint_set, cell_id, size);
                }
                if (row != 0 && grid[row - 1][col] == 1)
                {
                    do_union(disjoint_set, cell_id, cell_id - num_cols);
                }
                if (row != num_rows - 1 && grid[row + 1][col] == 1)
                {
                    do_union(disjoint_set, cell_id, cell_id + num_cols);
                }
                if (col != 0 && grid[row][col - 1] == 1)
                {
                    do_union(disjoint_set, cell_id, cell_id - 1);
                }
                if (col != num_cols - 1 && grid[row][col + 1] == 1)
                {
                    do_union(disjoint_set, cell_id, cell_id + 1);
                }
            }
        }

        vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits)
        {
            vector<int> solution;
            solution.resize(hits.size());
            int num_rows = grid.size();
            if (num_rows != 0)
            {
                int num_cols = grid[0].size();
                if (num_cols != 0)
                {
                    int size = num_rows * num_cols;
                    vector<int> disjoint_set;
                    disjoint_set.resize(size + 1);
                    for (int i = 0; i < size + 1; i++)
                    {
                        disjoint_set[i] = -1;
                    }
                    for (int i = 0; i < hits.size(); i++)
                    {
                        int hit_row = hits[i][0];
                        int hit_col = hits[i][1];
                        grid[hit_row][hit_col]--;
                    }

                    for (int row = 0; row < num_rows; row++)
                    {
                        for (int col = 0; col < num_cols; col++)
                        {
                            union_with_neighbors(grid, disjoint_set, row, col);
                        }
                    }
                    for (int i = 0; i < hits.size(); i++)
                    {
                        int before_undo_size = -disjoint_set[do_find(disjoint_set, size)];

                        int j = hits.size() - i - 1;
                        int row = hits[j][0];
                        int col = hits[j][1];
                        grid[row][col]++;

                        union_with_neighbors(grid, disjoint_set, row, col);

                        int after_undo_size = -disjoint_set[do_find(disjoint_set, size)];

                        solution[j] = after_undo_size - before_undo_size;
                        if (solution[j] > 0)
                        {
                            solution[j]--;
                        }
                    }
                }
            }
            return solution;
        }
    };
};

using namespace _LEET_BRICKS_FALLING_WHEN_HIT;

int LEET_BRICKS_FALLING_WHEN_HIT()
{
    int row1_array[] = { 1, 0, 0, 0 };
    int row2_array[] = { 1, 1, 0, 0 };
    int hit1_array[] = { 1, 1 };
    int hit2_array[] = { 1, 0 };
    vector<int> row1(row1_array, row1_array + _countof(row1_array));
    vector<int> row2(row2_array, row2_array + _countof(row2_array));
    vector<vector<int>> grid;
    grid.push_back(row1);
    grid.push_back(row2);
    vector<int> hit1(hit1_array, hit1_array + _countof(hit1_array));
    vector<int> hit2(hit2_array, hit2_array + _countof(hit2_array));
    vector<vector<int>> hits;
    hits.push_back(hit1);
    hits.push_back(hit2);
    Solution solution;

    vector<int> answers = solution.hitBricks(grid, hits);
    for (int answer : answers)
    {
        cout << answer << endl;
    }

    return 0;
}