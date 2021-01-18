#include "stdafx.h"

// https://leetcode.com/problems/beautiful-arrangement/

#include "LEET_BEAUTIFUL_ARRANGEMENT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BEAUTIFUL_ARRANGEMENT
{
    class Solution
    {
    public:
        int countArrangement(int n)
        {
            vector<vector<int>> matrix(n, vector<int>(n, 0));

            for (int i = 0; i < n; i++)
            {
                for (int j = i; j < n; j++)
                {
                    if ((j + 1) % (i + 1) == 0)
                    {
                        matrix[i][j] = 1;
                        matrix[j][i] = 1;
                    }
                }
            }

            vector<int> gray(n, 1);
            vector<int> focus_pointers(n + 1);
            bool code = true;
            for (int i = 0; i <= n; i++)
            {
                focus_pointers[i] = i;
            }
            int64_t answer = 0;
            vector<int64_t> row_sum(n, 0);
            for (int row = 0; row < n; row++)
            {
                for (int col = 0; col < n; col++)
                {
                    row_sum[row] += matrix[row][col];
                }
            }
            int parity = 1;
            while (true)
            {
                int64_t product = 1;
                for (int row = 0; row < n; row++)
                {
                    product = product * row_sum[row];
                }
                answer += parity * product;
                parity = -parity;
                int j = 0;
                j = focus_pointers[0];
                focus_pointers[0] = 0;
                if (j == n)
                {
                    break;
                }
                focus_pointers[j] = focus_pointers[j + 1];
                focus_pointers[j + 1] = j + 1;
                gray[j] = -gray[j];
                for (int row = 0; row < n; row++)
                {
                    row_sum[row] += gray[j] * matrix[row][j];
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_BEAUTIFUL_ARRANGEMENT;

int LEET_BEAUTIFUL_ARRANGEMENT()
{
    Solution solution;
    for (int i = 1; i <= 15; i++)
    {
        cout << solution.countArrangement(i) << endl;
    }
    return 0;
}