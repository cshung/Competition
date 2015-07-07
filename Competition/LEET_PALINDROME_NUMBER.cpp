#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_PALINDROME_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PALINDROME_NUMBER
{
    class Solution
    {
    public:
        bool isPalindrome(int x)
        {
            if (x < 0)
            {
                return false;
            }
            int num_digits = 1;
            int y = x;
            while (y / 10 != 0)
            {
                y = y / 10;
                num_digits++;
            }
            int l_mask = 1;
            int u_mask = 1;
            for (int i = 1; i < num_digits; i++)
            {
                u_mask = u_mask * 10;
            }

            int l = 0;
            int u = num_digits - 1;

            while (u > l)
            {
                int u_digit = (x / u_mask) % 10;
                int l_digit = (x / l_mask) % 10;
                if (u_digit != l_digit)
                {
                    return false;
                }
                u--;
                l++;
                u_mask = u_mask / 10;
                l_mask = l_mask * 10;
            }

            return true;
        }
    };
};

using namespace _LEET_PALINDROME_NUMBER;

int LEET_PALINDROME_NUMBER()
{
    Solution solution;
    cout << solution.isPalindrome(0) << endl;
    cout << solution.isPalindrome(1) << endl;
    cout << solution.isPalindrome(12) << endl;
    cout << solution.isPalindrome(121) << endl;
    return 0;
}