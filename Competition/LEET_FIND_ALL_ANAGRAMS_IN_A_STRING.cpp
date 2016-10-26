#include "stdafx.h"

// https://leetcode.com/problems/find-all-anagrams-in-a-string/

#include "LEET_FIND_ALL_ANAGRAMS_IN_A_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_ALL_ANAGRAMS_IN_A_STRING
{
    class Solution
    {
    public:
        vector<int> findAnagrams(string s, string p)
        {
            vector<int> result;
            if (s.length() >= p.length())
            {
                int histogram[26];
                for (int i = 0; i < 26; i++)
                {
                    histogram[i] = 0;
                }

                // Pre-populate the histogram with the first |p| characters
                for (size_t i = 0; i < p.length(); i++)
                {
                    histogram[s[i] - 'a']++;
                }

                for (size_t i = p.length(); i <= s.length(); i++)
                {
                    // Check match
                    bool pass = true;
                    for (size_t j = 0; j < p.length(); j++)
                    {
                        histogram[p[j] - 'a']--;
                        if (histogram[p[j] - 'a'] < 0)
                        {
                            pass = false;
                        }
                    }
                    for (size_t j = 0; j < p.length(); j++)
                    {
                        histogram[p[j] - 'a']++;
                    }
                    if (pass)
                    {
                        result.push_back(i - p.length());
                    }

                    if (i == s.length())
                    {
                        break;
                    }

                    // Updating histogram
                    histogram[s[i] - 'a']++;
                    histogram[s[i - p.length()] - 'a']--;
                }

            }
            return result;
        }
    };
};

using namespace _LEET_FIND_ALL_ANAGRAMS_IN_A_STRING;

int LEET_FIND_ALL_ANAGRAMS_IN_A_STRING()
{
    Solution solution;
    vector<int> result = solution.findAnagrams("abab", "ab");
    for (auto itr : result)
    {
        cout << itr << ", ";
    }
    cout << endl;
    result = solution.findAnagrams("cbaebabacd", "abc");
    for (auto itr : result)
    {
        cout << itr << ", ";
    }
    cout << endl;
    return 0;
}