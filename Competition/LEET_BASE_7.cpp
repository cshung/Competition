#include "stdafx.h"

// https://leetcode.com/problems/base-7

#include "LEET_BASE_7.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BASE_7
{
    class Solution {
    public:
        string convertToBase7(int num)
        {
            if (num == 0)
            {
                return "0";
            }

            bool negative = num < 0;
            num = num < 0 ? -num : num;
            char result[100];
            int last = 100;
            result[--last] = '\0';
            while (num > 0)
            {
                result[--last] = '0' + (num % 7);
                num = num / 7;
            }
            if (negative)
            {
                result[--last] = '-';
            }
            return result + last;
        }
    };
};

using namespace _LEET_BASE_7;

int LEET_BASE_7()
{
    Solution solution;
    for (int i = -50; i <= 50; i++)
    {
        cout << solution.convertToBase7(i) << endl;
    }
    return 0;
}