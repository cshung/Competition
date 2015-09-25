#include "stdafx.h"

// http://leetcode.com/problems/spiral-matrix

#include "LEET_SPIRAL_MATRIX.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SPIRAL_MATRIX
{
    class Solution
    {
    public:
        vector<int> spiralOrder(vector<vector<int>>& matrix)
        {
            vector<int> result;
            int height = matrix.size();
            if (height > 0)
            {
                int width = matrix[0].size();
                if (width > 0)
                {
                    int top = -1;
                    int left = -1;
                    int bottom = height;
                    int right = width;
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
                                result.push_back(matrix[row][col]);
                            }
                            top++;
                            direction = 1;
                            break;
                        case 1:
                            while (row + 1 < bottom)
                            {
                                row++;
                                moved = true;
                                result.push_back(matrix[row][col]);
                            }
                            right--;
                            direction = 2;
                            break;
                        case 2:
                            while (col - 1 > left)
                            {
                                col--;
                                moved = true;
                                result.push_back(matrix[row][col]);
                            }
                            bottom--;
                            direction = 3;
                            break;
                        case 3:
                            while (row - 1 > top)
                            {
                                row--;
                                moved = true;
                                result.push_back(matrix[row][col]);
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
                }
            }
            return result;
        }
    };
};

using namespace _LEET_SPIRAL_MATRIX;

int LEET_SPIRAL_MATRIX()
{
    Solution s;
    vector<vector<int>> matrix;
    matrix.resize(3);
    matrix[0].push_back(1);
    matrix[0].push_back(2);
    matrix[0].push_back(3);
    matrix[1].push_back(4);
    matrix[1].push_back(5);
    matrix[1].push_back(6);
    matrix[2].push_back(7);
    matrix[2].push_back(8);
    matrix[2].push_back(9);
    vector<int> ordered = s.spiralOrder(matrix);
    for (unsigned int i = 0; i < ordered.size(); i++)
    {
        cout << ordered[i];
    }
    cout << endl;
    return 0;
}