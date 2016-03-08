#include "stdafx.h"

// https://leetcode.com/problems/decode-ways/

#include "LEET_DECODE_WAYS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DECODE_WAYS
{
    class Solution
    {
    public:
        int numDecodings(string s)
        {
            int n = s.length();
            if (n == 0)
            {
                // The judge required that, but technically I think there is exactly 1 way to decode the empty string and the empty message
                return 0;
            }
            int a = 1;                     // decodeWays[i - 2], there is exactly one way to decode the empty string
            int b = (s[0] == '0') ? 0 : 1; // decodeWays[i - 1], there is exactly one way to decode a single digit if it is not zero
            
            for (int i = 2; i <= n; i++)
            {
                char currentCharacter  = s[i - 1];
                char previousCharacter = s[i - 2];
                bool canDoOneDigitDecoding = (currentCharacter != '0');
                bool canDoTwoDigitDecoding = (previousCharacter == '1' || (previousCharacter == '2' && currentCharacter <= '6'));
                int c = (canDoOneDigitDecoding ? b : 0) + (canDoTwoDigitDecoding ? a : 0); // decodeWays[i] = (canDoOneDigitDecoding ? decodeWays[i - 1] : 0) + (canDoTwoDigitDecoding ? decodeWays[i - 2] : 0);
                a = b;
                b = c;
            }
            return b;
        }
    };
};

using namespace _LEET_DECODE_WAYS;

int LEET_DECODE_WAYS()
{
    Solution solution;
    cout << solution.numDecodings("1012") << endl;   // 0
    return 0;
}