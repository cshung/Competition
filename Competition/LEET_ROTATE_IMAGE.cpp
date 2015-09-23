#include "stdafx.h"

// https://leetcode.com/problems/rotate-image/

#include "LEET_ROTATE_IMAGE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_ROTATE_IMAGE
{
    class Solution
    {
    public:
        void rotate(vector<vector<int>>& matrix)
        {
            int size = matrix.size();
            int left = 0;
            int right = size - 1;
            int top = 0;
            int bottom = size - 1;

            for (int shell = 0; shell < size / 2; shell++)
            {
                int a = top;
                int b = left;
                int c = bottom;
                int d = left;
                int e = bottom;
                int f = right;
                int g = top;
                int h = right;
                while (b < right)
                {
                    // Perform one rotate
                    int temp = matrix[a][b];
                    matrix[a][b] = matrix[c][d];
                    matrix[c][d] = matrix[e][f];
                    matrix[e][f] = matrix[g][h];
                    matrix[g][h] = temp;

                    // move the pointers
                    b++; // >
                    c--; // ^
                    f--; // <
                    g++; // v
                }
                left++;
                right--;
                top++;
                bottom--;
            }
        }
    };
};

using namespace _LEET_ROTATE_IMAGE;

int LEET_ROTATE_IMAGE()
{
    Solution s;
    vector<vector<int>> matrix;
    int size = 9;
    matrix.resize(size);
    for (int i = 0; i < size; i++)
    {
        matrix[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            // matrix[i][j] = i * 10 +  j;
            matrix[i][j] = i == j;
        }
    }
    s.rotate(matrix);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}