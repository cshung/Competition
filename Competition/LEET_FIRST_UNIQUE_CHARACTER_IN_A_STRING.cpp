#include "stdafx.h"

// https://leetcode.com/problems/first-unique-character-in-a-string/

#include "LEET_FIRST_UNIQUE_CHARACTER_IN_A_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIRST_UNIQUE_CHARACTER_IN_A_STRING
{
    class Solution
    {
    public:
        int firstUniqChar(string s)
        {
            vector<bool> repeated;
            vector<int> seenIndex;
            seenIndex.resize(26);
            repeated.resize(s.length());
            for (int i = 0; i < 26; i++)
            {
                seenIndex[i] = -1;
            }
            for (int i = 0; i < s.length(); i++)
            {
                repeated[i] = false;
            }
            for (int i = 0; i < s.length(); i++)
            {
                char c = s[i];
                int code = c - 'a';
                if (seenIndex[code] == -1)
                {
                    seenIndex[code] = i;
                }
                else
                {
                    repeated[seenIndex[code]] = true;
                    repeated[i] = true;
                }
            }
            for (int i = 0; i < s.length(); i++)
            {
                if (!repeated[i])
                {
                    return i;
                }
            }
            return -1;
        }
    };
};

using namespace _LEET_FIRST_UNIQUE_CHARACTER_IN_A_STRING;

int LEET_FIRST_UNIQUE_CHARACTER_IN_A_STRING()
{
    Solution solution;
    cout << solution.firstUniqChar("leetcode") << endl;
    cout << solution.firstUniqChar("loveleetcode") << endl;
    return 0;
}