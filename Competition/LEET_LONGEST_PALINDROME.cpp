#include "stdafx.h"

// 

#include "LEET_LONGEST_PALINDROME.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_PALINDROME
{
    class Solution
    {
    public:
        int longestPalindrome(string s)
        {
            int frequency[256];
            for (int i = 0; i < 256; i++)
            {
                frequency[i] = 0;
            }
            for (size_t i = 0; i < s.length(); i++)
            {
                frequency[s[i]]++;
            }
            int length = 0;
            bool hasOdd = false;
            for (int i = 0; i < 256; i++)
            {
                if (!hasOdd && frequency[i] % 2 == 1)
                {
                    hasOdd = true;
                }
                length += (frequency[i] / 2) * 2;
            }

            if (hasOdd)
            {
                length += 1;
            }

            return length;
        }
    };
};

using namespace _LEET_LONGEST_PALINDROME;

int LEET_LONGEST_PALINDROME()
{
    Solution solution;
    cout << solution.longestPalindrome("abccccdd") << endl;
    return 0;
}