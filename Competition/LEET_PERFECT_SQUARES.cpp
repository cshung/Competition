#include "stdafx.h"

// https://leetcode.com/problems/perfect-squares/

#include "LEET_PERFECT_SQUARES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_PERFECT_SQUARES
{
    class Solution
    {
    public:
        int numSquares(int n)
        {
            int* values = new int[n + 1]; 
            for (int i = 1; i <= n; i++)
            {
                values[i] = 0;
            }

            for (int i = 1; i * i <= n; i++)
            {
                values[i * i] = 1;
            }

            for (int i = 1; i <= n; i++)
            {
                if (values[i] == 0)
                {
                    int min = -1;
                    for (int j = 1; j < i; j++)
                    {
                        int candidate = values[j] + values[i - j];
                        if (min == -1 || candidate < min)
                        {
                            min = candidate;
                        }
                    }
                    values[i] = min;
                }
            }

            int result = values[n];
            delete[] values;

            return result;
        }
    };
};

using namespace _LEET_PERFECT_SQUARES;

int LEET_PERFECT_SQUARES()
{
    Solution s;
    cout << s.numSquares(5254) << endl;
    return 0;
}