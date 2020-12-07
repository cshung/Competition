#include "stdafx.h"

// https://leetcode.com/problems/implement-rand10-using-rand7/

#include "LEET_IMPLEMENT_RAND10_USING_RAND7.h"
#include <map>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IMPLEMENT_RAND10_USING_RAND7
{
    int rand7()
    {
        int result = rand() % 7 + 1;
        assert(1 <= result && result <= 7);
        return result;
    }

    class Solution
    {
    public:
        int m_callCount;
        Solution() : m_callCount(0)
        {
            
        }
        int rand10()
        {
            while (true)
            {
                int x = rand7() - 1;
                int y = rand7() - 1;
                m_callCount += 2;
                int z = x * 7 + y;
                if (z < 40)
                {
                    int result = 1 + z % 10;
                    assert(1 <= result && result <= 10);
                    return result;
                }
            }
        }
    };
};

using namespace _LEET_IMPLEMENT_RAND10_USING_RAND7;

int LEET_IMPLEMENT_RAND10_USING_RAND7()
{
    Solution solution;
    vector<int> counts(10, 0);
    for (int i = 0; i < 10000; i++)
    {
        int index = solution.rand10() - 1;
        counts[index]++;
    }
    for (int i = 0; i < 10; i++)
    {
        cout << counts[i] << " ";
    }
    cout << endl << solution.m_callCount << endl;
    return 0;
}