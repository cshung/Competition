#include "stdafx.h"

// https://leetcode.com/problems/longest-common-prefix/

#include "LEET_LONGEST_COMMON_PREFIX.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_COMMON_PREFIX
{
    class Solution
    {
    public:
        string longestCommonPrefix(vector<string>& strs)
        {
            if (strs.size() == 0)
            {
                return "";
            }
            if (strs.size() == 1)
            {
                return strs[0];
            }

            ostringstream os;
            unsigned int minLength = strs[0].length();
            for (unsigned int i = 1; i < strs.size(); i++)
            {
                unsigned int currentLength = strs[i].length();
                if (currentLength < minLength)
                {
                    minLength = currentLength;
                }
            }
            for (unsigned int prefixIndex = 0; prefixIndex < minLength; prefixIndex++)
            {
                bool match = true;
                char first = strs[0][prefixIndex];
                for (unsigned int strsIndex = 1; match && strsIndex < strs.size(); strsIndex++)
                {
                    match = (strs[strsIndex][prefixIndex] == first);
                }
                if (match)
                {
                    os << first;
                }
                else
                {
                    break;
                }
            }
            return os.str();
        }
    };
};

using namespace _LEET_LONGEST_COMMON_PREFIX;

int LEET_LONGEST_COMMON_PREFIX()
{
    Solution s;
    string case1[] = { "a", "ab" };
    string case2[] = { "ab", "ab" };
    string case3[] = { "abc", "abd" };
    string case4[] = { "aca", "cba" };
    cout << ("a" == s.longestCommonPrefix(vector<string>(case1, case1 + _countof(case1)))) << endl;
    cout << ("ab" == s.longestCommonPrefix(vector<string>(case2, case2 + _countof(case2)))) << endl;
    cout << ("ab" == s.longestCommonPrefix(vector<string>(case3, case3 + _countof(case3)))) << endl;
    cout << ("" == s.longestCommonPrefix(vector<string>(case4, case4 + _countof(case4)))) << endl;
    return 0;
}