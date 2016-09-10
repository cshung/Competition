#include "stdafx.h"

// https://leetcode.com/problems/shuffle-an-array/

#include "LEET_SHUFFLE_AN_ARRAY.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SHUFFLE_AN_ARRAY
{
    class Solution
    {
    public:
        Solution(vector<int> nums)
        {
            this->nums = nums;
        }

        /** Resets the array to its original configuration and return it. */
        vector<int> reset()
        {
            return this->nums;
        }

        /** Returns a random shuffling of the array. */
        vector<int> shuffle()
        {
            vector<int> result = this->nums;
            size_t n = result.size();
            if (n > 0)
            {
                for (size_t i = n - 1; i > 0; i--)
                {
                    int j = rand() % (i + 1);
                    swap(result[i], result[j]);
                }
            }
            return result;
        }
    private:
        vector<int> nums;
    };
};

using namespace _LEET_SHUFFLE_AN_ARRAY;

int LEET_SHUFFLE_AN_ARRAY()
{
    vector<int> v;
    map<int, int> c;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    Solution solution(v);
    for (int k = 0; k < 1000; k++)
    {
        vector<int> t = solution.shuffle();
        int x = t[0] * 100 + t[1] * 10 + t[2];
        auto probe = c.find(x);
        if (probe == c.end())
        {
            c.insert(make_pair(x, 1));
        }
        else
        {
            probe->second++;
        }
    }
    for (auto iter = c.begin(); iter != c.end(); iter++)
    {
        cout << iter->first << ", " << iter->second << endl;
    }
    return 0;
}