#include "stdafx.h"

// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

#include "LEET_LONGEST_INCREASING_PATH_IN_A_MATRIX.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_INCREASING_PATH_IN_A_MATRIX
{
    class Solution
    {
    public:
        int dfs(int row, int col, int height, int width, vector<vector<int>>& matrix, vector<int>& depth)
        {
            int num = row * width + col;
            if (depth[num] > 0)
            {
                return depth[num];
            }
            int max = 0;
            if (row > 0 && matrix[row][col] < matrix[row - 1][col])
            {
                int d = dfs(row - 1, col, height, width, matrix, depth);
                if (d > max)
                {
                    max = d;
                }
            }
            if (row < height - 1 && matrix[row][col] < matrix[row + 1][col])
            {
                int d = dfs(row + 1, col, height, width, matrix, depth);
                if (d > max)
                {
                    max = d;
                }
            }
            if (col > 0 && matrix[row][col] < matrix[row][col - 1])
            {
                int d = dfs(row, col - 1, height, width, matrix, depth);
                if (d > max)
                {
                    max = d;
                }
            }
            if (col < width - 1 && matrix[row][col] < matrix[row][col + 1])
            {
                int d = dfs(row, col + 1, height, width, matrix, depth);
                if (d > max)
                {
                    max = d;
                }
            }
            depth[num] = 1 + max;
            return depth[num];
        }
        int longestIncreasingPath(vector<vector<int>>& matrix)
        {
            int height = matrix.size();
            if (height == 0)
            {
                return 0;
            }
            int width = matrix[0].size();
            if (width == 0)
            {
                return 0;
            }
            int area = width * height;
            vector<int> depth;
            depth.resize(area);
            for (int i = 0; i < area; i++)
            {
                depth[i] = 0;
            }
            int max_depth = 0;
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    int d = dfs(row, col, height, width, matrix, depth);
                    if (d > max_depth)
                    {
                        max_depth = d;
                    }
                }
            }
            return max_depth;
        }
    };
};

using namespace _LEET_LONGEST_INCREASING_PATH_IN_A_MATRIX;

int LEET_LONGEST_INCREASING_PATH_IN_A_MATRIX()
{
    Solution solution;
    vector<vector<int>> test;
    test.resize(3);
    test[0].push_back(3);
    test[0].push_back(4);
    test[0].push_back(5);
    test[1].push_back(3);
    test[1].push_back(2);
    test[1].push_back(6);
    test[2].push_back(2);
    test[2].push_back(2);
    test[2].push_back(1);
    cout << solution.longestIncreasingPath(test) << endl;
    return 0;
}