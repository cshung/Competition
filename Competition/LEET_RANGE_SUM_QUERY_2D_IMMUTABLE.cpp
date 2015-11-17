#include "stdafx.h"

// https://leetcode.com/problems/range-sum-query-2d-immutable/

#include "LEET_RANGE_SUM_QUERY_2D_IMMUTABLE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANGE_SUM_QUERY_2D_IMMUTABLE
{
    class NumMatrix
    {
    private:
        vector<vector<int>> runningSums;
    public:
        NumMatrix(vector<vector<int>> &matrix)
        {            
            int height = matrix.size();
            if (height == 0)
            {
                return;
            }

            int width = matrix[0].size();
            if (width == 0)
            {
                return;
            }

            // runningSum[i][j] = sum(r = 0 to i - 1) sum(c = 0 to j - 1) matrix[r][c]
            runningSums.resize(height + 1);
            for (int r = 0; r <= height; r++)
            {
                runningSums[r].resize(width + 1);
            }

            for (int i = 0; i <= height; i++)
            {
                for (int j = 0; j <= width; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        runningSums[i][j] = 0;
                    }
                    else
                    {
                        // Inclusive exclusive principle applies here
                        runningSums[i][j] = runningSums[i - 1][j] + runningSums[i][j - 1] - runningSums[i - 1][j - 1] + matrix[i - 1][j - 1];
                    }
                }
            }
        }

        int sumRegion(int row1, int col1, int row2, int col2)
        {
            // Inclusive exclusive principle applies here as well
            return runningSums[row2 + 1][col2 + 1] - runningSums[row1][col2 + 1] - runningSums[row2 + 1][col1] + runningSums[row1][col1];
        }
    };
};

using namespace _LEET_RANGE_SUM_QUERY_2D_IMMUTABLE;

int LEET_RANGE_SUM_QUERY_2D_IMMUTABLE()
{
    int row1[] = { 3, 0, 1, 4, 2 };
    int row2[] = { 5, 6, 3, 2, 1 };
    int row3[] = { 1, 2, 0, 1, 5 };
    int row4[] = { 4, 1, 0, 1, 7 };
    int row5[] = { 1, 0, 3, 0, 5 };
    vector<vector<int>> nums;
    nums.push_back(vector<int>(row1, row1 + _countof(row1)));
    nums.push_back(vector<int>(row2, row2 + _countof(row2)));
    nums.push_back(vector<int>(row3, row3 + _countof(row3)));
    nums.push_back(vector<int>(row4, row4 + _countof(row4)));
    nums.push_back(vector<int>(row5, row5 + _countof(row5)));
    NumMatrix n(nums);
    cout << (n.sumRegion(2, 1, 4, 3) == 8) << endl;
    cout << (n.sumRegion(1, 1, 2, 2) == 11) << endl;
    cout << (n.sumRegion(1, 2, 2, 4) == 12) << endl;
    return 0;
}