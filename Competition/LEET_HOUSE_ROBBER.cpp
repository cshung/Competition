#include "stdafx.h"

// https://leetcode.com/problems/house-robber/

#include "LEET_HOUSE_ROBBER.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_HOUSE_ROBBER
{
    class Solution
    {
    public:
        int rob(vector<int> &num)
        {
            if (num.size() == 0)
            {
                return 0;
            }

            vector<int> best;
            best.resize(num.size());
            if (num.size() > 0)
            {
                best[0] = num[0];
            }
            if (num.size() > 1)
            {
                best[1] = max(num[0], num[1]);
            }

            for (unsigned int i = 2; i < num.size(); i++)
            {
                best[i] = max(num[i] + best[i - 2], best[i - 1]);
            }

            return best[num.size() - 1];
        }
    };
};

using namespace _LEET_HOUSE_ROBBER;

int LEET_HOUSE_ROBBER()
{
    Solution solution;
    vector<int> data;
    data.push_back(2);
    data.push_back(1);
    data.push_back(3);
    data.push_back(4);
    cout << solution.rob(data) << endl;
    return 0;
}
