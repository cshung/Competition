#include "stdafx.h"

// https://leetcode.com/problems/flip-string-to-monotone-increasing

#include "LEET_FLIP_STRING_TO_MONOTONE_INCREASING.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FLIP_STRING_TO_MONOTONE_INCREASING
{
    class Solution
    {
    public:
        int minFlipsMonoIncr(string S)
        {
            if (S.length() < 2)
            {
                return 0;
            }
            vector<int> forward;
            vector<int> backward;
            forward.resize(S.length() + 2);
            backward.resize(S.length() + 2);
            int f = 0;
            int b = 0;
            forward[0] = 0;
            backward[S.length() + 1] = 0;
            for (int i = 0; i < S.length(); i++)
            {
                int j = S.length() - 1 - i;
                if (S[i] == '1')
                {
                    f++;
                }
                if (S[j] == '0')
                {
                    b++;
                }
                forward[i + 1] = f;
                backward[j + 1] = b;
            }
            int best = S.length();
            for (int i = 0; i < S.length() + 1; i++)
            {
                best = min(best, forward[i] + backward[i + 1]);
            }
            return best;
        }
    };
};

using namespace _LEET_FLIP_STRING_TO_MONOTONE_INCREASING;

int LEET_FLIP_STRING_TO_MONOTONE_INCREASING()
{
    Solution solution;
    cout << solution.minFlipsMonoIncr("00110") << endl;
    cout << solution.minFlipsMonoIncr("010110") << endl;
    cout << solution.minFlipsMonoIncr("00011000") << endl;
    return 0;
}