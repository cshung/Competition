#include "stdafx.h"

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/

#include "LEET_COUNT_OF_SMALLER_NUMBERS_AFTER_SELF.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_OF_SMALLER_NUMBERS_AFTER_SELF
{
    class Solution
    {
    public:
        vector<int> countSmaller(vector<int>& nums)
        {
            vector<int> counts(nums.size());
            vector<int> result(nums.size());
            vector<int> buffer(nums.size());
            for (size_t i = 0; i < result.size(); i++)
            {
                counts[i] = 0;
            }
            countSmaller(0, nums.size(), nums, result, buffer, counts);
            return counts;
        }

        void countSmaller(int begin, int end, vector<int>& nums, vector<int>& result, vector<int>& buffer, vector<int>& counts)
        {
            // At this point, we have a correct merge sort implementation
            if (end - begin <= 1)
            {
                for (size_t i = begin; i < end; i++)
                {
                    result[i] = i;
                }
                return;
            }
            int mid = (begin + end) / 2;
            countSmaller(begin, mid, nums, buffer, result, counts);
            countSmaller(mid, end, nums, buffer, result, counts);
            int i = mid - 1;
            int j = end - 1;
            int k = end - 1;
            while ((i >= begin) || (j >= mid))
            {
                if (i < begin)
                {
                    result[k--] = buffer[j--];
                }
                else if (j < mid)
                {
                    counts[buffer[i]] += (end - 1 - j);
                    result[k--] = buffer[i--];
                }
                else
                {
                    // Prioritize moving the left hand side item 
                    // to avoid counting identical element as smaller
                    if (nums[buffer[i]] <= nums[buffer[j]])
                    {
                        counts[buffer[i]] += (end - 1 - j);
                        result[k--] = buffer[i--];
                    }
                    else
                    {
                        result[k--] = buffer[j--];
                    }
                }
            }
            /*cout << "After merge" << endl;
            for (int i = begin; i < end; i++)
            {
                cout << nums[result[i]] << " ";
            }
            cout << endl;
            for (int i = begin; i < end; i++)
            {
                cout << counts[result[i]] << " ";
            }
            cout << endl;*/
        }
    };
};

using namespace _LEET_COUNT_OF_SMALLER_NUMBERS_AFTER_SELF;

int LEET_COUNT_OF_SMALLER_NUMBERS_AFTER_SELF()
{
    Solution solution;
    int input_array[] = { 5, 2, 6, 1 };
    vector<int> input(input_array, input_array + _countof(input_array));
    vector<int> result = solution.countSmaller(input);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}