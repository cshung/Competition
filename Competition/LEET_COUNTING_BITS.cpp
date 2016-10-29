#include "stdafx.h"

// https://leetcode.com/problems/counting-bits/

#include "LEET_COUNTING_BITS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNTING_BITS
{
    class Solution
    {
    public:
        vector<int> countBits(int num)
        {
            vector<int> result;
            result.resize(num + 1);
            result[0] = 0;
            if (num == 0)
            {
                return result;
            }
            result[1] = 1;
            int i = 0;
            int j = 2;
            int b = 1;
            while (true)
            {
                for (i = 0; i < j; i++)
                {
                    if (i + j > num)
                    {
                        break;
                    }
                    result[i + j] = result[i] + b;
                }
                if (i + j > num)
                {
                    break;
                }
                j = i + j;
            }

            return result;
        }
    };
};

using namespace _LEET_COUNTING_BITS;

int LEET_COUNTING_BITS()
{
    Solution solution;
    vector<int> v = solution.countBits(13);
    for (int i = 0; i < 14; i++)
    {
        cout << v[i] << ", ";
    }
    cout << endl;
    return 0;
}