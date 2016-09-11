#include "stdafx.h"

// https://leetcode.com/contest/4/problems/random-pick-index/

#include "LEET_RANDOM_PICK_INDEX.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_RANDOM_PICK_INDEX
{
    class Entry
    {
    public:
        Entry(int value, size_t index) : m_value(value), m_index(index) {}
        int m_value;
        size_t m_index;
    };

    bool compareEntry(Entry i, Entry j)
    {
        return i.m_value < j.m_value;
    }

    class Solution
    {
    public:
        Solution(vector<int> nums)
        {
            if (nums.size() == 0)
            {
                return;
            }

            for (size_t i = 0; i < nums.size(); i++)
            {
                this->m_entries.push_back(Entry(nums[i], i));
            }
            sort(this->m_entries.begin(), this->m_entries.end(), compareEntry);
        }

        int pick(int target)
        {
            // I have no idea how can this run out of memory :(
            auto from = lower_bound(this->m_entries.begin(), this->m_entries.end(), Entry(target, 0), compareEntry);
            auto to = upper_bound(this->m_entries.begin(), this->m_entries.end(), Entry(target, 0), compareEntry);
            long long x = distance(from, to);
            return (int)(from + rand() % x)->m_index;
        }
    private:
        vector<Entry> m_entries;
    };

};

using namespace _LEET_RANDOM_PICK_INDEX;

int LEET_RANDOM_PICK_INDEX()
{
    vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    nums.push_back(2);
    Solution solution(nums);
    for (int i = 0; i < 100000000; i++)
    {
        cout << solution.pick(2) << endl;
    }
    return 0;
}