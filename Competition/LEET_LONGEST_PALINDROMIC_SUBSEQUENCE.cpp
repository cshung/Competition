#include "stdafx.h"

// https://leetcode.com/problems/longest-palindromic-subsequence/

#include "LEET_LONGEST_PALINDROMIC_SUBSEQUENCE.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_PALINDROMIC_SUBSEQUENCE
{
    class Solution
    {
    public:
        int longestPalindromeSubseq(string s)
        {
            if (s.length() == 0)
            {
                return 0;
            }

            vector<int> result[3];
            result[0].resize(s.length());
            result[1].resize(s.length());
            result[2].resize(s.length());
            for (size_t i = 0; i < s.length(); i++)
            {
                // The maximum palindromic subsequence of a subsequence starting at i with length 0 is 0
                result[0][i] = 0;
                // The maximum palindromic subsequence of a subsequence starting at i with length 1 is 1
                result[1][i] = 1;
            }

            int current_row = 2;
            int last_row = 1;
            int last_last_row = 0;
            for (int length = 2; length <= s.length(); length++)
            {
                for (int i = 0; i + length <= s.length(); i++)
                {
                    int candidate = result[last_row][i];
                    candidate = max(candidate, result[last_row][i + 1]);
                    if (s[i] == s[i + length - 1])
                    {
                        candidate = max(candidate, 2 + result[last_last_row][i + 1]);
                    }
                    result[current_row][i] = candidate;
                }
                current_row = (current_row + 1) % 3;
                last_row = (last_row + 1) % 3;
                last_last_row = (last_last_row + 1) % 3;
            }
            return result[last_row][0];
        }
    };
};

using namespace _LEET_LONGEST_PALINDROMIC_SUBSEQUENCE;

int LEET_LONGEST_PALINDROMIC_SUBSEQUENCE()
{
    Solution solution;
    cout << solution.longestPalindromeSubseq("") << endl;
    cout << solution.longestPalindromeSubseq("bbbab") << endl;
    cout << solution.longestPalindromeSubseq("cbbd") << endl;
    return 0;
}