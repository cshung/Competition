#include "stdafx.h"

// https://leetcode.com/problems/two-sum/

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
            map<int, unsigned int> previous;
            for (unsigned int i = 0; i < numbers.size(); i++)
            {
                if (i == 0)
                {
                    previous.insert(pair<int, unsigned int>(numbers[i], i));
                }
                else
                {
                    map<int, unsigned int>::iterator probe = previous.find(target - numbers[i]);
                    if (probe != previous.end())
                    {
                        result.push_back(probe->second + 1);
                        result.push_back(i + 1);
                        break;
                    }
                    else
                    {
                        previous.insert(pair<int, unsigned int>(numbers[i], i));
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
