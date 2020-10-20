#include "stdafx.h"

// https://leetcode.com/problems/combination-sum-iii/

#include "LEET_COMBINATION_SUM_III.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COMBINATION_SUM_III
{
    class Solution
    {
    public:
        vector<vector<int>> combinationSum3(int k, int n)
        {
            vector<vector<int>> solution;
            vector<int> current(k);
            combinationSum3(solution, current, 0, 0, k, n);
            return solution;
        }

        void combinationSum3(vector<vector<int>>& solution, vector<int>& current, int last_used, int count, int k, int n)
        {
            if (count == k)
            {
                if (n == 0) {
                    solution.push_back(current);
                }
                return;
            }
            for (int i = last_used + 1; i <= 9; i++)
            {
                if (n >= i)
                {
                    current[count] = i;
                    combinationSum3(solution, current, i, count + 1, k, n - i);
                }
            }
        }
    };
};

using namespace _LEET_COMBINATION_SUM_III;

int LEET_COMBINATION_SUM_III()
{
    Solution solution;

    vector<vector<int>> combinations = solution.combinationSum3(3, 7);
    for (auto combination : combinations)
    {
        for (auto value : combination)
        {
            cout << value << " ";
        }
        cout << endl;
    }
    return 0;
}