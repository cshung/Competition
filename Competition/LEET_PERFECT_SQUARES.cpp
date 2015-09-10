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
    private:
        bool isSquare(int n)
        {
            for (int i = 1; i * i <= n; i++)
            {
                if (i * i == n)
                {
                    return true;
                }
            }

            return false;
        }
        bool isTwoSquare(int n)
        {
            for (int i = 1; i * i < n; i++)
            {
                int s = i * i;
                int r = n - s;
                if (isSquare(r))
                {
                    return true;
                }
            }

            return false;
        }
        bool isThreeSquare(int n)
        {
            for (int i = 1; i * i < n; i++)
            {
                int s = i * i;
                int r = n - s;
                if (isTwoSquare(r))
                {
                    return true;
                }
            }

            return false;
        }
    public:
        int numSquares(int n)
        {
            if (isSquare(n))
            {
                return 1;
            }
            else if (isTwoSquare(n))
            {
                return 2;
            }
            else if (isThreeSquare(n))
            {
                return 3;
            }
            else
            {
                return 4;
            }
            
        }
    };
};

using namespace _LEET_PERFECT_SQUARES;

int LEET_PERFECT_SQUARES()
{
    Solution s;
    for (int i = 1; i <= 10000; i++)
    {
        cout << i << " " << s.numSquares(i) << endl;
    }
    return 0;
}