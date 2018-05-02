#include "stdafx.h"

// https://leetcode.com/problems/teemo-attacking

#include "LEET_TEEMO_ATTACKING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TEEMO_ATTACKING
{
    class Solution {
    public:
        int findPoisonedDuration(vector<int>& timeSeries, int duration) {
            int result = 0;

            int poisoned = -1;
            int next = 0;
            int recover = -1;
            while (true)
            {
                if (poisoned == -1)
                {
                    if (next == timeSeries.size())
                    {
                        break;
                    }
                    poisoned = timeSeries[next];
                    recover = timeSeries[next] + duration;
                    next++;
                }
                else
                {
                    if ((next == timeSeries.size()) || (recover <= timeSeries[next]))
                    {
                        result += recover - poisoned;
                        poisoned = -1;
                    }
                    else
                    {
                        recover = timeSeries[next] + duration;
                        next++;
                    }
                }
            }
            return result;
        }
    };
};

using namespace _LEET_TEEMO_ATTACKING;

int LEET_TEEMO_ATTACKING()
{
    Solution solution;
    int test1_array[] = { 1, 4 };
    vector<int> test1(test1_array, test1_array + _countof(test1_array));
    cout << solution.findPoisonedDuration(test1, 2) << endl;
    int test2_array[] = { 1, 2 };
    vector<int> test2(test2_array, test2_array + _countof(test2_array));
    cout << solution.findPoisonedDuration(test2, 2) << endl;
    return 0;
}