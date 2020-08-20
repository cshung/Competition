#include "stdafx.h"

// https://leetcode.com/problems/numbers-with-same-consecutive-differences/

#include "LEET_NUMBERS_WITH_SAME_CONSECUTIVE_DIFFERENCES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBERS_WITH_SAME_CONSECUTIVE_DIFFERENCES
{
    class Solution
    {
    public:
        vector<int> numsSameConsecDiff(int N, int K)
        {
            vector<int> answer;
            for (int i = 1; i <= 9; i++)
            {
                dfs(0, i, N, K, answer);
            }
            if (N == 1)
            {
                answer.push_back(0);
            }
            return answer;
        }
    private:
        void dfs(int current_number, int next_digit, int num_remaining_digits, int K, vector<int>& answer)
        {
            current_number = current_number * 10 + next_digit;
            num_remaining_digits--;
            if (num_remaining_digits == 0)
            {
                answer.push_back(current_number);
            }
            else
            {
                if (K == 0)
                {
                    dfs(current_number, next_digit, num_remaining_digits, K, answer);
                }
                else
                {
                    int small_next_digit = next_digit - K;
                    if (small_next_digit >= 0)
                    {
                        dfs(current_number, small_next_digit, num_remaining_digits, K, answer);
                    }
                    int large_next_digit = next_digit + K;
                    if (large_next_digit <= 9)
                    {
                        dfs(current_number, large_next_digit, num_remaining_digits, K, answer);
                    }
                }
            }
        }
    };
};

using namespace _LEET_NUMBERS_WITH_SAME_CONSECUTIVE_DIFFERENCES;

int LEET_NUMBERS_WITH_SAME_CONSECUTIVE_DIFFERENCES()
{
    Solution solution;
    auto answer = solution.numsSameConsecDiff(3, 7);
    for (auto entry : answer)
    {
        cout << entry << " ";
    }
    cout << endl;
    return 0;
}