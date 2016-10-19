#include "stdafx.h"

// https://leetcode.com/problems/longest-repeating-character-replacement/

#include "LEET_LONGEST_REPEATING_CHARACTER_REPLACEMENT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_REPEATING_CHARACTER_REPLACEMENT
{
    class Solution
    {
    public:
        int characterReplacement(string s, int k)
        {
            int best = 0;
            int* bestSoFar = new int[k + 1];
            for (char h = 'A'; h <= 'Z'; h++)
            {
                for (int i = 0; i < k + 1; i++)
                {
                    bestSoFar[i] = 0;
                }
                int base = 0;
                int top = k;
                int offset = 0;
                for (size_t i = 0; i < s.length(); i++)
                {
                    if (s[i] == h)
                    {
                        offset++;
                    }
                    else
                    {
                        offset++;
                        base = base - 1;
                        if (base < 0)
                        {
                            base = k;
                        }
                        bestSoFar[base] = -offset;
                        top--;
                        if (top < 0)
                        {
                            top = k;
                        }
                    }
                    if (bestSoFar[top] + offset > best)
                    {
                        best = bestSoFar[top] + offset;
                    }
                }
            }
            delete[] bestSoFar;
            return best;
        }
    };
};

using namespace _LEET_LONGEST_REPEATING_CHARACTER_REPLACEMENT;

int LEET_LONGEST_REPEATING_CHARACTER_REPLACEMENT()
{
    Solution solution;
    cout << solution.characterReplacement("ABAB", 2) << endl;
    cout << solution.characterReplacement("AABABBA", 1) << endl;
    return 0;
}