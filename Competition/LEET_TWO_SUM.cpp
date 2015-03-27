#include "stdafx.h"

// https://leetcode.com/problems/sum-root-to-leaf-numbers/

#include "LEET_TWO_SUM.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_TWO_SUM
{
    class Solution {
    public:
        vector<int> twoSum(vector<int> &numbers, int target) {
            vector<int> result;
            for (unsigned int i = 0; i < numbers.size(); i++)
            {
                for (unsigned int j = i + 1; j < numbers.size(); j++)
                {
                    if (numbers[i] + numbers[j] == target)
                    {
                        
                        result.push_back(i + 1);
                        result.push_back(j + 1);
                        return result;
                    }
                }
            }

            return result;
        }
    };
};

using namespace _LEET_TWO_SUM;

int LEET_TWO_SUM()
{
    vector<int> data;
    data.push_back(2);
    data.push_back(7);
    data.push_back(11);
    data.push_back(15);
    Solution solution;
    vector<int> indices = solution.twoSum(data, 9);
    cout << indices[0] << " " << indices[1] << endl;
    return 0;
}
