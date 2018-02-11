#include "stdafx.h"

// https://leetcode.com/problems/number-of-segments-in-a-string

#include "LEET_NUMBER_OF_SEGMENTS_IN_A_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBER_OF_SEGMENTS_IN_A_STRING
{
    class Solution
    {
    public:
        int countSegments(string s)
        {
            int count = 0;
            int state = 0;
            for (size_t i = 0; i < s.length(); i++)
            {
                char c = s[i];
                if (state == 0)
                {
                    if (c != ' ')
                    {
                        state = 1;
                        count++;
                    }
                }
                else
                {
                    if (c == ' ')
                    {
                        state = 0;
                    }
                }
            }
            return count;
        }
    };
};

using namespace _LEET_NUMBER_OF_SEGMENTS_IN_A_STRING;

int LEET_NUMBER_OF_SEGMENTS_IN_A_STRING()
{
    Solution solution;
    cout << solution.countSegments("Hello, my name is John") << endl;
    return 0;
}