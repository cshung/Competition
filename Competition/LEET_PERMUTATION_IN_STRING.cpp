#include "stdafx.h"

// https://leetcode.com/problems/permutation-in-string

#include "LEET_PERMUTATION_IN_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PERMUTATION_IN_STRING
{
    class Solution {
    public:
        bool checkInclusion(string s1, string s2)
        {
            if (s1.length() > s2.length())
            {
                return false;
            }
            char fixed_histogram[26];
            char slide_histogram[26];
            for (int i = 0; i < 26; i++)
            {
                fixed_histogram[i] = slide_histogram[i] = 0;
            }
            for (size_t i = 0; i < s1.length(); i++)
            {
                fixed_histogram[s1[i] - 'a']++;
                slide_histogram[s2[i] - 'a']++;
            }
            bool match = true;
            for (int i = 0; match && i < 26; i++)
            {
                match = fixed_histogram[i] == slide_histogram[i];
            }
            if (match)
            {
                return true;
            }
            for (size_t i = s1.length(); i < s2.length(); i++)
            {
                slide_histogram[s2[i - s1.length()] - 'a']--;
                slide_histogram[s2[i] - 'a']++;
                match = true;
                for (int i = 0; match && i < 26; i++)
                {
                    match = fixed_histogram[i] == slide_histogram[i];
                }
                if (match)
                {
                    return true;
                }
            }
            return false;
        }
    };
};

using namespace _LEET_PERMUTATION_IN_STRING;

int LEET_PERMUTATION_IN_STRING()
{
    Solution solution;
    cout << (solution.checkInclusion("ab", "eidbaooo") ? "True" : "False") << endl;
    return 0;
}