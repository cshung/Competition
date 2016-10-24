#include "stdafx.h"

// https://leetcode.com/problems/ransom-note/

#include "LEET_RANSOM_NOTE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANSOM_NOTE
{
    class Solution
    {
    public:
        bool canConstruct(string ransomNote, string magazine)
        {
            int frequency[256];
            for (int i = 0; i < 256; i++)
            {
                frequency[i] = 0;
            }
            for (size_t i = 0; i < magazine.length(); i++)
            {
                frequency[magazine[i]]++;
            }
            for (size_t i = 0; i < ransomNote.length(); i++)
            {
                if (--frequency[ransomNote[i]] < 0)
                {
                    return false;
                }
            }
            return true;
        }
    };
};

using namespace _LEET_RANSOM_NOTE;

int LEET_RANSOM_NOTE()
{
    Solution solution;
    cout << solution.canConstruct("aabb", "abac") << endl;
    return 0;
}