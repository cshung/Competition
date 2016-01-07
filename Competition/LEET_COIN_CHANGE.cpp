#include "stdafx.h"

// https://leetcode.com/problems/coin-change/

#include "LEET_COIN_CHANGE.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COIN_CHANGE
{
    class Solution
    {
    public:
        int coinChange(vector<int>& coins, int amount)
        {
            vector<int> answer;
            answer.resize(amount + 1);
            answer[0] = 0;
            for (int i = 1; i <= amount; i++)
            {
                int goal = i;
                int count = -1;
                for (unsigned int j = 0; j < coins.size(); j++)
                {
                    int remainder = goal - coins[j];
                    if (remainder >= 0)
                    {
                        int recursive_solution = answer[remainder];
                        if (recursive_solution != -1)
                        {
                            if (count == -1)
                            {
                                count = recursive_solution + 1;
                            }
                            else
                            {
                                count = min(count, recursive_solution + 1);
                            }
                        }
                    }
                }

                answer[i] = count;
            }
            return answer[amount];
        }
    };
};

using namespace _LEET_COIN_CHANGE;

int LEET_COIN_CHANGE()
{
    Solution solution;
    vector<int> coin;
    coin.push_back(1);
    coin.push_back(2);
    coin.push_back(5);
    cout << solution.coinChange(coin, 11) << endl;
    return 0;
}