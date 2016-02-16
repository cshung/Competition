#include "stdafx.h"

// https://leetcode.com/problems/fraction-to-recurring-decimal/

#include "LEET_FRACTION_TO_RECURRING_DECIMAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FRACTION_TO_RECURRING_DECIMAL
{
    typedef long long int64;

    class Solution
    {
    public:
        void fractionPart(ostringstream& ss, int64 numerator, int64 denominator)
        {
            vector<int64> quotient_digits;
            map<int64, size_t> remainder_index;
            int found = -1;
            while (true)
            {
                if (numerator == 0)
                {
                    break;
                }
                numerator *= 10;
                map<int64, size_t>::iterator probe = remainder_index.find(numerator);
                if (probe != remainder_index.end())
                {
                    found = probe->second;
                    break;
                }
                remainder_index.insert(pair<int64, size_t>(numerator, quotient_digits.size()));
                int64 quotient = numerator / denominator;
                int64 remainder = numerator % denominator;
                quotient_digits.push_back(quotient);
                numerator = remainder;
            }
            ss << ".";
            for (size_t i = 0; i < quotient_digits.size(); i++)
            {
                if (i == found)
                {
                    ss << "(";
                }
                ss << quotient_digits[i];
            }
            if (found != -1)
            {
                ss << ")";
            }
        }

        string fractionToDecimal(int numerator, int denominator)
        {
            int64 n = numerator; 
            int64 d = denominator;

            bool positive = true;
            if (n < 0)
            {
                positive = !positive;
                n *= -1;
            }
            if (d < 0)
            {
                positive = !positive;
                d *= -1;
            }

            ostringstream ss;
            if (!positive && n != 0)
            {
                ss << "-";
            }
            ss << n / d;
            int64 remainder = n % d;
            if (remainder != 0)
            {
                fractionPart(ss, remainder, d);
            }
            return ss.str();
        }
    };
};

using namespace _LEET_FRACTION_TO_RECURRING_DECIMAL;

int LEET_FRACTION_TO_RECURRING_DECIMAL()
{
    Solution solution;
    cout << solution.fractionToDecimal(1, 2) << endl;
    cout << solution.fractionToDecimal(2, 1) << endl;
    cout << solution.fractionToDecimal(2, 3) << endl;
    cout << solution.fractionToDecimal(1, 7) << endl;
    cout << solution.fractionToDecimal(1, 70) << endl;
    cout << solution.fractionToDecimal(1, 99) << endl;
    cout << solution.fractionToDecimal(-50, 8) << endl;
    cout << solution.fractionToDecimal((1 << 31), 1) << endl;
    cout << solution.fractionToDecimal(1, (1 << 31)) << endl;
    return 0;
}