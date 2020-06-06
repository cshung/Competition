#include "stdafx.h"

// https://leetcode.com/problems/random-pick-with-weight/

#include "LEET_RANDOM_PICK_WITH_WEIGHT.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANDOM_PICK_WITH_WEIGHT
{
    class Solution
    {
    public:
        Solution(vector<int>& w)
        {
            int sum = 0;
            for (int i = 0; i < w.size(); i++)
            {
                sum += w[i];
                sums.push_back(sum);
            }
        }

        int pickIndex()
        {
            int v = rand() % sums[sums.size() - 1];
            return upper_bound(sums.begin(), sums.end(), v) - sums.begin();
        }
    private:
        vector<int> sums;
    };
};

using namespace _LEET_RANDOM_PICK_WITH_WEIGHT;

int LEET_RANDOM_PICK_WITH_WEIGHT()
{
    vector<int> w;
    w.push_back(1);
    Solution solution(w);
    cout << solution.pickIndex() << endl;
    return 0;
}