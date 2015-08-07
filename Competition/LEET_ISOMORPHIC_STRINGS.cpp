#include "stdafx.h"

// https://leetcode.com/problems/isomorphic-strings/

#include "LEET_ISOMORPHIC_STRINGS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ISOMORPHIC_STRINGS
{
    class Solution
    {
    public:
        bool isIsomorphic(string s, string t)
        {
            if (s.length() != t.length())
            {
                return false;
            }

            map<char, char> forward_map;
            map<char, char> backward_map;
            for (unsigned int i = 0; i < s.length(); i++)
            {
                map<char, char>::iterator forward_probe = forward_map.find(s[i]);
                if (forward_probe == forward_map.end())
                {
                    forward_map.insert(pair<char, char>(s[i], t[i]));
                }
                else if (forward_probe->second != t[i])
                {
                    return false;
                }

                map<char, char>::iterator backward_probe = backward_map.find(t[i]);
                if (backward_probe == backward_map.end())
                {
                    backward_map.insert(pair<char, char>(t[i], s[i]));
                }
                else if (backward_probe->second != s[i])
                {
                    return false;
                }
            }

            return true;
        }
    };
};

using namespace _LEET_ISOMORPHIC_STRINGS;

int LEET_ISOMORPHIC_STRINGS()
{
    Solution solution;
    cout << solution.isIsomorphic("egg", "add") << endl;
    cout << !solution.isIsomorphic("foo", "bar") << endl;
    cout << solution.isIsomorphic("paper", "title") << endl;
    cout << !solution.isIsomorphic("ab", "aa") << endl;
    return 0;
}