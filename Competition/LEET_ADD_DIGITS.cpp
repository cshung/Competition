#include "stdafx.h"

// https://leetcode.com/problems/add-digits/

#include "LEET_ADD_DIGITS.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_ADD_DIGITS
{
    class NaiveSolution {
    public:
        int addDigits(int num)
        {
            int sum = 0;
            while (num > 0)
            {
                sum += num % 10;
                num = num / 10;
            }
            if (sum > 9)
            {
                return addDigits(sum);
            }
            else
            {
                return sum;
            }
        }
    };
    class Solution {
    public:
        int addDigits(int num)
        {
            if (num == 0)
            {
                return 0;
            }
            else
            {
                return (num - 1) % 9 + 1;
            }
        }
    };
};

using namespace _LEET_ADD_DIGITS;

int LEET_ADD_DIGITS()
{
    NaiveSolution n;
    Solution s;
    for (int i = 0; i < 100000; i++)
    {
        if (s.addDigits(i) - n.addDigits(i) != 0)
        {
            cout << "Fail" << endl;
        }
    }
    return 0;
}