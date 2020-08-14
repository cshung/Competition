#include "stdafx.h"

// https://leetcode.com/problems/make-the-string-great/

#include "LEET_MAKE_THE_STRING_GREAT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAKE_THE_STRING_GREAT
{
    class Solution
    {
    public:
        string makeGood(string s)
        {
            vector<char> v;
            for (int i = 0; i < s.length(); i++)
            {
                v.push_back(s[i]);
                while (v.size() >= 2)
                {
                    char p = v[v.size() - 1];
                    char q = v[v.size() - 2];
                    if ((p + 'a' - 'A' == q) || (q + 'a' - 'A' == p))
                    {
                        v.pop_back();
                        v.pop_back();
                    }
                    else
                    {
                        break;
                    }
                }
            }
            ostringstream oss;
            for (auto c : v)
            {
                oss << c;
            }
            return oss.str();
        }
    };
};

using namespace _LEET_MAKE_THE_STRING_GREAT;

int LEET_MAKE_THE_STRING_GREAT()
{
    Solution solution;
    cout << solution.makeGood("leEeetcode") << endl;
    cout << solution.makeGood("abBAcC") << endl;
    cout << solution.makeGood("s") << endl;
    return 0;
}