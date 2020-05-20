#include "stdafx.h"

// https://leetcode.com/problems/one-edit-distance/

#include "LEET_ONE_EDIT_DISTANCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ONE_EDIT_DISTANCE
{
    class Solution
    {
    public:
        bool isOneEditDistance(string s, string t)
        {
            int slen = s.size();
            int tlen = t.size();
            if (slen == tlen)
            {
                bool edited = false;
                for (int i = 0; i < slen; i++)
                {
                    if (s[i] != t[i])
                    {
                        if (edited)
                        {
                            return false;
                        }
                        else
                        {
                            edited = true;
                        }
                    }
                }
                return edited;
            }
            else if (slen + 1 == tlen)
            {
                return check(s, t);
            }
            else if (tlen + 1 == slen)
            {
                return check(t, s);
            }
            else
            {
                return false;
            }
        }

        bool check(string& s, string& t)
        {
            bool edited = false;
            for (int i = 0; i < t.size(); i++)
            {
                char sc = i == s.size() ? '\0' : s[i];
                char tc = edited ? t[i + 1] : t[i];
                if (sc != tc)
                {
                    if (edited)
                    {
                        return false;
                    }
                    else
                    {
                        edited = true;
                        i--;
                    }
                }
            }
            return edited;
        }
    };
};

using namespace _LEET_ONE_EDIT_DISTANCE;

int LEET_ONE_EDIT_DISTANCE()
{
    Solution solution;
    cout << solution.isOneEditDistance("ab", "acb") << endl;
    cout << solution.isOneEditDistance("cab", "ad") << endl;
    cout << solution.isOneEditDistance("1203", "1213") << endl;
    return 0;
}