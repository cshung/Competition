#include "stdafx.h"

// https://leetcode.com/problems/permutation-sequence/

#include "LEET_PERMUTATION_SEQUENCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PERMUTATION_SEQUENCE
{
    class Solution
    {
    public:
        string getPermutation(int n, int k)
        {
            vector<int> digits;
            vector<int> factorial;
            for (int i = 0; i < n; i++)
            {
                digits.push_back(i + 1);
                if (i == 0)
                {
                    factorial.push_back(1);
                }
                else
                {
                    factorial.push_back(factorial[i - 1] * (i + 1));
                }
            }
            factorial.push_back(factorial[n - 1] * n);
            ostringstream oss;
            k--;
            for (int i = 0; i < n; i++)
            {
                int p = n - i;
                if (p > 1)
                {
                    int group_size = factorial[p - 2];
                    int group = k / group_size;
                    oss << digits[group];
                    digits.erase(digits.begin() + group);
                    k = k % group_size;
                }
                else
                {
                    oss << digits[0];
                }

            }
            return oss.str();
        }
    };
};

using namespace _LEET_PERMUTATION_SEQUENCE;

int LEET_PERMUTATION_SEQUENCE()
{
    Solution solution;
    cout << solution.getPermutation(3, 3) << endl;
    cout << solution.getPermutation(4, 9) << endl;
    return 0;
}