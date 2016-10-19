#include "stdafx.h"

// https://leetcode.com/problems/reconstruct-original-digits-from-english/

#include "LEET_RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH
{
    class Solution
    {
    public:
        string originalDigits(string s)
        {
            int digits[11];
            int histogram[26];
            for (int i = 0; i < 11; i++)
            {
                digits[i] = 0;
            }
            for (int i = 0; i < 26; i++)
            {
                histogram[i] = 0;
            }
            for (size_t i = 0; i < s.length(); i++)
            {
                histogram[s[i] - 'a']++;
            }

            /*
            zero	z
            two     w
            six     x
            four	u
            eight	g

            five	f
            one     o
            nine	i
            three	r

            seven	v

            ten     n
            */
            digits[0] = histogram['z' - 'a'];
            histogram['z' - 'a'] -= digits[0];
            histogram['e' - 'a'] -= digits[0];
            histogram['r' - 'a'] -= digits[0];
            histogram['o' - 'a'] -= digits[0];

            digits[2] = histogram['w' - 'a'];
            histogram['t' - 'a'] -= digits[2];
            histogram['w' - 'a'] -= digits[2];
            histogram['o' - 'a'] -= digits[2];

            digits[6] = histogram['x' - 'a'];
            histogram['s' - 'a'] -= digits[6];
            histogram['i' - 'a'] -= digits[6];
            histogram['x' - 'a'] -= digits[6];

            digits[4] = histogram['u' - 'a'];
            histogram['f' - 'a'] -= digits[4];
            histogram['o' - 'a'] -= digits[4];
            histogram['u' - 'a'] -= digits[4];
            histogram['r' - 'a'] -= digits[4];

            digits[8] = histogram['g' - 'a'];
            histogram['e' - 'a'] -= digits[8];
            histogram['i' - 'a'] -= digits[8];
            histogram['g' - 'a'] -= digits[8];
            histogram['h' - 'a'] -= digits[8];
            histogram['t' - 'a'] -= digits[8];

            digits[5] = histogram['f' - 'a'];
            histogram['f' - 'a'] -= digits[5];
            histogram['i' - 'a'] -= digits[5];
            histogram['v' - 'a'] -= digits[5];
            histogram['e' - 'a'] -= digits[5];

            digits[1] = histogram['o' - 'a'];
            histogram['o' - 'a'] -= digits[1];
            histogram['n' - 'a'] -= digits[1];
            histogram['e' - 'a'] -= digits[1];

            digits[9] = histogram['i' - 'a'];
            histogram['n' - 'a'] -= digits[9];
            histogram['i' - 'a'] -= digits[9];
            histogram['n' - 'a'] -= digits[9];
            histogram['e' - 'a'] -= digits[9];

            digits[3] = histogram['r' - 'a'];
            histogram['t' - 'a'] -= digits[3];
            histogram['h' - 'a'] -= digits[3];
            histogram['r' - 'a'] -= digits[3];
            histogram['e' - 'a'] -= digits[3];
            histogram['e' - 'a'] -= digits[3];

            digits[7] = histogram['v' - 'a'];
            histogram['s' - 'a'] -= digits[7];
            histogram['e' - 'a'] -= digits[7];
            histogram['v' - 'a'] -= digits[7];
            histogram['e' - 'a'] -= digits[7];
            histogram['n' - 'a'] -= digits[7];

            digits[10] = histogram['n' - 'a'];
            histogram['t' - 'a'] -= digits[10];
            histogram['e' - 'a'] -= digits[10];
            histogram['n' - 'a'] -= digits[10];

            int digits_count = 0;
            for (int i = 0; i < 11; i++)
            {
                digits_count += digits[i];
            }
            char* result = new char[digits_count + 1];
            result[digits_count] = '\0';
            digits_count = 0;
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < digits[i]; j++)
                {
                    result[digits_count++] = i + '0';
                }
            }
            string t(result);
            delete[] result;
            return t;
        }
    };
};

using namespace _LEET_RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH;

int LEET_RECONSTRUCT_ORIGINAL_DIGITS_FROM_ENGLISH()
{
    Solution solution;
    cout << solution.originalDigits("owoztneoer") << endl;
    cout << solution.originalDigits("fviefuro") << endl;
    return 0;
}