#include "stdafx.h"

// https://leetcode.com/problems/valid-palindrome/

#include "LEET_VALID_PALINDROME.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_VALID_PALINDROME
{
    class Solution {
    private:

        bool isAlphaNumeric(char c)
        {
            if ('A' <= c && c <= 'Z')
            {
                return true;
            }
            if ('a' <= c && c <= 'z')
            {
                return true;
            }
            if ('0' <= c && c <= '9')
            {
                return true;
            }
            return false;
        }
        char toLower(char x)
        {
            if (x >= 'A' && x <= 'Z')
            {
                return x + 'a' - 'A';
            }
            else
            {
                return x;
            }
        }
    public:
        bool isPalindrome(string s)
        {
            int b = 0;
            int e = s.size() - 1;
            while (b < e)
            {
                if (!isAlphaNumeric(s[b]))
                {
                    b++;
                }
                else if (!isAlphaNumeric(s[e]))
                {
                    e--;
                }
                else if (toLower(s[b]) == toLower(s[e]))
                {
                    b++;
                    e--;
                }
                else
                {
                    return false;
                }
            }

            return true;
        }
    };
};

using namespace _LEET_VALID_PALINDROME;

int LEET_VALID_PALINDROME()
{
    Solution s;
    cout << s.isPalindrome("A man, a plan, a canal: Panama") << endl;
    cout << !s.isPalindrome("race a car") << endl;
    cout << !s.isPalindrome("1a2") << endl;
    cout << s.isPalindrome("Zeus was deified, saw Suez.") << endl;
    return 0;
}