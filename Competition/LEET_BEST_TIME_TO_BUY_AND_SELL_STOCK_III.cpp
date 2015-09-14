#include "stdafx.h"

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

#include "LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_III.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_III
{
    class Solution
    {
    public:
        int maxProfit(vector<int>& prices)
        {
            int num_days = prices.size();
            if (num_days == 0)
            {
                return 0;
            }

            // Step 1: A dynamic programming solution for calculating the best profit 
            // if I can do a single transaction up to a current day starting from day 1
            vector<int> best_forward_profits;
            best_forward_profits.resize(num_days);
            best_forward_profits[0] = 0;

            int min_price_before = prices[0];
            int current_best_forward_profit = 0;
            
            for (int i = 1; i < num_days; i++)
            {
                int sell_now_profit = prices[i] - min_price_before;
                min_price_before = min(prices[i], min_price_before);
                best_forward_profits[i] = current_best_forward_profit = max(sell_now_profit, current_best_forward_profit);
            }

            // Step 2: A dynamic programming solution for calculating the best profit 
            // if I can do a single transaction starting from current day to the last day
            vector<int> best_backward_profits;
            best_backward_profits.resize(num_days);
            best_backward_profits[num_days - 1] = 0;

            int max_price_after = prices[num_days - 1];
            int current_best_backward_profit = 0;

            for (int i = num_days - 1; i >= 0; i--)
            {
                int buy_now_profit = max_price_after - prices[i];
                max_price_after = max(prices[i], max_price_after);
                best_backward_profits[i] = current_best_backward_profit = max(buy_now_profit, current_best_backward_profit);
            }

            // Step 3: Assemble the result
            int best_profit = 0;

            for (int i = 0; i < num_days; i++)
            {
                int current_profit = best_backward_profits[i] + best_forward_profits[i];
                best_profit = max(best_profit, current_profit);
            }

            return best_profit;
        }
    };
};

using namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_III;

int LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_III()
{
    Solution s;
    int case1[] = { 10, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    cout << s.maxProfit(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}