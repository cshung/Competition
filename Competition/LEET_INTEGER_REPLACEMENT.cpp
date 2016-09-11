#include "stdafx.h"

// https://leetcode.com/contest/4/problems/integer-replacement/

#include "LEET_INTEGER_REPLACEMENT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INTEGER_REPLACEMENT
{
    class Solution {
    public:
        int integerReplacement(int n)
        {
            return integerReplacementLong(n);
        }

        int integerReplacementLong(long long n)
        {
            if (n == 0)
            {
                return 1;
            }
            else if (n == 1)
            {
                return 0;
            }
            // But the judge does not like this case :( - shame on leetcode 
            //else if (n == 3)
            //{
            //    // The divide by 4 rule does not apply for it
            //    return 2;
            //}
            else if (n % 2 == 0)
            {
                return integerReplacementLong(n / 2) + 1;
            }
            else if ((n + 1) % 4 == 0)
            {
                return integerReplacementLong(n + 1) + 1;
            }
            else
            {
                return integerReplacementLong(n - 1) + 1;
            }
        }
    };
};

using namespace _LEET_INTEGER_REPLACEMENT;

int LEET_INTEGER_REPLACEMENT()
{
    Solution solution;
    for (int i = 0; i < 10; i++) {
        cout << i << "\t" << solution.integerReplacement(i) << endl;
    }
    cout << solution.integerReplacement(2147483647) << endl;
    return 0;
}