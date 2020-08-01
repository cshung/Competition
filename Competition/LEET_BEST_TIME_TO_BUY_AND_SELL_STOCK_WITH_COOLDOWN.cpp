#include "stdafx.h"

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/

#include "LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_WITH_COOLDOWN.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_WITH_COOLDOWN
{
    class Solution
    {
    public:
        int maxProfit(vector<int>& prices)
        {
            size_t n = prices.size();
            vector<int> best_holding(n);
            vector<int> best_not_holding(n);

            best_holding[n - 1] = prices[n - 1];
            best_not_holding[n - 1] = 0;

            for (int i = n - 2; i >= 0; i--)
            {
                int sell_option = (i == n - 2) ? prices[n - 2] : (prices[i] + best_not_holding[i + 2]);
                int hold_option = best_holding[i + 1];
                best_holding[i] = max(sell_option, hold_option);
                int buy_option = -prices[i] + best_holding[i + 1];
                int stay_option = best_not_holding[i + 1];
                best_not_holding[i] = max(buy_option, stay_option);
            }
            return best_not_holding[0];
        }
    };
};

using namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_WITH_COOLDOWN;

int LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_WITH_COOLDOWN()
{
    int case1_array[] = { 1,2,3,0,2 };
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    Solution s;
    cout << s.maxProfit(case1) << endl;
    return 0;
}