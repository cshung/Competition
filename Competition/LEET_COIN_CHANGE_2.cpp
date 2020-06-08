#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_COIN_CHANGE_2.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COIN_CHANGE_2
{
    class Solution
    {
    public:
        int change(int amount, vector<int>& coins)
        {
            if (amount == 0)
            {
                return 1;
            }
            if (coins.size() == 0)
            {
                return 0;
            }

            sort(coins.begin(), coins.end());

            // ways[c][target] is the number of ways 'target' can be written as a sum of ascending coins with c being the index of the last coin.
            vector<vector<int>> ways(coins.size(), vector<int>(amount + 1, 0));

            for (int i = 0; i < coins.size(); i++)
            {
                ways[i][0] = 0;
            }

            for (int target = 1; target <= amount; target++)
            {
                for (int c = 0; c < coins.size(); c++)
                {
                    ways[c][target] = 0;
                    if (target == coins[c])
                    {
                        ways[c][target] = 1;
                    }
                    else if (target > coins[c])
                    {
                        int previous = target - coins[c];
                        for (int d = 0; d <= c; d++)
                        {
                            ways[c][target] += ways[d][previous];
                        }
                    }
                }
            }

            int answer = 0;
            for (int c = 0; c < coins.size(); c++)
            {
                answer += ways[c][amount];
            }
            return answer;
        }
    };
};

using namespace _LEET_COIN_CHANGE_2;

int LEET_COIN_CHANGE_2()
{
    vector<int> coins;
    coins.push_back(1);
    coins.push_back(2);
    coins.push_back(5);
    Solution s;
    cout << s.change(5, coins) << endl;
    return 0;
}