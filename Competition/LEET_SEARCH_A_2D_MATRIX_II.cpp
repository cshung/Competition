#include "stdafx.h"

// https://leetcode.com/problems/search-a-2d-matrix-ii/

#include "LEET_SEARCH_A_2D_MATRIX_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SEARCH_A_2D_MATRIX_II
{
    class Solution
    {
    public:
        bool searchMatrix(vector<vector<int>>& matrix, int target)
        {
            unsigned int matrix_height = matrix.size();

            if (matrix_height == 0)
            {
                // There is no element in the matrix
                return false;
            }

            unsigned int matrix_width = matrix[0].size();

            int x1 = 0;
            int y1 = 0;
            int x2 = matrix_width - 1;
            int y2 = matrix_height - 1;

            while (true)
            {
                if (x2 < x1)
                {
                    return false;
                }
                if (y2 < y1)
                {
                    return false;
                }
                if (target < matrix[y1][x1])
                {
                    return false;
                }
                else if (target > matrix[y2][x2])
                {
                    return false;
                }
                else
                {
                    int corner = matrix[y1][x2];
                    if (target == corner)
                    {
                        return true;
                    }
                    else if (target < corner)
                    {
                        x2--;
                    }
                    else
                    {
                        y1++;
                    }
                }
            }
        }
    };
};

using namespace _LEET_SEARCH_A_2D_MATRIX_II;

int LEET_SEARCH_A_2D_MATRIX_II()
{
    Solution solution;
    vector<vector<int>> matrix;
    int row1[] = { 1, 4, 7, 11, 15 };
    int row2[] = { 2, 5, 8, 12, 19 };
    int row3[] = { 3, 6, 9, 16, 22 };
    int row4[] = { 10, 13, 14, 17, 24 };
    int row5[] = { 18, 21, 23, 26, 30 };
    matrix.push_back(vector<int>(row1, row1 + _countof(row1)));
    matrix.push_back(vector<int>(row2, row2 + _countof(row2)));
    matrix.push_back(vector<int>(row3, row3 + _countof(row3)));
    matrix.push_back(vector<int>(row4, row4 + _countof(row4)));
    matrix.push_back(vector<int>(row5, row5 + _countof(row5)));
    cout << (solution.searchMatrix(matrix, 5) == true) << endl;
    cout << (solution.searchMatrix(matrix, 20) == false) << endl;
    return 0;
}