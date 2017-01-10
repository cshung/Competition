#include "stdafx.h"

// 

#include "LEET_HAMMING_DISTANCE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_HAMMING_DISTANCE
{
    class Solution
    {
    public:
        int hammingDistance(int x, int y)
        {
            int mask = 1;
            int result = 0;
            for (int i = 0; i < 32; i++)
            {
                int mask_x = x & mask;
                int mask_y = y & mask;
                if (mask_x != mask_y)
                {
                    result++;
                }
                mask = mask << 1;
            }

            return result;
        }
    };
};

using namespace _LEET_HAMMING_DISTANCE;

int LEET_HAMMING_DISTANCE()
{
    Solution solution;
    cout << solution.hammingDistance(1, 4) << endl;
    return 0;
}