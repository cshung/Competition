#include "stdafx.h"

// https://leetcode.com/problems/predict-the-winner

#include "LEET_PREDICT_THE_WINNER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_PREDICT_THE_WINNER
{
    class Solution
    {
    public:
        bool PredictTheWinner(vector<int>& nums)
        {
            // Denote f(i, L) to be the (nextPlayer - otherPlayer) on the interval [i, i + L] 
            // f(i, L) = nums(i) for all i
            // f(p, L) = max(num[p] - f(p + 1, L - 1), nums[q] - f(p, L - 1))
            vector<int> buffer1;
            vector<int> buffer2;
            buffer1.resize(nums.size());
            buffer2.resize(nums.size());
            for (int i = 0; i < nums.size(); i++)
            {
                buffer1[i] = nums[i];
            }
            vector<int>* prevPointer = &buffer1;
            vector<int>* nextPointer = &buffer2;
            for (int l = 1; l < nums.size(); l++)
            {
                vector<int>& prev = *prevPointer;
                vector<int>& next = *nextPointer;
                for (int p = 0; p + l < nums.size(); p++)
                {
                    next[p] = max(nums[p] - prev[p + 1], nums[p + l] - prev[p]);
                }
                swap(prevPointer, nextPointer);
            }

            // Be careful, the last computed buffer is pointed by prevPointer!
            return (*prevPointer)[0] >= 0;
        }
    };
};

using namespace _LEET_PREDICT_THE_WINNER;

int LEET_PREDICT_THE_WINNER()
{
    Solution solution;
    int test[] = { 1, 5, 233, 7 };
    cout << solution.PredictTheWinner(vector<int>(test, test + _countof(test))) << endl;
    return 0;
}