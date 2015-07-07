#include "stdafx.h"

// https://leetcode.com/problems/regular-expression-matching/

#include "LEET_REGULAR_EXPRESSION_MATCHING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REGULAR_EXPRESSION_MATCHING
{
    class Solution
    {
    public:
        bool isMatch(string s, string p)
        {
            return this->isMatch(s, 0, p, 0);
        }
    private:
        bool isMatchCharacter(char s, char p)
        {
            if (p == '.')
            {
                return true;
            }
            else
            {
                return s == p;
            }
        }

        bool isMatch(string& s, int s_start, string& p, int p_start)
        {
            if (p_start == p.length())
            {
                return s_start == s.length();
            }
            else if (p_start == p.length() - 1)
            {
                if (s_start == s.length() - 1)
                {
                    return this->isMatchCharacter(s[s_start], p[p_start]);
                }
                else
                {
                    // There is only one character left in the pattern but more than one character in string, doom to failure!
                    return false;
                }
            }
            else if (s_start < s.length())
            {
                // p_start != p.length() - 1, so p_start + 1 is a valid p index
                if (p[p_start + 1] != '*')
                {
                    return this->isMatchCharacter(s[s_start], p[p_start]) && this->isMatch(s, s_start + 1, p, p_start + 1);
                }
                else
                {
                    return this->isMatch(s, s_start, p, p_start + 2)
                        || this->isMatchCharacter(s[s_start], p[p_start]) && this->isMatch(s, s_start + 1, p, p_start + 2)
                        || this->isMatchCharacter(s[s_start], p[p_start]) && this->isMatch(s, s_start + 1, p, p_start);
                }
            }
            else
            {
                return false;
            }
        }
    };
};

using namespace _LEET_REGULAR_EXPRESSION_MATCHING;

int LEET_REGULAR_EXPRESSION_MATCHING()
{
    Solution s;
    /*
    cout << (s.isMatch("aa","a") == 0) << endl;
    cout << s.isMatch("aa","aa") << endl;
    cout << (s.isMatch("aaa","aa") == 0) << endl;
    cout << s.isMatch("aa", "a*") << endl;
    cout << s.isMatch("aa", ".*") << endl;
    cout << s.isMatch("ab", ".*") << endl;
    cout << s.isMatch("aab", "c*a*b") << endl;
    cout << s.isMatch("ab", ".*c") << endl;
    */
    cout << s.isMatch("aaa", "ab*a") << endl;
    return 0;
}