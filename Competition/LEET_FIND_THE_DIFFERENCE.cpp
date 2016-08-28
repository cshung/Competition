#include "stdafx.h"

// https://leetcode.com/contest/2/problems/find-the-difference/

#include "LEET_FIND_THE_DIFFERENCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_THE_DIFFERENCE
{
    class Solution
    {
    public:
        char findTheDifference(string s, string t)
        {
            int* counts = new int[26];
            for (int i = 0; i < 26; i++)
            {
                counts[i] = 0;
            }
            for (size_t i = 0; i < s.length(); i++)
            {
                counts[s[i] - 'a']--;
            }
            for (size_t i = 0; i < t.length(); i++)
            {
                counts[t[i] - 'a']++;
            }
            for (int i = 0; i < 26; i++)
            {
                if (counts[i] == 1)
                {
                    return i + 'a';
                }
            }
            return 0;
        }
    };
};

using namespace _LEET_FIND_THE_DIFFERENCE;

int LEET_FIND_THE_DIFFERENCE()
{
    Solution solution;
    cout << solution.findTheDifference("abcd", "aecbd") << endl;
    return 0;
}