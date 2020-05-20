#include "stdafx.h"

// https://leetcode.com/problems/online-stock-span/

#include "LEET_ONLINE_STOCK_SPAN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ONLINE_STOCK_SPAN
{
    class StockSpanner
    {
    public:
        int next(int price)
        {
            int n = prices.size();
            prices.push_back(price);
            left.push_back(-1);
            right.push_back(-1);
            parent.push_back(n - 1);
            left_count.push_back(0);
            right_count.push_back(0);
            if (n > 0)
            {
                right[n - 1] = n;
            }
            else
            {
                root = 0;
            }
            int c = parent[n];
            while (c != -1)
            {
                if (prices[c] > prices[n])
                {
                    break;
                }
                else
                {
                    int nc = parent[c];
                    int l = left[n];

                    right[c] = -1;
                    parent[n] = -1;

                    if (nc != -1)
                    {
                        right[nc] = n;
                    }
                    parent[n] = nc;

                    left[n] = c;
                    parent[c] = n;

                    right[c] = l;
                    if (l != -1)
                    {
                        parent[l] = c;
                    }

                    int lc = (l == -1) ? 0 : left_count[l] + 1 + right_count[l];

                    right_count[c] = lc;
                    left_count[n] = left_count[c] + 1 + right_count[c];

                    c = nc;
                }
            }
            if (c == -1)
            {
                root = n;
            }
            return left_count[n] + 1;
        }
    private:
        int root;
        vector<int> prices;
        vector<int> left;
        vector<int> right;
        vector<int> parent;
        vector<int> left_count;
        vector<int> right_count;
    };
};

using namespace _LEET_ONLINE_STOCK_SPAN;

int LEET_ONLINE_STOCK_SPAN()
{
    StockSpanner s;
    cout << s.next(100) << endl;
    cout << s.next(80) << endl;
    cout << s.next(60) << endl;
    cout << s.next(70) << endl;
    cout << s.next(60) << endl;
    cout << s.next(75) << endl;
    cout << s.next(85) << endl;
    return 0;
}