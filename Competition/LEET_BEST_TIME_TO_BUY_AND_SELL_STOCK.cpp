#include "stdafx.h"

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

#include "LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK
{
    class Solution
    {
    public:
        int maxProfit(vector<int>& prices)
        {
            int num_days = prices.size();

            if (num_days < 2)
            {
                return 0;
            }

            vector<int> min_cost;
            vector<int> max_sold;
            min_cost.resize(num_days);
            max_sold.resize(num_days);

            min_cost[0] = prices[0];
            for (int i = 1; i < num_days; i++)
            {
                min_cost[i] = min(min_cost[i - 1], prices[i]);
            }

            max_sold[num_days - 1] = prices[num_days - 1];
            for (int i = num_days - 2; i >= 0; i--)
            {
                max_sold[i] = max(max_sold[i + 1], prices[i]);
            }

            int max_profit = 0;
            for (int i = 0; i < num_days; i++)
            {
                max_profit = max(max_profit, max_sold[i] - min_cost[i]);
            }

            return max_profit;
        }
    };
};

using namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK;

int LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK()
{
    Solution s;
    int case1[] = { 10, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    cout << s.maxProfit(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}