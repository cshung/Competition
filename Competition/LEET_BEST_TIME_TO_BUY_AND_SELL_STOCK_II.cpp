#include "stdafx.h"

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

#include "LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_II
{
    class Solution
    {
    public:
        int maxProfit(vector<int>& prices)
        {
            int best_profit = 0;
            bool holding = false;
            int purchase_price = -1; 
            int time = 0;
            int num_days = prices.size();
            while (time < num_days)
            {
                if (!holding)
                {
                    if (time < num_days - 1)
                    {
                        if (prices[time] < prices[time + 1])
                        {
                            purchase_price = prices[time];
                            holding = true;
                        }
                    }
                }
                else
                {
                    if (time < num_days - 1)
                    {
                        if (prices[time] > prices[time + 1])
                        {
                            best_profit += (prices[time] - purchase_price);
                            purchase_price = -1;
                            holding = false;
                        }
                    }
                    else
                    {
                        best_profit += (prices[time] - purchase_price);
                        purchase_price = -1;
                        holding = false;
                    }
                }

                time++;
            }

            return best_profit;
        }
    };
};

using namespace _LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_II;

int LEET_BEST_TIME_TO_BUY_AND_SELL_STOCK_II()
{
    Solution s;
    int case1[] = { 10, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    cout << s.maxProfit(vector<int>(case1, case1 + _countof(case1))) << endl;
    return 0;
}