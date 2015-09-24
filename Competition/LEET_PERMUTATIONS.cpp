#include "stdafx.h"

// https://leetcode.com/problems/permutations/

#include "LEET_PERMUTATIONS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_PERMUTATIONS
{
    class Solution
    {
    private:
        void permute(vector<int>& nums, vector<bool>& used, vector<int>& partialVector, vector<vector<int>>& finalResult)
        {
            int size = nums.size();
            if (partialVector.size() == size)
            {
                finalResult.push_back(partialVector);
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    if (!used[i])
                    {
                        partialVector.push_back(nums[i]);
                        used[i] = true;
                        this->permute(nums, used, partialVector, finalResult);
                        partialVector.pop_back();
                        used[i] = false;
                    }
                }
            }
        }
    public:
        vector<vector<int>> permute(vector<int>& nums)
        {
            vector<vector<int>> finalResult;
            int size = nums.size();
            if (size > 0)
            {
                vector<bool> used;
                vector<int> partialVector;
                used.resize(size);
                for (int i = 0; i < size; i++)
                {
                    used[i] = false;
                }
                this->permute(nums, used, partialVector, finalResult);
            }
            return finalResult;
        }
    };
};

using namespace _LEET_PERMUTATIONS;

int LEET_PERMUTATIONS()
{
    int case1[] = { 1, 2, 3 };
    Solution s;
    vector<vector<int>> result = s.permute(vector<int>(case1, case1 + _countof(case1)));
    for (unsigned int i = 0; i < result.size(); i++)
    {
        for (unsigned int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j];
        }
        cout << endl;
    }
    return 0;
}