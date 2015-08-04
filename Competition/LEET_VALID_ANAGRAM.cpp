#include "stdafx.h"

// https://leetcode.com/problems/valid-anagram/

#include "LEET_VALID_ANAGRAM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VALID_ANAGRAM
{
    class Solution {
    public:
        bool isAnagram(string s, string t)
        {
            int count[26];
            for (unsigned int i = 0; i < 26; i++)
            {
                count[i] = 0;
            }
            for (unsigned int i = 0; i < s.length(); i++)
            {
                count[s[i] - 'a']++;
            }
            for (unsigned int i = 0; i < t.length(); i++)
            {
                count[t[i] - 'a']--;
            }
            for (unsigned int i = 0; i < 26; i++)
            {
                if (count[i] != 0)
                {
                    return false;
                }
            }
            return true;
        }
    };
};

using namespace _LEET_VALID_ANAGRAM;

int LEET_VALID_ANAGRAM()
{
    Solution solution;
    cout << solution.isAnagram("", "") << endl;
    cout << solution.isAnagram("anagram", "nagaram") << endl;
    cout << !solution.isAnagram("rat", "car") << endl;
    return 0;
}