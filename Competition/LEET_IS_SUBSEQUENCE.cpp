#include "stdafx.h"

// https://leetcode.com/problems/is-subsequence/

#include "LEET_IS_SUBSEQUENCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IS_SUBSEQUENCE
{
    class Solution
    {
    public:
        bool isSubsequence(string s, string t)
        {
            if (s == "")
            {
                return true;
            }
            int i = 0;
            for (int j = 0; j < t.length(); j++)
            {
                if (t[j] == s[i])
                {
                    i++;
                    if (i == s.length())
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    };
};

using namespace _LEET_IS_SUBSEQUENCE;

int LEET_IS_SUBSEQUENCE()
{
    Solution solution;
    cout << solution.isSubsequence("abc", "ahbgdc") << endl;
    return 0;
}