#include "stdafx.h"

// https://leetcode.com/problems/set-matrix-zeroes/

#include "LEET_SET_MATRIX_ZEROES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SET_MATRIX_ZEROES
{
    class Solution
    {
    public:
        void setZeroes(vector<vector<int>>& matrix)
        {
            int height = matrix.size();
            if (height > 0)
            {
                int width = matrix[0].size();
                if (width > 0)
                {
                    bool firstRowZero = false;
                    bool firstColumnZero = false;
                    for (int col = 0; col < width; col++)
                    {
                        if (matrix[0][col] == 0)
                        {
                            firstRowZero = true;
                            break;
                        }
                    }
                    for (int row = 0; row < height; row++)
                    {
                        if (matrix[row][0] == 0)
                        {
                            firstColumnZero = true;
                            break;
                        }
                    }
                    for (int row = 1; row < height; row++)
                    {
                        for (int col = 1; col < width; col++)
                        {
                            if (matrix[row][col] == 0)
                            {
                                matrix[row][0] = 0;
                                matrix[0][col] = 0;
                            }
                        }
                    }
                    for (int row = 1; row < height; row++)
                    {
                        for (int col = 1; col < width; col++)
                        {
                            if (matrix[row][0] == 0 || matrix[0][col] == 0)
                            {
                                matrix[row][col] = 0;
                            }
                        }
                    }
                    if (firstRowZero)
                    {
                        for (int col = 0; col < width; col++)
                        {
                            matrix[0][col] = 0;
                        }
                    }
                    if (firstColumnZero)
                    {
                        for (int row = 0; row < height; row++)
                        {
                            matrix[row][0] = 0;
                        }
                    }
                }
            }
        }
    };
};

using namespace _LEET_SET_MATRIX_ZEROES;

int LEET_SET_MATRIX_ZEROES()
{
    Solution solution;
    vector<vector<int>> matrix;
    matrix.resize(3);
    matrix[0].push_back(1);
    matrix[0].push_back(1);
    matrix[0].push_back(1);
    matrix[1].push_back(1);
    matrix[1].push_back(0);
    matrix[1].push_back(1);
    matrix[2].push_back(1);
    matrix[2].push_back(1);
    matrix[2].push_back(1);
    solution.setZeroes(matrix);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    return 0;
}