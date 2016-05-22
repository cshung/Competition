#include "stdafx.h"

// https://leetcode.com/problems/reverse-vowels-of-a-string/

#include "LEET_REVERSE_VOWELS_OF_A_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_VOWELS_OF_A_STRING
{
    class Solution
    {
    public:
        bool is_vowel(char c)
        {
            switch (c)
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
                return true;
            default:
                return false;
            }
        }
        string reverseVowels(string s)
        {
            size_t length = s.length();
            char* y = new char[length + 1];
            int b = 0, e = length - 1;
            while (b <= e)
            {
                while (b <= e)
                {
                    if (is_vowel(s[b]))
                    {
                        break;
                    }
                    y[b] = s[b];
                    b++;
                }
                while (e >= b)
                {
                    if (is_vowel(s[e]))
                    {
                        break;
                    }
                    y[e] = s[e];
                    e--;
                }
                if (b <= e)
                {
                    y[b] = s[e];
                    y[e] = s[b];
                    b++;
                    e--;
                }
            }
            y[length] = '\0';
            string result = y;
            delete[] y;
            return result;
        }
    };
};

using namespace _LEET_REVERSE_VOWELS_OF_A_STRING;

int LEET_REVERSE_VOWELS_OF_A_STRING()
{
    Solution solution;
    cout << "\"" << solution.reverseVowels("ao") << "\"" << endl;
    return 0;
}