#include "stdafx.h"

// https://leetcode.com/problems/ugly-number/

#include "LEET_UGLY_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_UGLY_NUMBER
{
    class Solution
    {
    public:
        bool isUgly(int num)
        {
            if (num <= 0)
            {
                return false;
            }

            while (num > 1)
            {
                if (num % 2 == 0)
                {
                    num = num / 2;
                }
                else if (num % 3 == 0)
                {
                    num = num / 3;
                }
                else if (num % 5 == 0)
                {
                    num = num / 5;
                }
                else
                {
                    return false;
                }
            }

            return true;
        }
    };
};

using namespace _LEET_UGLY_NUMBER;

int LEET_UGLY_NUMBER()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        cout << solution.isUgly(i) << endl;
    }
    return 0;
}