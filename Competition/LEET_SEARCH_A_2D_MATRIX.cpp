#include "stdafx.h"

// https://leetcode.com/problems/search-a-2d-matrix/

#include "LEET_SEARCH_A_2D_MATRIX.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SEARCH_A_2D_MATRIX
{
    class Solution
    {
    public:
        bool searchMatrix(vector<vector<int>>& matrix, int target)
        {
            int height = matrix.size();
            if (height == 0)
            {
                return false;
            }
            int width = matrix[0].size();
            if (width == 0)
            {
                return false;
            }
            int size = height * width;

            // [,)
            int begin = 0;
            int end = size;
            while (end > begin)
            {
                // Forget about overflow, there should not be so many elements
                int mid = (begin + end) / 2;
                int probe_row = mid / width;
                int probe_col = mid % width;
                int probe_val = matrix[probe_row][probe_col];
                if (probe_val == target)
                {
                    return true;
                }
                else if (target < probe_val)
                {
                    end = mid;
                }
                else
                {
                    begin = mid + 1;
                }
            }

            return false;
        }
    };
};

using namespace _LEET_SEARCH_A_2D_MATRIX;

int LEET_SEARCH_A_2D_MATRIX()
{
    Solution s;
    vector<vector<int>> matrix;
    int row1[] = { 1, 3, 5, 7 };
    int row2[] = { 10, 11, 16, 20 };
    int row3[] = { 23, 30, 34, 50 };
    matrix.push_back(vector<int>(row1, row1 + _countof(row1)));
    matrix.push_back(vector<int>(row2, row2 + _countof(row2)));
    matrix.push_back(vector<int>(row3, row3 + _countof(row3)));
    cout << (s.searchMatrix(matrix, 2) == 1) << endl;
    return 0;
}