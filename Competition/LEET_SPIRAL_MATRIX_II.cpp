#include "stdafx.h"

// https://leetcode.com/problems/spiral-matrix-ii/

#include "LEET_SPIRAL_MATRIX_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SPIRAL_MATRIX_II
{
    class Solution
    {
    public:
        vector<vector<int>> generateMatrix(int n)
        {
            vector<vector<int>> result;
            result.resize(n);
            for (int i = 0; i < n; i++)
            {
                result[i].resize(n);
            }
            int current = 1;
            int top = -1;
            int left = -1;
            int bottom = n;
            int right = n;
            int direction = 0; // 0 left, 1 down, 2 right, 3 up
            int row = 0;
            int col = -1;
            while (true)
            {
                bool moved = false;
                switch (direction)
                {
                case 0:
                    while (col + 1 < right)
                    {
                        col++;
                        moved = true;
                        result[row][col] = current++;
                    }
                    top++;
                    direction = 1;
                    break;
                case 1:
                    while (row + 1 < bottom)
                    {
                        row++;
                        moved = true;
                        result[row][col] = current++;
                    }
                    right--;
                    direction = 2;
                    break;
                case 2:
                    while (col - 1 > left)
                    {
                        col--;
                        moved = true;
                        result[row][col] = current++;
                    }
                    bottom--;
                    direction = 3;
                    break;
                case 3:
                    while (row - 1 > top)
                    {
                        row--;
                        moved = true;
                        result[row][col] = current++;
                    }
                    left++;
                    direction = 0;
                    break;
                }

                if (!moved)
                {
                    break;
                }
            }

            return result;
        }
    };
};

using namespace _LEET_SPIRAL_MATRIX_II;

int LEET_SPIRAL_MATRIX_II()
{
    Solution s;
    vector<vector<int>> result = s.generateMatrix(4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << result[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}