#include "stdafx.h"

// https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

#include "LEET_LONGEST_SUBSTRING_WITH_AT_MOST_TWO_DISTINCT_CHARACTERS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_SUBSTRING_WITH_AT_MOST_TWO_DISTINCT_CHARACTERS
{
    class Solution {
    public:
        int lengthOfLongestSubstringTwoDistinct(string s)
        {
            int n = s.size();
            if (n == 0)
            {
                return 0;
            }
            int state = 0;
            char a = s[0];
            char b = '\0';
            int ai = 0;
            int li = -1;
            int answer = 0;
            for (int i = 1; i <= n; i++)
            {
                char c = (i == n) ? '\0' : s[i];
                if (c == a)
                {
                    if (state == 1)
                    {
                        li = i;
                        state = 0;
                    }
                }
                else
                {
                    if (b == '\0')
                    {
                        if (c == '\0')
                        {
                            int length = i - ai;
                            if (length > answer)
                            {
                                answer = length;
                            }
                        }
                        b = c;
                        state = 1;
                        li = i;
                    }
                    else if (c == b)
                    {
                        if (state == 0)
                        {
                            li = i;
                            state = 1;
                        }
                    }
                    else
                    {
                        int length = i - ai;
                        if (length > answer)
                        {
                            answer = length;
                        }
                        if (state == 1)
                        {
                            a = b;
                        }
                        b = c;
                        ai = li;
                        li = i;
                        state = 1;
                    }
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_LONGEST_SUBSTRING_WITH_AT_MOST_TWO_DISTINCT_CHARACTERS;

int LEET_LONGEST_SUBSTRING_WITH_AT_MOST_TWO_DISTINCT_CHARACTERS()
{
    Solution solution;
    cout << solution.lengthOfLongestSubstringTwoDistinct("eceba") << endl;
    cout << solution.lengthOfLongestSubstringTwoDistinct("ccaabbb") << endl;
    return 0;
}