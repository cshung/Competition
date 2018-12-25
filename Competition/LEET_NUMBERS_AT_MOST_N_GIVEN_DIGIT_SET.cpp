#include "stdafx.h"

// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

#include "LEET_NUMBERS_AT_MOST_N_GIVEN_DIGIT_SET.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBERS_AT_MOST_N_GIVEN_DIGIT_SET
{
    class Solution
    {
    public:
        int atMostNGivenDigitSet(vector<string>& D, int N)
        {
            vector<int> digits;
            while (N > 0)
            {
                digits.push_back(N % 10);
                N /= 10;
            }
            vector<int> givens;
            for (string s : D)
            {
                givens.push_back(s[0] - '0');
            }
            return atMostNGivenDigitSet(givens, digits, digits.size(), false);
        }

        int power(int b, int p)
        {
            int result = 1;
            for (int i = 0; i < p; i++)
            {
                result *= b;
            }
            return result;
        }

        int atMostNGivenDigitSet(vector<int>& givens, vector<int>& digits, int num_digits, bool non_zero_used)
        {
            int msb = digits[num_digits - 1];
            bool match_msb = false;
            int num_less_than_msb = 0;
            for (int g : givens)
            {
                if (g == msb)
                {
                    match_msb = true;
                }
                else if (g < msb)
                {
                    num_less_than_msb++;
                }
            }

            if (num_digits == 1)
            {
                return num_less_than_msb + (match_msb ? 1 : 0);
            }

            int result = num_less_than_msb * power(givens.size(), num_digits - 1);
            
            if (!non_zero_used)
            {
                if (givens.size() == 1)
                {
                    result += num_digits - 1;
                }
                else
                {
                    result += (power(givens.size(), num_digits) - givens.size()) / (givens.size() - 1);
                }
            }
            
            if (match_msb)
            {
                result += atMostNGivenDigitSet(givens, digits, num_digits - 1, true);
            }
            return result;
        }
    };
};

using namespace _LEET_NUMBERS_AT_MOST_N_GIVEN_DIGIT_SET;

int LEET_NUMBERS_AT_MOST_N_GIVEN_DIGIT_SET()
{
    Solution solution;
    string test1_array[] = { "1", "3", "5", "7" };
    vector<string> test1(test1_array, test1_array + _countof(test1_array));
    cout << solution.atMostNGivenDigitSet(test1, 100) << endl;

    string test2_array[] = { "1", "4", "9" };
    vector<string> test2(test2_array, test2_array + _countof(test2_array));
    cout << solution.atMostNGivenDigitSet(test2, 1000000000) << endl;

    string test3_array[] = { "9" };
    vector<string> test3(test3_array, test3_array + _countof(test3_array));
    cout << solution.atMostNGivenDigitSet(test3, 55) << endl;

    return 0;
}