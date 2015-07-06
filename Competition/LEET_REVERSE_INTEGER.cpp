#include "stdafx.h"

// https://leetcode.com/problems/reverse-integer/

#include "LEET_REVERSE_INTEGER.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_REVERSE_INTEGER
{
    class Solution
    {
    public:
        int reverse(int x)
        {
            int num_digits = 1;
            int y = x;
            while (y / 10 != 0)
            {
                num_digits++;
                y = y / 10;
            }
            try
            {
                return reverse_helper(x, num_digits);
            }
            catch (int& x)
            {
                return 0;
            }
        }
    private:
        int shift(int digit, int num_digits)
        {
            if (num_digits == 1)
            {
                return digit;
            }
            else
            {
                int recursive_result = shift(digit, num_digits - 1); 
                int product = recursive_result * 10;
                if (product % 10 != 0)
                {
                    throw 0;
                }
                else
                {
                    return product;
                }
            }
        }

        int add(int x, int y)
        {
            int sum = x + y;
            if (x > 0 && y > 0 && sum < 0)
            {
                throw 0;
            }
            else if (x < 0 && y < 0 && sum > 0)
            {
                throw 0;
            }
            else
            {
                return sum;
            }
        }

        int reverse_helper(int num, int num_digits)
        {
            if (num_digits == 1)
            {
                return num;
            }
            else
            {
                return add(reverse_helper(num / 10, num_digits - 1), shift(num % 10, num_digits));
            }
        }
    };
};

using namespace _LEET_REVERSE_INTEGER;

int LEET_REVERSE_INTEGER()
{
    cout << (1 << 31) << endl;
    Solution s;
    cout << s.reverse(123) << endl;
    cout << s.reverse(-123) << endl;
    cout << s.reverse(0) << endl;
    cout << s.reverse(100) << endl;
    cout << s.reverse(101) << endl;
    cout << s.reverse(1010) << endl;
    cout << s.reverse(1534236469) << endl;
    cout << s.reverse(1 << 31) << endl;
    cout << s.reverse(~(1 << 31)) << endl;
    return 0;
}
