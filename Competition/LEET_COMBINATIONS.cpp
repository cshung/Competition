#include "stdafx.h"

// https://leetcode.com/problems/combinations/

#include "LEET_COMBINATIONS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COMBINATIONS
{
    class Solution
    {
    private:
        void generate_combinations(vector<bool>& used, int start, int k, vector<vector<int>>& result)
        {
            if (k == 0)
            {
                vector<int> found_combination;
                for (unsigned int i = 0; i < used.size(); i++)
                {
                    if (used[i])
                    {
                        found_combination.push_back(i + 1);
                    }
                }
                result.push_back(found_combination);
            }
            else
            {
                for (unsigned int i = start; i < used.size(); i++)
                {
                    if (!used[i])
                    {
                        used[i] = true;
                        generate_combinations(used, i + 1, k - 1, result);
                        used[i] = false;
                    }
                }
            }
        }
    public:
        vector<vector<int>> combine(int n, int k)
        {
            vector<vector<int>> result;
            vector<bool> used;
            used.resize(n);
            for (int i = 0; i < n; i++)
            {
                used[i] = false;
            }
            generate_combinations(used, 0, k, result);
            return result;
        }
    };
};

using namespace _LEET_COMBINATIONS;

int LEET_COMBINATIONS()
{
    Solution solution;
    vector<vector<int>> result = solution.combine(4, 2);
    for (unsigned int i = 0; i < result.size(); i++)
    {
        for (unsigned int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}